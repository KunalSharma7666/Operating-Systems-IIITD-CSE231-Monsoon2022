#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

     
#define ADDRESS     "Anything"  


char arr[55][20] = {{0}};


int main()
{

    int a = 0;
    while (a < 50)
    {
        int b = 0;
        while (b < 15)
        {
            arr[a][b] = 'a' + rand() % 26;
            b++;
        }
        arr[a][15] = '\n';
        a++;
    }

    int c;
    FILE *fp;

    
    struct sockaddr_un saun, fsaun;

    int sock;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, ADDRESS);

    unlink(ADDRESS);
    int length;
    length = sizeof(saun.sun_family) + strlen(saun.sun_path);

    bind(sock, &saun, length);

    listen(sock, 60);

    int acc;

    int fromlen;
    acc = accept(sock, &fsaun, &fromlen);

    fp = fdopen(acc, "r");

    for (int i = 0; i < 50; i++){
        send(acc, arr[i], strlen(arr[i]), 0);
        sleep(1);
        if(i > 0 && (i+1)%5==0){
            recv(sock, c, 1024, 0);
            sleep(1);
            printf("Recevied ID: %d\n",c);
            
        }
    }

    close(sock);

    return 0;
}