#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sched.h>
#include <sys/wait.h>

struct timespec start1, end1, delta;
struct timespec start2, end2, delta2;
struct timespec start3, end3, delta3;

int main()
{
    int pid1 = fork();
    int pid2 = fork();
    int pid3 = fork();

    if (pid1 > 0 && pid2 > 0 && pid3 == 0)
    {
        clock_gettime(CLOCK_REALTIME, &start1);
        printf("I am child 1 \n");
        execl("/bin/bash", "sh", "bash1.sh", NULL);
        printf("after execl \n");

        // clock_gettime(CLOCK_REALTIME, &end1);
        // double seconds = (end.tv_sec - start.tv_sec);
        // double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        // printf("time taken by Process 1 : %f seconds \n", seconds + nanoseconds);
    }

    else if (pid1 > 0 && pid2 == 0 && pid3 > 0)
    {
        struct timespec start2, end2, delta2;
        clock_gettime(CLOCK_REALTIME, &start2);
        printf("I am child 2\n");
        execl("/bin/bash", "sh", "bash2.sh", NULL);
        // clock_gettime(CLOCK_REALTIME, &end);
        // double seconds = (end.tv_sec - start.tv_sec);
        // double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        // printf("time taken by Process 2 : %f seconds \n", seconds + nanoseconds);
    }

    else if (pid1 == 0 && pid2 > 0 && pid3 > 0)
    {
        struct timespec start3, end3, delta3;
        clock_gettime(CLOCK_REALTIME, &start3);
        printf("I am child 3\n");
        execl("/bin/bash", "sh", "bash3.sh", NULL);
        // clock_gettime(CLOCK_REALTIME, &end);
        // double seconds = (end.tv_sec - start.tv_sec);
        // double nanoseconds = (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        // printf("time taken by Process 3 : %f seconds \n", seconds + nanoseconds);
    }
    int i = 0;
    while (i != 3)
    {
        if (waitpid(-1, NULL, 0) == pid1)
        {
            printf("loop 1 \n");
            clock_gettime(CLOCK_REALTIME, &end1);
            double seconds = (end1.tv_sec - start1.tv_sec);
            double nanoseconds = (end1.tv_nsec - start1.tv_nsec) / 1000000000.0;
            printf("time taken by Process 1 : %f seconds \n", seconds + nanoseconds);
            i++;
        }

        else if (waitpid(-1, NULL, 0) == pid2)
        {
            printf("loop 2 \n");
            clock_gettime(CLOCK_REALTIME, &end2);
            double seconds = (end2.tv_sec - start2.tv_sec);
            double nanoseconds = (end2.tv_nsec - start2.tv_nsec) / 1000000000.0;
            printf("time taken by Process 2 : %f seconds \n", seconds + nanoseconds);
            i++;
        }

        else if (waitpid(-1, NULL, 0) == pid3)
        {
            printf("loop 3 \n");
            clock_gettime(CLOCK_REALTIME, &end3);
            double seconds = (end3.tv_sec - start3.tv_sec);
            double nanoseconds = (end3.tv_nsec - start3.tv_nsec) / 1000000000.0;
            printf("time taken by Process 3 : %f seconds \n", seconds + nanoseconds);
            i++;
        }
    }
    return 0;
}