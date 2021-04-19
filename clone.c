#include"types.h"
#include"stat.h"
#include"user.h"
#include"fs.h"

void clone_fcn(void *arg1, void *arg2){
    printf(1, "Hello, I am Kushal\n");
    printf(1, "%d\n", (int)arg1);
    printf(1, "%d\n", (int)arg2);
    exit();
}

int main(int argc, char *argv[]){
    int a = 5;
    int b = 10;
    void *stack = malloc(4096);
    if(!stack){
        printf(1, "Memory alloction failed!\n");
        exit();
    }
    clone(&clone_fcn, (void*)a, (void*)b, stack);
    wait();
    exit();
}
