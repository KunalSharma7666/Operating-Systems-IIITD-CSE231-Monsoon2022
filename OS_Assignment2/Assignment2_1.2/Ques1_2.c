#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sched.h>

#define BILLION 1000000000L

int main()
{
    int status;
    pid_t pid[3];
    struct timespec start[3], end[3];
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            clock_gettime(CLOCK_REALTIME, &start[i]);
            pid[i] = fork();
            if (pid[i] < 0)
            {
                perror("Error : ");
            }
            else if (pid[i] == 0)
            {
                struct sched_param param;
                param.sched_priority = 0;
                if (!sched_setscheduler(getpid(), SCHED_OTHER, &param))
                {
                    execl("./bash1.sh", NULL);
                }
                else
                {
                    perror("Error : ");
                }
                exit(0);
            } 
        }
        else if (i == 1)
        {
            clock_gettime(CLOCK_REALTIME, &start[i]);
            pid[i] = fork();
            if (pid[i] < 0)
            {
                perror("Error : ");
            }
            else if (pid[i] == 0)
            {
                struct sched_param param;
                param.sched_priority = 60;
                if (!sched_setscheduler(getpid(), SCHED_RR, &param))
                {
                    execl("./bash2.sh", NULL);
                }
                else
                {
                    perror("Error : ");
                }
                exit(0);
            } 
        }
        else
        {
            clock_gettime(CLOCK_REALTIME, &start[i]);
            pid[i] = fork();
            if (pid[i] < 0)
            {
                perror("Error : ");
            }
            else if (pid[i] == 0)
            {
                struct sched_param param;
                param.sched_priority = 60;
                if (!sched_setscheduler(getpid(), SCHED_FIFO, &param))
                {
                    execl("./bash3.sh", NULL);
                }
                else
                {
                    perror("Error : ");
                }
                exit(0);
            } 
        }
    }

    int a = 0, b = 0, c = 0;

    while (true)
    {
        if (waitpid(pid[0], &status, WNOHANG) > 0)
        {
            clock_gettime(CLOCK_REALTIME, &end[0]);
            a++;
        }
        if (waitpid(pid[1], &status, WNOHANG) > 0)
        {
            clock_gettime(CLOCK_REALTIME, &end[1]);
            b++;
        }
        if (waitpid(pid[2], &status, WNOHANG) > 0)
        {
            clock_gettime(CLOCK_REALTIME, &end[2]);
            c++;
        }
        if (a == 1 && b == 1 && c == 1)
        {
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        double time = (end[i].tv_sec - start[i].tv_sec) + (double)(end[i].tv_nsec - start[i].tv_nsec) / (double)BILLION;
        printf("time %d: %lf\n", i, time);
    }
}