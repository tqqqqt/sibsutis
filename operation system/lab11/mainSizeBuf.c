#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>

int sizeBufer=0, turns=0;
int *buffer;
int count=0;

int ConvertToInt(char mas[]){
    int temp=0, i=0;
    for(i;i<strlen(mas);i++){
        temp=temp*10+(mas[i]-'0');
    }
    return temp;
}

pthread_mutex_t Mutex;
sem_t buffer_count;

void* consumer(void*);

int main(int argK, char* argV[]){
    if(argK!=4) return 0;
    sizeBufer=ConvertToInt(argV[1]);
    turns=ConvertToInt(argV[3]);
    buffer=malloc(sizeof(int)*sizeBufer);
    sem_init(&buffer_count,0,0);
    int i=0, error=0, consumerK=ConvertToInt(argV[2]);;    
    for(i;i<sizeBufer;i++) buffer[i]=-1;
    pthread_t consumer_id[consumerK];
    pthread_mutex_init(&Mutex,NULL);
    for(i=0;i<consumerK;i++){
	    error=pthread_create(&consumer_id[i],NULL,&consumer,NULL);
		if(error!=0){
			printf("%s",strerror(error));
			return -1;
	    }
	}
    
    int in=0, j=0;//, count=0;
    i=1;   
    while(1){
        if(i++>(turns*consumerK)) break;
        while(count==sizeBufer);
        sleep(0.5);
        pthread_mutex_lock(&Mutex);
        if(buffer[in]==-1){
            buffer[in]=in;
            count++;
            printf("Produced->%d ",in);
            sem_post(&buffer_count);
        }
        else i--;
        printf("\n{");
        for(j=0;j<sizeBufer;j++) printf("%d ",buffer[j]);
        printf("}\n");
        pthread_mutex_unlock(&Mutex);
        in=(in+1)%sizeBufer;
    }

	for(i=0;i<consumerK;i++){
    	pthread_join(consumer_id[i],NULL);
    }
    printf("\n");
    return 0;
}

void* consumer(void* params){
    int out=0, i=1;    
    while(1){
        if(i++>turns) break;
        while(count==0);
        sleep(0.5);
        sem_wait(&buffer_count);
        pthread_mutex_lock(&Mutex);
        if(buffer[out]!=-1){
            buffer[out]=-1;
            count--;
            printf("[%d]Consumer->%d ",i,out);
        }
        pthread_mutex_unlock(&Mutex);
        out=(out+1)%sizeBufer;
    }
}
