#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t fork1;
pthread_mutex_t fork2;
pthread_mutex_t fork3;
pthread_mutex_t fork4;
pthread_mutex_t fork5;

void *phil(int a){
    while(1){
        if(a==1){
            pthread_mutex_lock(&fork2);
            pthread_mutex_lock(&fork1);
            printf("Philosopher 1 is eating with fork1 and fork2.\n");
            pthread_mutex_unlock(&fork2);
            pthread_mutex_unlock(&fork1);
            printf("Philosopher 1 is thinking.\n");
        }
        if(a==2){
            pthread_mutex_lock(&fork3);
            pthread_mutex_lock(&fork2);
            printf("Philosopher 2 is eating with fork2 and fork3.\n");
            pthread_mutex_unlock(&fork3);
            pthread_mutex_unlock(&fork2);
            printf("Philosopher 2 is thinking.\n");
        }
        if(a==3){
            pthread_mutex_lock(&fork4);
            pthread_mutex_lock(&fork3);
            printf("Philosopher 3 is eating with fork3 and fork4.\n");
            pthread_mutex_unlock(&fork4);
            pthread_mutex_unlock(&fork3);
            printf("Philosopher 3 is thinking.\n");
        }
        if(a==4){
            pthread_mutex_lock(&fork5);
            pthread_mutex_lock(&fork4);
            printf("Philosopher 4 is eating with fork4 and fork5.\n");
            pthread_mutex_unlock(&fork5);
            pthread_mutex_unlock(&fork4);
            printf("Philosopher 4 is thinking.\n");
        }
        if(a==5){       // breaking the deadlock
            pthread_mutex_lock(&fork5);
            pthread_mutex_lock(&fork1);
            printf("Philosopher 5 is eating with fork1 and fork5.\n");
            pthread_mutex_unlock(&fork5);
            pthread_mutex_unlock(&fork1);
            printf("Philosopher 5 is thinking.\n");
        }
    }
}

int main(){
    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;
    pthread_t th5;

    pthread_mutex_init(&fork1,NULL);
    pthread_mutex_init(&fork2,NULL);
    pthread_mutex_init(&fork3,NULL);
    pthread_mutex_init(&fork4,NULL);
    pthread_mutex_init(&fork5,NULL);

    pthread_create(&th1,NULL,(void *)phil,1);
    pthread_create(&th2,NULL,(void *)phil,2);
    pthread_create(&th3,NULL,(void *)phil,3);
    pthread_create(&th4,NULL,(void *)phil,4);
    pthread_create(&th5,NULL,(void *)phil,5);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    pthread_join(th5,NULL);

    return 0;
}
