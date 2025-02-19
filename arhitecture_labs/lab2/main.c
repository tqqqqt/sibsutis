#include<stdio.h>
#include<signal.h>

void SignalHandler(int signo){
	if(signo==SIGTSTP || signo==SIGUSR1){
		return;
	}
}

int main(int argc, char* argv[]){
	signal(SIGTSTP,SignalHandler);
	signal(SIGUSR1,SignalHandler);
	if(argc==1){
		fprintf(stdout,"No argument\n");
		return -1;
	}
	FILE *file;
	int i;
	for(i=1;i<argc;i++){
		file=fopen(argv[i],"r");
		if(file==NULL){
			fprintf(stdout,"Error open file");
		//	return -1;
		}
		else{
			fprintf(stdout,"----------File - %s----------\n",argv[i]);
			char buffer[256];
			while(fgets(buffer,256,file)!=NULL){
				fprintf(stdout,"%s",buffer);
			}
			fclose(file);
		}
		fprintf(stdout,"\n----------End file----------\n");
	}
	int c=getchar();
	raise(SIGUSR1);
	return 0;
}
