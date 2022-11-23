#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void countA()
{
    long int i;
    for (i = 0; i < 4294967296; i++)
    {
        continue;
    }
    printf("A\n");
}
void countB()
{
    long int i;
    for (i = 0; i < 4294967296; i++)
    {
        continue;
    }
    printf("B\n");
}
void countC()
{
    long int i;
    for (i = 0; i < 4294967296; i++)
    {
        continue;
    }
    printf("C\n");
}

void *thread_func_fifo(void *arg)
{
    int policy = SCHED_FIFO;
    struct sched_param param;
    int s;

    param.sched_priority = 20;
    s = pthread_setschedparam(pthread_self(), policy, &param);
    printf("thread_func_fifo: policy = %d, priority = %d\n", policy, param.sched_priority);

    struct timespec start, end, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    clock_gettime(CLOCK_REALTIME, &end);
    double seconds = (end.tv_sec - start.tv_sec);
    double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time taken by FIFO %f seconds \n", seconds + nanoseconds);
}

void *thread_func_rr(void *arg)
{
    int policy = SCHED_RR;
    struct sched_param param;
    int s;

    param.sched_priority = 20;
    s = pthread_setschedparam(pthread_self(), policy, &param);
    printf("thread_func_rr: policy = %d, priority = %d\n", policy, param.sched_priority);

    struct timespec start, end, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    clock_gettime(CLOCK_REALTIME, &end);
    double seconds = (end.tv_sec - start.tv_sec);
    double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time taken by RR %f seconds \n", seconds + nanoseconds);
}
void *thread_func_other(void *arg)
{
    int policy = SCHED_OTHER;
    struct sched_param param;
    int s;

    param.sched_priority = 0;
    s = pthread_setschedparam(pthread_self(), policy, &param);
    printf("thread_func_other: policy = %d, priority = %d\n", policy, param.sched_priority);

    struct timespec start, end, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    clock_gettime(CLOCK_REALTIME, &end);

    double seconds = (end.tv_sec - start.tv_sec);
    double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time taken by OTHER %f seconds \n", seconds + nanoseconds);
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2, thread3;
    int s;
    s = pthread_create(&thread1, NULL, &thread_func_fifo, NULL);
    s = pthread_create(&thread2, NULL, &thread_func_rr, NULL);
    s = pthread_create(&thread3, NULL, &thread_func_other, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
}
