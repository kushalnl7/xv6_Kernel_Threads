#include"types.h"
#include"stat.h"
#include"user.h"
#include"fs.h"
#define CLONE_THREAD 0
#define CLONE_PARENT 1
#define CLONE_VM 2

void clone_fcn(void *arg1, void *arg2){
    printf(1, "Hello, I am Kushal\n");
    printf(1, "%d\n", (int)arg1);
    printf(1, "%d\n", (int)arg2);
    // printf(1, "%d\n", gettid());
    // printf(1, "%d\n", getppid());
    exit();
}

int main(int argc, char *argv[]){

    // int pid = fork();
    // if(pid < 0){
    //     printf(1, "Fork failed!\n");
    // }
    // else if(pid == 0){
    //     printf(1, "%d\n", gettid());
    //     printf(1, "%d\n", getppid());
    // }
    // else{
    //     printf(1, "%d\n", pid);
    //     wait();
    // }

    int a = 5;
    int b = 10;
    void *stack;
    int flag_count = 3;
    int *flags;
    flags = malloc(3*sizeof(int));
    *(flags + CLONE_THREAD) = 0;
    *(flags + CLONE_PARENT) = 0;
    *(flags + CLONE_VM) = 1;

    stack = malloc(4096);
    clone(&clone_fcn, (void*)a, (void*)b, stack, (void*)flag_count, (void*)flags);
    join(stack);
    // printf(1, "%d\n", pid);
    
    // void *stack[5];
    // for(int i = 0; i < 5; i++){
    //     stack[i] = malloc(4096);
    //     if(!stack[i]){
    //         printf(1, "Memory alloction failed!\n");
    //         exit();
    //     }
    //     int pid = clone(&clone_fcn, (void*)a, (void*)b, stack);
    //     printf(1, "%d\n", pid);
    //     printf(1, "%d\n", gettid());
    //     printf(1, "%d\n", getppid());
    //     join(stack[i]);
    //     free(stack[i]);
    // }
    // for(int i = 0; i < 5; i++){
    //     join(stack[i]);
    // }
    // wait();
    exit();
}
