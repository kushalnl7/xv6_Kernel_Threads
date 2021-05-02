#define CLONE_THREAD 0
#define CLONE_PARENT 1
#define CLONE_VM 2
#define CLONE_FS 3
#define CLONE_FILES 4

struct thread{
    int thread_id;
    char *stack;
};

int thread_create(void(*)(void*, void*), void*, void*, void*, void*);
int thread_join(int);
int thread_kill(int, int, int);
int thread_gettid();
int thread_getppid();
int thread_gettgid();