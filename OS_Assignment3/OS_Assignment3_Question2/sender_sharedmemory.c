#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>

char characterArray [100][10] = {{0}};
//char characterArray1 [100][10] = {{0}};
// char IntegerArray[50];
void sender(int i){
    void *SharedMemory;
    int shmid;
    //char **index;
    shmid = shmget((key_t)2345, sizeof(*SharedMemory) , 0666|IPC_CREAT);
    SharedMemory = shmat(shmid,NULL,0);
    // index = (char **)SharedMemory;
    // char *buffer;
    // for(int i = 0; i<5; i++){

        // buffer = (char *)(&index[i+1]);
    
    strcpy(SharedMemory, characterArray[i]);
    shmdt(SharedMemory);
    //strcpy(SharedMemory, &IntegerArray[i]);
    // strcpy(SharedMemory, characterArray[i]);
        // if(i%5 == 0){
        //    sleep(1);
        // }
    // }

    // printf("%s\n", (char *)SharedMemory);
}


void receiver(int i){

    void *SharedMemory;
    int shmid;
    shmid = shmget((key_t)2345, 1024, 0666);
    SharedMemory = shmat(shmid,NULL,0);
    // char buffer[100];
    // strcpy(buffer,SharedMemory1);
    
    // if(i>=30){
    //     printf("Received ID is: %d\n", i+1);
    
    // }
    //else{

    printf("Received ID is: %d\n", ((int *)SharedMemory));
    //}
    // printf("Received ID is: %d\n", i+1);
    
    // if( i >0 && (i+1)%5==0){

    //     printf("Received ID is: %d\n", (buffer[0]) - 'a');
    // }
    shmdt(SharedMemory);
    


}
int main(){
    for (int x = 0; x < 50; x++){
        for (int i = 0; i < 6; i++){
            characterArray[x][i] = 'a' + (rand() % 25);
            if(i==5){
                char m = 'a' + (x+1);
                characterArray[x][6] = m;
            }
        }
    }

    //printf("%d\n",(characterArray[1][6]) - 'a');

    // for(int j=0;j<50;j++){
    //     printf("%s\n",characterArray[j]);
    //     printf("%d\n",(characterArray[j][6]) - 'a');
    // }

    for(int i=0;i<50;i++){
        
        sender(i);
        sleep(1);
        if(i>0 && (i+1)%5==0){
            
            receiver(i);
            sleep(1);
        }
    }
}