#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>
#include <errno.h>

int priorityF = 1;
int priorityR = 1;
int priorityO = 0;

double resultA[5];
double resultB[5];
double resultC[5];

void countA()
{
    long int count = 0;
    for (long int i = 0; i < 4294967296; i++)
    {
        count++;
    }
    printf("thread id for A is = %ld \n", pthread_self());
}

void countB()
{
    long int count = 0;
    for (long int i = 0; i < 4294967296; i++)
    {
        count++;
    }
    printf("thread id for B is = %ld \n", pthread_self());
}
void countC()
{
    long int count = 0;
    for (long int i = 0; i < 4294967296; i++)
    {
        count++;
    }
    printf("thread id for C is = %ld \n", pthread_self());
}

void *ThreadA()
{
    struct sched_param a;
    a.sched_priority = priorityO;
    pthread_t ida = pthread_self();
    if (setpriority(PRIO_PROCESS, 0, priorityO) == -1)
    {
        if (pthread_setschedparam(ida, SCHED_OTHER, &a) != 0)
        {
            printf("Error setting priority for OTHER ");
        }
    }
    else
    {
        printf("a working \n");
    }
    struct timespec start, end, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    clock_gettime(CLOCK_REALTIME, &end);
    double seconds = (end.tv_sec - start.tv_sec);
    double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time taken by OTHER[%d] %f seconds \n", priorityO, seconds + nanoseconds);
}

void *ThreadB()
{
    struct sched_param b;
    pthread_t idb = pthread_self();
    b.sched_priority = priorityR;
    if (pthread_setschedparam(idb, SCHED_RR, &b) != 0)
    {
        printf("error in B\n");
    }
    else
    {
        printf("b working \n");
    }
    struct timespec start, end, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    clock_gettime(CLOCK_REALTIME, &end);
    double seconds = (end.tv_sec - start.tv_sec);
    double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time taken by RR[%d] %f seconds \n", priorityR, seconds + nanoseconds);
}

void *ThreadC()
{
    pthread_t idc = pthread_self();
    struct sched_param c;
    c.sched_priority = priorityF;
    if (pthread_setschedparam(idc, SCHED_FIFO, &c) != 0)
    {
        printf("error in C\n");
    }
    else
    {
        printf("c working \n");
    }
    struct timespec start, end, diff;
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    clock_gettime(CLOCK_REALTIME, &end);
    double seconds = (end.tv_sec - start.tv_sec);
    double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("time taken by FIFO[%d] %f seconds \n", priorityF, seconds + nanoseconds);
}

int main(int argc, char *argv[])
{
    // take priority from command line
    if (argc == 4)
    {
        priorityF = atoi(argv[1]);
        priorityR = atoi(argv[2]);
        priorityO = atoi(argv[3]);
    }

    pthread_t ThrA, ThrB, ThrC;

    pthread_create(&ThrB, NULL, ThreadB, NULL);
    pthread_create(&ThrC, NULL, ThreadC, NULL);
    pthread_create(&ThrA, NULL, ThreadA, NULL);

    pthread_join(ThrB, NULL);
    pthread_join(ThrC, NULL);
    pthread_join(ThrA, NULL);

    printf("\n");

    return 0;
}