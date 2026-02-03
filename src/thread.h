
#define atomic _Atomic

typedef struct{
	pthread_mutex_t handle;
}Mutex;

Mutex create_mutex();
void destroy_mutex(Mutex mutex);
void lock_mutex(Mutex *mutex);
void unlock_mutex(Mutex *mutex);
typedef struct{
	pthread_cond_t handle;
	b32 should_signal;
}Cond;

Cond create_cond();
void destroy_cond(Cond cond);
void broadcast_cond(Cond *cond);
void signal_cond(Cond *cond);
void wait_cond(Cond *cond, Mutex *mutex);

typedef struct{
	atomic u64 value;	
	pthread_cond_t handle;
}Semaphore;

Semaphore create_semaphore(u64 value);
void destroy_semaphore(Semaphore semaphore);
b32 binary_signal_semaphore(Semaphore *semaphore);
void binary_reset_semaphore(Semaphore *semaphore);
void binary_wait_semaphore(Semaphore *semaphore, Mutex *mutex);

typedef void*(PFN_Void)(void*);

typedef struct{
	pthread_t handle;
	u64 index;
	Arena *scratch_arenas[2];	

	Semaphore working_semaphore;
	Semaphore idling_semaphore;
	Mutex mutex;
	atomic PFN_Void *function;
}Thread;

typedef void*(PFN_Thread)(Thread*);

Thread *allocate_thread(Arena *arena, u64 scratch_arena_size);
Thread *create_thread(Arena *arena, u64 scratch_arena_size, u64 stack_size);
void wait_for_thread_idle(Thread *thread);
b32 begin_thread_work(Thread *thread, PFN_Thread *function);
