#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    char buf[22];
    char FIFO1[] = "FIFO1";
    char FIFO2[] = "FIFO2";

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    for (int p = 1; p < 51; p++)
    {
        int fd1 = 0;
        fd1 = open(FIFO1, O_RDONLY);

        int ret = 0;
        ret = read(fd1, buf, sizeof(buf));

        printf("string: ");
        int i = 0;

        while (i <= 14)
        {
            printf("%c", buf[i]);
            i++;
        }

        printf(" ID: %d\n", (int)buf[15]);
        if (p % 5 == 0)
        {

            printf("\n");
        }
        close(fd1);

        if (p % 5 == 0)
        {
            int fd2 = 0;
            fd2 = open(FIFO2, O_WRONLY);
            ret = write(fd2, buf, strlen(buf) + 1);
            ret = close(fd2);
        }
    }
    return 0;
}
