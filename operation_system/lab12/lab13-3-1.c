#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

int main(int argc, char* const argv[]){
    int fd;
    char* map_address;
    fd=shm_open("/common_region",O_RDWR | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP);
    if(fd==-1) fprintf(stderr,"open\n");
    ftruncate(fd,256);
    map_address=(char*)mmap(0,256,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    if(map_address==MAP_FAILED) fprintf(stderr,"mmap\n");
    close(fd);
    memcpy(map_address,"Take it easy! Be happy!",sizeof("Take it easy! Be happy!"));
    getc(stdin);
    munmap(map_address,256);
    shm_unlink("/common_region");
    return 0;
}
