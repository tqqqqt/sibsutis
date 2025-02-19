#include<libserver/checkmessage.h>

int CheckMessageConnect(char *buffer){
	char *temp;
	int i=0,r=0;
	for(i;i<strlen(buffer);i++){
		if(buffer[i]==' ' || buffer[i]=='\n' || buffer[i]=='\0') break;
		r+=1;
	}
	temp=(char*)malloc(sizeof(char)*r);
	strncpy(temp,buffer,r);
	if(strcmp(temp,"client")==0) return 0;
	return 1;
}

int CheckMessageCommand(char *buffer){
	char *temp;
	int i=0,r=0;
	for(i;i<strlen(buffer);i++){
		if(buffer[i]==' ' || buffer[i]=='\n' || buffer[i]=='\0') break;
		r++;
	}
	temp=(char*)malloc(sizeof(char)*r);
	strncpy(temp,buffer,r);
	if(strcmp(temp,"readelf")==0) return 1;
	if(strcmp(temp,"quit")==0) return 2;
	return 0;
}
