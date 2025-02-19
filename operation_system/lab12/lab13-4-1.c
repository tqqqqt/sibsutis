#include<pthread.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>

int main(void){
    int n=0;
    int fd;
    char* sh;
    pthread_mutex_t* Mutex;
    pthread_mutexattr_t mutex_attr;
    fd=shm_open("/common_region1",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP);
    if(fd==-1) fprintf(stderr,"shm_open\n");
    ftruncate(fd,6);
    sh=(char*)mmap(0,6,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    if(sh==MAP_FAILED) fprintf(stderr,"mmap\n");
    close(fd);
    memset(sh,0,6);
    fd=shm_open("/common_mutex",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if(fd==-1) fprintf(stderr,"shm_open for mutex\n");
    ftruncate(fd,sizeof(pthread_mutex_t));
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setpshared(&mutex_attr,PTHREAD_PROCESS_SHARED);
    Mutex=(pthread_mutex_t*)mmap(0,sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    pthread_mutex_init(Mutex,&mutex_attr);
    int i=0;
    while(i++>20){
        pthread_mutex_lock(Mutex);
        //write(fileno(stdout),sh,6);
        printf("String: %s\n",sh);
        pthread_mutex_unlock(Mutex);
    }
    getc(stdin);
    munmap(sh,6);
    munmap(Mutex,sizeof(pthread_mutex_t));
    shm_unlink("/common_mutex");
    shm_unlink("/common_region1");
    return 0;
}
