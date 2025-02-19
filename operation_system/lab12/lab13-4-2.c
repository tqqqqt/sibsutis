#include<pthread.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>

int main(){
    int n=0, counter=0;
    int fd;
    char* sh;
    pthread_mutex_t *Mutex;
    fd=shm_open("/common_region1",O_RDWR,S_IRUSR | S_IWUSR | S_IRGRP);
    sh=(char*)mmap(0,6,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    memset(sh,0,6);
    fd=shm_open("/common_mutex",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP);
    Mutex=(pthread_mutex_t*)mmap(0,sizeof(pthread_mutex_t),PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
    close(fd);
    int i=0;
    while(1){
        pthread_mutex_lock(Mutex);
        if(counter%2){
            sh[0]='H'; sh[1]='e'; sh[2]='l'; sh[3]='l'; sh[4]='o'; sh[5]='!';
        }
        else{
            sh[0]='B'; sh[1]='y'; sh[2]='e'; sh[3]='_'; sh[4]='u'; sh[5]='!';
        }
        pthread_mutex_unlock(Mutex);
        counter++;
    }
    getc(stdin);
    munmap(sh,6);
    shm_unlink("/common_region1");
    munmap(Mutex,sizeof(pthread_mutex_t));
    shm_unlink("/common_mutex");
    return 0;
}
