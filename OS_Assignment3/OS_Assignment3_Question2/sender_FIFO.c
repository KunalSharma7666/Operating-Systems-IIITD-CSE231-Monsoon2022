#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>

int main(int argc, char *argv[])
{
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_REALTIME, &start);
    char buf[22];
    char arr[50][20] = {{0}};

    char FIFO1[] = "FIFO1";
    char FIFO2[] = "FIFO2";

    int a = 0;
    while (a < 50)
    {
        int b = 0;
        while (b < 15)
        {
            arr[a][b] = 'a' + rand() % 26;
            b++;
        }
        arr[a][15] = a + 1;
        a++;
    }
    
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    for (int p = 0; p < 10; p++)
    {
        int fd1 = 0;
        fd1 = open(FIFO1, O_WRONLY);
        int ret = 0;
        for (int i = 0; i < 5; i++)
        {
            ret = write(fd1, arr[p * 5 + i], strlen(arr[p]) + 1);
            sleep(1);
        }

        ret = close(fd1);
        int fd2 = 0;
        fd2 = open(FIFO2, O_RDONLY);
        ret = read(fd2, buf, sizeof(buf));
        printf("Highest ID: %d\n", (int)buf[15]);
        close(fd2);
    }
    unlink(FIFO1);
    unlink(FIFO2);
    clock_gettime(CLOCK_REALTIME, &finish);
    printf("\n");
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time Taken: %lf\n", (double)elapsed);

    return 0;
}