#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<semaphore.h>

struct mas{
    struct mas* next;
    int data;
};
struct mas *buffer=NULL;

void* consumer(void*);

pthread_mutex_t Mutex=PTHREAD_MUTEX_INITIALIZER;

sem_t buffer_size;

int ConvertToInt(char mas[]){
	int i=0,temp=0;
	for(i;i<strlen(mas);i++){
		temp=temp*10+(mas[i]-'0');
	}
	return temp;
}

int main(int argK, char* argV[]){
    if(argK!=2) return -1;
    int i, consumerK=ConvertToInt(argV[1]), error=0;
    sem_init(&buffer_size,0,0);
    pthread_t consumer_id[consumerK];
    for(i=0;i<consumerK;i++){
    	error=pthread_create(&consumer_id[i],NULL,&consumer,NULL);
    	if(error!=0){
    		printf("%s",strerror(error));
    		return -1;
    	}
    }

    while(1){
        if(i++>(10*consumerK)+2*consumerK) break;
        sleep(1);
        struct mas *new_mas;
        new_mas=(struct mas*)calloc(1,sizeof(struct mas));
        pthread_mutex_lock(&Mutex);
        new_mas->next=buffer;
        new_mas->data=i;
        buffer=new_mas;
        sem_post(&buffer_size);
        pthread_mutex_unlock(&Mutex);
    }
    for(i=0;i<consumerK;i++){
    	pthread_join(consumer_id[i],NULL);
    }
    return 0;
}

void* consumer(void* params){
    int i=0;
    while(1){
        if(i++>10) break;
        struct mas *new_mas;
        //printf("Consumer turn - %d",i);
        sem_wait(&buffer_size);
        pthread_mutex_lock(&Mutex);
        printf("Consumer turn - %d, buffer - %X, buffer data - %d\n",i,buffer,buffer->data);
        new_mas=buffer;
        buffer=buffer->next;
        pthread_mutex_unlock(&Mutex);
        free(new_mas);
    }
}
