#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<sched.h>



void * CountA(void *arg){
    struct sched_param param;
    int ret;
    long long count=0;
    struct timespec start1, finish1;
    double elapsed1;
    param.sched_priority = 0;
    ret = pthread_setschedparam(pthread_self(),SCHED_OTHER,&param);
    if(ret==0){
        clock_gettime(CLOCK_REALTIME, &start1);
        while(count!=4294967296){
           count++;
        }
        clock_gettime(CLOCK_REALTIME, &finish1);
    }
    else{
        printf("Error");
    }
    elapsed1 = (finish1.tv_sec - start1.tv_sec);
    elapsed1 += (finish1.tv_nsec - start1.tv_nsec) / 1000000000.0;
    printf("OTHER: %lf\n", (double)elapsed1);
   
}



void * CountB(void *arg){

    struct sched_param param;
    struct timespec start2, finish2;
    double elapsed2;
    int ret;
    long long count=0;
    param.sched_priority = 21;
    ret = pthread_setschedparam(pthread_self(),SCHED_RR,&param);
    
    if(ret==0){
        clock_gettime(CLOCK_REALTIME, &start2);
        while(count!=4294967296){
            
            count++;
        }
        clock_gettime(CLOCK_REALTIME, &finish2);
    }
    else{
        printf("Error");
    }
    elapsed2 = (finish2.tv_sec - start2.tv_sec);
    elapsed2 += (finish2.tv_nsec - start2.tv_nsec) / 1000000000.0;
    printf("RR: %lf\n", (double)elapsed2);
    
}


void * CountC(void *arg){

    struct sched_param param;
    struct timespec start3, finish3;
    double elapsed3;
    int ret;
    long long count=0;
    param.sched_priority = 20;
    ret = pthread_setschedparam(pthread_self(),SCHED_FIFO,&param);
    if(ret==0){
        clock_gettime(CLOCK_REALTIME, &start3);
        while(count!=4294967296){
           
            count++;
        }
        clock_gettime(CLOCK_REALTIME, &finish3);
    }
    else{
        
        printf("Error");
    }
    elapsed3 = (finish3.tv_sec - start3.tv_sec);
    elapsed3 += (finish3.tv_nsec - start3.tv_nsec) / 1000000000.0;
    printf("FIFO: %lf\n", (double)elapsed3);

}


int main(int argc, char **argv){

    pthread_t pid1;
    pthread_t pid2;
    pthread_t pid3;
    
  
    pthread_create(&pid1, NULL, CountA, NULL);
    
    pthread_create(&pid2, NULL, CountB, NULL);
    
    pthread_create(&pid3, NULL, CountC, NULL);

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);
    pthread_join(pid3, NULL);

}
