#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int test = 4;

int main() {
    int pid = fork();

    if(pid < 0) {
        perror("create process failed");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0) {
        printf("this is child process, pid = %d\n", pid);
        printf("child process: perform some functions..\n");
        sleep(3); //do some work, wait for parent to finish incrementing test value
        printf("child process: test = %d\n", test); //test = 4, parent & child process have different memory (except text section)
        sleep(3); //do some work, parent process have to wait for child process
        printf("child process: finished!\n");
    }

    if(pid > 0) {
        printf("this is parent process, pid = %d\n", pid); 
        printf("parent process: change value of test variable\n");
        for(int i = 0; i < 100; ++i) ++test;
        printf("parent process: test after change = %d\n", test);
        wait(NULL); //wait until child process finish
        printf("parent process: finished\n");
    }

    return 0;
}
