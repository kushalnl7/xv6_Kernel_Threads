#include"threads.h"
#include"types.h"
#include"stat.h"
#include"user.h"
#include"fs.h"

struct thread threads[1000];
int th_index = 0;

int thread_create(void(*clone_fcn)(void*, void*), void* a, void* b, void* flag_count, void* flags){

    void *stack;
    stack = malloc(4096);
    int pid = clone((void*)clone_fcn, (void*)a, (void*)b, stack, (void*)flag_count, (void*)flags);
    if(pid < 0){
        // printf(1, "Error: Clone Failed\n");
        return pid;
    }
    if(th_index < 1000){
        threads[th_index].thread_id = pid;
        threads[th_index].stack = stack;
        th_index++;
    }
    else{
        printf(1, "Error: No space in threads array\n");
        return -1;
    }
    return pid;
}

int thread_join(int tid){
    int pid = join(tid);
    int j;
    for(j = 0; j < th_index; j++){
        if(threads[j].thread_id == pid){
            free(threads[j].stack);
            break;
        }
    }
    for(int k = j; k < th_index - 1; k++){
        threads[k].thread_id = threads[k+1].thread_id;
        threads[k].stack = threads[k+1].stack; 
    }
    th_index--;

    return pid;
}

int thread_kill(int tid, int tgid, int signal){
    int ret = tgkill(tid, tgid, signal);
    return ret;
}

int thread_gettid(){
    return gettid();
}

int thread_getppid(){
    return getppid();
}

int thread_gettgid(){
    return gettgid();
}
