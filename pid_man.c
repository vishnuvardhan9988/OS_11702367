#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>


#define MIN_PID 100
#define MAX_PID 1000
#define NO_OF_PROCESS 16      //no of process/threads

int process_id[MAX_PID-MIN_PID]={0};

int allocate_processid(void){
    int i,flag=1;
    for(i=0; i<MAX_PID-MIN_PID; i++){
        if(process_id[i]==0){
            
            process_id[i]=1;
            flag=0;
            break;
        }
    }
    return flag?-1:i;
}
void release_processid(int id){
    process_id[id]=0;
}
void *threadRoutine(void *arg){
    int tid =  *(( int* )arg);
    
    
    int id = allocate_processid();


    if(id==-1){
        puts("No PID available.");
    }
    else{
        printf("Thread [%3d] PID [%3d] Allocated\n",tid,id+MIN_PID);
        //sleep for a random time between 1-10 seconds
        
        int r=1+rand()%30;
        
        printf("Thread [%3d] PID [%3d] Released after %d sec\n",tid,id+MIN_PID,r);
        release_processid(id);
    }
    pthread_exit(NULL);
}

int main(){
    int i;
    
    pthread_t process[NO_OF_PROCESS];
    srand(time(NULL));
    for(i=0; i<NO_OF_PROCESS; i++){
        if(pthread_create(&process[i],NULL,threadRoutine,(void*)&i))
            return -1*printf("Error in thread %d creation!!!\n",i);   
    }

    for(i=0; i<NO_OF_PROCESS; i++)
        pthread_join(process[i],NULL);
    
    return 0*printf("\nSUCCESSFUL EXIT\n");
}
