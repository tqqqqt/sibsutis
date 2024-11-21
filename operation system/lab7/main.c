#include<stdio.h>
#include<string.h>
#include<dlfcn.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<signal.h>

struct spis{
	char firstName[30];
	char lastName[30];
	char loginDate[12];
	struct spis* next;
	struct spis* prev;
};

int main(){
	fprintf(stdout,"My proc info - %d \n Sleep after load lib \n",(int)getpid());
	sleep(20);
	const char* libName="liblab5.so";
	void *dl_handle;
	struct spis* (*initFunc)(char*,char*,char*);
	void (*printFunc)(struct spis*);
	struct spis* mainHead=NULL;
	dl_handle=dlopen(libName,RTLD_LAZY);
	if(!dl_handle){
		fprintf(stdout,"Open eror - %s \n",dlerror());
		return -1;
	}
	initFunc=dlsym(dl_handle,"InitNewSpis");
	char *error=dlerror();
	if(error!=NULL){
		fprintf(stdout,"Find first func error - %s \n",error);
		return -1;
	}
	mainHead=(*initFunc)("first","last","10-10-2010");
	printFunc=dlsym(dl_handle,"PrintSpis");
	error=dlerror();
	if(error!=NULL){
		fprintf(stdout,"Find second func error - %s \n",error);
		return -1;
	}
	(*printFunc)(mainHead);
	fprintf(stdout,"\nStart sleep before close lib.");
	sleep(20);
	dlclose(dl_handle);
	fprintf(stdout,"\nStart sleep after close lib.\n");
	sleep(20);
	fprintf(stdout,"End work.\n");
	return 0;
}
