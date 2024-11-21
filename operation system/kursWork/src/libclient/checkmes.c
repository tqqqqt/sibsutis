#include<libclient/checkmes.h>

int CheckClientBuffer(char *buffer){
	char *helpStr=strstr(buffer,HELP), *readStr=strstr(buffer,READELF), *quitStr=strstr(buffer,QUIT);
	if(!helpStr && !readStr && !quitStr) return 1;
	return 0;
}

int CheckEndAnswer(char *buffer){
	char *endAnswer="endAnswer444";
	int l=0,i=0;
	for(i=0;i<strlen(buffer);i++){
		if(buffer[i]==endAnswer[l]) l++;
		else l=0;
	}
	if(l==strlen(endAnswer)) return 1;
	return 0;
}

int CheckErrorAnswer(char *buffer){
	char *errorAnswer="errorRed";
	int l=0,i=0;
	for(i=0;i<strlen(buffer);i++){
		if(buffer[i]==errorAnswer[l]) l++;
		else l=0;
	}
	if(l==strlen(errorAnswer)) return 1;
	return 0;
}
