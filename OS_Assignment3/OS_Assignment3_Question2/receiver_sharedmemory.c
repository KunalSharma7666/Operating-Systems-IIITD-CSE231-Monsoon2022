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
//int characterArray1 [100][10] = {{0}};

void receiver(int i){
    //char **index;
    void *SharedMemory;
    int shmid;
    shmid = shmget((key_t)2345, sizeof(*SharedMemory), 0666);
    SharedMemory = shmat(shmid,NULL,0);
    //index = (char **)SharedMemory;
    char buffer[1000];
    strcpy(buffer,SharedMemory);
    // for(int i = 0; i<8; i++){
        for (int j = 0; j < 6; j++)
        {
            //printf("%s",buffer[(6*i)+j]);
            printf("%c",buffer[j]);
            
            
            // printf("%s", buffer);
            
        }

        if(i>=30){
            printf(" ID:%d",i+1);
        }
        else{
            printf(" ID:%d",(buffer[6]) - 'a');
        }
        printf("\n");
        shmdt(SharedMemory);
        
        
        
        //buffer = (char *)(&index[i+1]);
        
        //printf("%s", buffer);
        //printf("%s\n", (char *)buffer);
    //}
    //printf("%s\n", (char *)SharedMemory);

}

void sender(int i){
    void *SharedMemory;
    int shmid;
    //char **index;
    shmid = shmget((key_t)2345, sizeof(*SharedMemory) , 0666|IPC_CREAT);
    SharedMemory = shmat(shmid,NULL,0);
    
        // char a[1];
        // char m = 'a' + (i+1);
        // a[0] = m;
        
        SharedMemory = i+1;

        // if(i>=30){
        //     printf("Sending ID is: %d\n", i+1);
        // }
        // else{
            printf("Sending ID is: %d\n", (int *)SharedMemory);
        // }
        
    
    shmdt(SharedMemory);
    

}
int main(){
    for(int i =0;i<50;i++){
         receiver(i);
         sleep(1);
        if( i > 0 && (i+1)%5==0){

         sender(i);
         sleep(1);

        }
    }
   
}