Mutex create_mutex(void)
{
	Mutex mutex;
	pthread_mutex_init(&mutex.handle, NULL);
	return mutex;
}

void destroy_mutex(Mutex mutex)
{
	pthread_mutex_destroy(&mutex.handle);
}

void lock_mutex(Mutex *mutex)
{
	pthread_mutex_lock(&mutex->handle);
}
void unlock_mutex(Mutex *mutex)
{
	pthread_mutex_unlock(&mutex->handle);
}

Cond create_cond(void)
{
	Cond cond;
	pthread_cond_init(&cond.handle, NULL);
	return cond;
}

void destroy_cond(Cond cond)
{
	pthread_cond_destroy(&cond.handle);
}

void broadcast_cond(Cond *cond) 
{
	pthread_cond_broadcast(&cond->handle);
}
void signal_cond(Cond *cond) 
{
	pthread_cond_signal(&cond->handle);
}

void wait_cond(Cond *cond, Mutex *mutex)
{
	pthread_cond_wait(&cond->handle,&mutex->handle);
}

Semaphore create_semaphore(u64 value)
{
	Semaphore semaphore;
	atomic_store(&semaphore.value, value);
	pthread_cond_init(&semaphore.handle, NULL);
	return semaphore;
}

void destroy_semaphore(Semaphore semaphore)
{
	pthread_cond_destroy(&semaphore.handle);
}

b32 binary_signal_semaphore(Semaphore *semaphore)
{
	atomic_store(&semaphore->value, true);
	pthread_cond_broadcast(&semaphore->handle);
	return true;
}

void binary_reset_semaphore(Semaphore *semaphore)
{
	atomic_store(&semaphore->value, false);
}

void binary_wait_semaphore(Semaphore *semaphore, Mutex *mutex)
{
	while(atomic_load(&semaphore->value) == false)
	{
		pthread_cond_wait(&semaphore->handle, &mutex->handle);
	}
}

void* end_thread_work(Thread *thread)
{
	return (void*)-1lu;
}

void *thread_wrapper(void *args)
{
	Thread *thread = args;
#if defined(thread_local)
	CURRENT_THREAD = thread;
#endif
	while(true)
	{
		lock_mutex(&thread->mutex);
		binary_signal_semaphore(&thread->idling_semaphore);
		binary_wait_semaphore(&thread->working_semaphore, &thread->mutex);
		binary_reset_semaphore(&thread->working_semaphore);
		unlock_mutex(&thread->mutex);

		PFN_Thread *function = (PFN_Thread*)atomic_load(&thread->function);
		void *ret = 0;
		if(function)
			ret = function(thread);
		if(ret == (void*)-1lu)
			break;			
	}
	return NULL;
}

Thread *allocate_thread(Arena *arena, u64 scratch_arena_size)
{
	Thread *thread = arena_push(arena, true, sizeof(Thread));
	for(u32 i = 0; i < 2; i++)
	{
		thread->scratch_arenas[i] = init_arena(scratch_arena_size, arena_push(arena, 0, scratch_arena_size));
	}
	thread->working_semaphore = create_semaphore(0);
	thread->idling_semaphore = create_semaphore(0);
	thread->mutex = create_mutex();
	thread->index = U32_MAX;
	thread->handle = pthread_self();
	return thread;
}

Thread *create_thread(Arena *arena, u64 scratch_arena_size, u64 stack_size)
{
	stack_size = Max(KiB(8), stack_size);
	Thread *thread = allocate_thread(arena, scratch_arena_size);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, stack_size);
#if !defined(thread_local)
	lock_mutex(&thread_table_mutex);
	for(u32 i = 0; i < max_thread_count; i++)
	{
		if(thread_table[i] == 0)
		{
			thread_table[i] = thread;
			thread->index = i;
			goto FOUND;
		}
	}
	unlock_mutex(&thread_table_mutex);
	printf("Too many threads in global array!\n");
	pthread_attr_destroy(&attr);
	return 0;
FOUND:
	unlock_mutex(&thread_table_mutex);
#endif

	if(pthread_create(&thread->handle, &attr, thread_wrapper, (void*)thread))
	{
		printf("There was an error while calling pthread_create(...)\n");
	}
	pthread_attr_destroy(&attr);
	return thread;
}

void destroy_thread(Thread *thread)
{
	if(thread == 0)
		return;
	if(thread->index > max_thread_count)
		return;

	thread->index = max_thread_count+1;

	wait_for_thread(thread);	
	begin_thread_work(thread, end_thread_work);
	lock_mutex(&thread_table_mutex);
	for(u32 i = 0; i < max_thread_count; i++)
	{
		if(thread_table[i])
		{
			if(thread_table[i]->handle == thread->handle)
			{
				thread_table[i] = 0;
				break;
			}
		}
	}
	unlock_mutex(&thread_table_mutex);
}

void wait_for_thread(Thread *thread)
{
	lock_mutex(&thread->mutex);
	binary_wait_semaphore(&thread->idling_semaphore, &thread->mutex);	
	binary_reset_semaphore(&thread->idling_semaphore);
	unlock_mutex(&thread->mutex);
}

b32 begin_thread_work(Thread *thread, PFN_Thread *function)
{
	lock_mutex(&thread->mutex);
	binary_signal_semaphore(&thread->working_semaphore);
	atomic_store(&thread->function, (u64)function);
	unlock_mutex(&thread->mutex);
	return false;
}

Thread *start_thread(Arena *arena, u64 scratch_arena_size, u64 stack_size, PFN_Thread *function)
{
	Thread *thread = create_thread(arena, scratch_arena_size, stack_size);
	if(thread)
	{
		wait_for_thread(thread);
		begin_thread_work(thread, function);
	}
	return thread;
}


#if defined(COMPILER_GCC) || defined(COMPILER_CLANG)
Thread *current_thread(void)
{
	return CURRENT_THREAD;	
}
#else
Thread* current_thread(void)
{
	pthread_t handle = pthread_self();
	if(main_thread == NULL)
	{
		printf("ABORT: Trying to use scratch arenas before the main thread was created!\n");
		exit(1);
	}
	if(main_thread->handle == handle)
	{
		return main_thread;
	}
	for(u32 i = 0; i < max_thread_count; i++)
	{
		if(thread_table[i])
		{
			if(thread_table[i]->handle == handle)
			{
				return thread_table[i];
			}
		}
	}
	return 0;
}
#endif

u32 get_physical_thread_count()
{
	cpu_set_t mask;
	sched_getaffinity(0,sizeof(mask), &mask);
	s32 count = CPU_COUNT(&mask);
	return Min((u32)count, 1024);
}

b32 set_thread_affinity(Thread *thread, u32 cpu_index)
{
	if(thread == 0)
		thread = current_thread();
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET((u64)cpu_index, &set);
	if(pthread_setaffinity_np(thread->handle, sizeof(cpu_set_t), &set))
	{
		return false;
	}
	return true;
}
