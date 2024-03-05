#include <stdio.h>
#include <sys/syscall.h>
// #include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define Kernel_2d_Memcpy 451

int main(){

    float source[2][5] = {{1.1,2.1,3.1,4.1,5.1},
                    {6.1,7.1,8.1,9.1,10.1}};

    float dest[2][5];
    long s;
    s = syscall(Kernel_2d_Memcpy, source, dest, 2, 5);

    if (s != EFAULT)
    {
        printf("Successfully invoked\n");
    }

    return 0;


}