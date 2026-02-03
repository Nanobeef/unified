Mutex create_mutex()
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

Cond create_cond()
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

void* empty_thread_work(Thread *thread)
{
	printf("empty work\n");
	return NULL;
}

void *thread_wrapper(void *args)
{
	Thread *thread = args;
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
		else
			ret = empty_thread_work(thread);
			
		if(ret != NULL)
		{
			break;			
		}

	}
	printf("return\n");
	return NULL;
}

Thread *allocate_thread(Arena *arena, u64 scratch_arena_size)
{
	Thread *thread = arena_push(arena, true, sizeof(Thread));
	for(u32 i = 0; i < 2; i++)
	{
		thread->scratch_arenas[i] = init_arena(arena_push(arena, 0, scratch_arena_size), scratch_arena_size);
	}
	thread->working_semaphore = create_semaphore(0);
	thread->idling_semaphore = create_semaphore(0);
	thread->mutex = create_mutex();
	thread->index = 0;
	return thread;
}

Thread *create_thread(Arena *arena, u64 scratch_arena_size, u64 stack_size)
{
	Thread *thread = allocate_thread(arena, scratch_arena_size);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, stack_size);

	if(pthread_create(&thread->handle, &attr, thread_wrapper, (void*)thread))
	{
		printf("There was an error while calling pthread_create(...)\n");
	}
	pthread_attr_destroy(&attr);
	return thread;
}

void wait_for_thread_idle(Thread *thread)
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
	atomic_store(&thread->function, (PFN_Void*)function);
	unlock_mutex(&thread->mutex);
	return false;
}
