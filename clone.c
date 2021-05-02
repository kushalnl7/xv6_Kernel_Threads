#include"types.h"
#include"stat.h"
#include"user.h"
#include"fs.h"
#include"threads.h"

int global = 0;

int arr1[6][6] = {{1,2,3,2,1,7}, {5,6,8,4,5,3}, {7,4,2,1,5,1}, {9,8,4,5,4,5}, {7,8,4,2,3,7}, {5,4,6,9,8,6}};
int arr2[6][6] = {{5,4,6,9,8,6}, {7,1,2,3,5,1}, {2,8,6,4,1,7}, {8,6,5,3,7,3}, {4,6,5,1,3,8}, {7,4,2,1,5,1}};
int arr3[6][6];
int step = 0;

void matmul(void *arg1, void *arg2){
    // printf(1, "%s\n", (char*)arg1);
    int div = step++;
    if(div != 2){
        for(int i = div*(6/3); i < (div + 1)*(6/3); i++){
            for(int j = 0; j < 6; j++){
                int sum = 0;
                for(int k = 0; k < 6; k++){
                    sum += arr1[i][k]*arr2[k][j];
                }
                arr3[i][j] = sum;
            }
        }
    }
    else{
        for(int i = div*(6/3); i < 6; i++){
            for(int j = 0; j < 6; j++){
                int sum = 0;
                for(int k = 0; k < 6; k++){
                    sum += arr1[i][k]*arr2[k][j];
                }
                arr3[i][j] = sum;
            }
        }
    }
    exit();
}

// void F6(void *arg1, void *arg2){
//     exit();
// }

void F5(void *arg1, void *arg2){
    char *exec_arr[] = {"cat", "README"};
    int pid = fork();
    if(pid == 0){
        exec("cat", exec_arr);
        printf(1, "Inside child process\n");
    }
    else{
        printf(1, "Inside parent process\n");
        wait();
    }
    wait();
    exit();
}

void F4(void *arg1, void *arg2){
    printf(1, "%s\n", (char*)arg1);
    int ret = thread_kill(thread_gettid(), thread_gettgid(), 5);
    printf(1, "%d\n", ret);
    printf(1, "%d\n", (int)arg2);
    exit();
}

void F3(void *arg1, void *arg2){
    printf(1, "%s %d\n", (char*)arg1, (int)arg2);
    exit();
}

void F2(void *arg1, void *arg2){
    printf(1, "%s %d\n", (char*)arg1, (int)arg2);
    char a[100] = "This is F3 clone function called inside F2 clone function and my arg 2 is";
    int b = 5;
    int flag_count = 4;
    int *flags;
    flags = malloc(flag_count*sizeof(int));
    *(flags + CLONE_THREAD) = 0;
    *(flags + CLONE_PARENT) = 0;
    *(flags + CLONE_VM) = 1;
    *(flags + CLONE_FS) = 0;
    int pid = thread_create(&F3, (void*)a, (void*)b, (void*)flag_count, (void*)flags);
    thread_join(pid);
    exit();
}

void F1(void *arg1, void *arg2){
    printf(1, "%s %d\n", (char*)arg1, (int)arg2);
    exit();
}


int main(int argc, char *argv[]){

    char a[50] = "This is F1 clone function and my arg 2 is";
    char c[50] = "This is F2 clone function and my arg 2 is";
    char d[100] = "This is F4 clone function and I would not be able to print arg 2 as I will be killed";
    char e[100] = "This is F5 clone function and we are doing matrix multiplication here";
    int b = 10;
    int flag_count = 4;
    int *flags;
    flags = malloc(flag_count*sizeof(int));
    *(flags + CLONE_THREAD) = 0;
    *(flags + CLONE_PARENT) = 0;
    *(flags + CLONE_VM) = 1;
    *(flags + CLONE_FS) = 0;

    printf(1, "\n\n_________CLONE JOIN TESTING_________\n\n");
    int pid = thread_create(&F1, (void*)a, (void*)b, (void*)flag_count, (void*)flags);
    thread_join(pid);

    printf(1, "\n\n_________CLONE INSIDE CLONE WITH JOIN TESTING_________\n\n");
    pid = thread_create(&F2, (void*)c, (void*)b, (void*)flag_count, (void*)flags);
    thread_join(pid);

    printf(1, "\n\n_________CLONE KILL TESTING_________\n\n");
    pid = thread_create(&F4, (void*)d, (void*)b, (void*)flag_count, (void*)flags);
    thread_join(pid);

    printf(1, "\n\n_________FORK INSIDE CLONE TESTING_________\n\n");
    pid = thread_create(&F5, (void*)d, (void*)b, (void*)flag_count, (void*)flags);
    thread_join(pid);

    // printf(1, "\n\n_________EXEC INSIDE CLONE TESTING_________\n\n");
    // pid = thread_create(&F6, (void*)d, (void*)b, (void*)flag_count, (void*)flags);
    // thread_join(pid);
    
    printf(1, "\n\n_________MATRIX MULTIPLICATION USING CLONE TESTING_________\n\n");
    int pid_matmul[3];
    for (int i = 0; i < 3; i++){  
        pid_matmul[i] = thread_create(&matmul, (void*)e, (void*)b, (void*)flag_count, (void*)flags); 
    } 
    for (int i = 0; i < 3; i++){
        thread_join(pid_matmul[i]);
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            printf(1, "%d ", arr3[i][j]);
        }
        printf(1, "\n");
    }

    printf(1, "\n\n_________MULTIPLE CLONES IN FOR LOOP TESTING_________\n\n");
    int pids[100];
    for(int i = 0; i < 60; i++){
        pids[i] = thread_create(&F1, (void*)a, (void*)b, (void*)flag_count, (void*)flags);
    }
    for(int i = 0; i < 60; i++){
        join(pids[i]);
    }

 


    // wait();
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
