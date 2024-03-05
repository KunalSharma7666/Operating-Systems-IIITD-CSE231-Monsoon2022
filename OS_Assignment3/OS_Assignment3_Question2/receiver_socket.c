#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

        
#define ADDRESS     "Anything" 


int arr[55];
int main()
{

    for(int j=0;j<50;j++){
        arr[j] = j+1;
    }

    char c;
    FILE *fp;
    struct sockaddr_un saun;

    int sock;
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    saun.sun_family = AF_UNIX;

    strcpy(saun.sun_path, ADDRESS);

    int length;
    length = sizeof(saun.sun_family) + strlen(saun.sun_path);

    connect(sock, &saun, length);

    fp = fdopen(sock, "r");



    for (int i = 0; i < 50; i++) {
        printf("ID: %d String: ",i+1);
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);

            if (c == '\n')
            {
                sleep(1);
                break;
            }
                
        }
        if( i > 0 && (i+1)%5==0){

            send(sock, arr[i], sizeof(arr[i]), 0);
            sleep(1);
            printf("Sending ID: %d\n",i+1);
            
        }
    }

    close(sock);

    return 0;
}
