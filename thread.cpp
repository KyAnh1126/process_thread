#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
#include <time.h>

#define N 20
#define THREAD_NUM 3

//struct store thread id, start position and end position of array
typedef struct {
    int tid;
    int tstart;
    int tend;
} pthread_data;

int array[N];
pthread_t threads[THREAD_NUM];
pthread_data data[THREAD_NUM];
int pthread_sum[THREAD_NUM];

//this function is registered by a thread and calculate the sum of array from start to end position
void* solve(void* data) {
    pthread_data* tdata = (pthread_data*)data;

    //get data
    int id = tdata->tid;
    int start = tdata->tstart;
    int end = tdata->tend;
    int sum = 0;

    printf("thread tid = %d, tstart = %d, tend = %d is solving..\n", id, start, end);

    //calculate sum of array from start to end
    for(int i = start; i <= end; ++i) {
        sum += array[i];
    }

    printf("thread tid = %d, with sum = %d\n", id, sum);
    pthread_sum[id] = sum; //assign calculated sum to pthread_sum array

    printf("thread tid = %d finished\n", id);
}

int main() {
    srand(time(NULL));
    for(int i = 0; i < N; ++i) {
        array[i] = rand() % 100; //random element of array
    }
    printf("array:\n");
    for(int i = 0; i < N; ++i) {
        printf("%d ", array[i]);
    } printf("\n");

    int start, end = -1;

    for(int i = 0; i < THREAD_NUM; ++i) {
        start = end + 1; //start position, calculated by the end of the previous thread 
        end = start + N / 3; //ensure all threads calculate same number of element in array 
        if(i == THREAD_NUM - 1) end = N - 1; //if last thread, end must be N - 1

        //assign value to struct data 
        data[i].tid = i;
        data[i].tstart = start;
        data[i].tend = end;
        
        //create thread and assign to thread[i], thread[i] perform solve() function, argument passed to solve() function is data[i]
        pthread_create(&threads[i], NULL, solve, &data[i]);
    }

    //pthread_join: this main thread must wait until threads[i] finished
    for(int i = 0; i < THREAD_NUM; ++i) {
        pthread_join(threads[i], NULL);
    }

    //calculate total
    int total = 0;
    for(int i = 0; i < THREAD_NUM; ++i) {
        total += pthread_sum[i];
    }

    printf("total (multi-thread) = %d\n", total);

    //compare total calculated by multi-thread to single-thread
    total = 0;
    for(int i = 0; i < N; ++i) {
        total += array[i];
    }

    printf("total (single-thread) = %d\n", total);
}