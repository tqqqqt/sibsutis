#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>

int main(){
    int n=0;
    int counter=0;
    int fd;
    char *sh;
    sem_t *sem;
    fd=shm_open("/common_region",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP);
    sh=(char*)mmap(0,6,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    memset(sh,0,6);
    sem=sem_open("/common_sem",0);
    while(1){
        sem_wait(sem);
        if(counter%2){
            sh[0]='H';sh[1]='e';sh[2]='l';sh[3]='l';sh[4]='o';sh[5]='\0';
        }
        else{
            sh[0]='B';sh[1]='y';sh[2]='e';sh[3]='_';sh[4]='u';sh[5]='\0';
        }
        sem_post(sem);
        counter++;
        //sleep(1);
    }
    getc(stdin);
    munmap(sh,6);
    //shm_unlink("/common_region");
    //shm_unlink("/commin_sem");    
    return 0;
}
