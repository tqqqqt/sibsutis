#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void ran(int **mas, int *str, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<str[i];j++){
			mas[i][j]=1+rand()%49;
		}
	}
}

void prin(int **mas, int *str, int n){
	printf("\n \n \n");
	for(int i=0;i<n;i++){
		for(int j=0;j<str[i];j++){
			printf("%d ",mas[i][j]);
		}
		printf("\n-------------\n");
	}
}

int main(){
	srand(time(NULL));
	int **mas, *str;
	int n=1+rand()%20, s=0;
	mas=(int**)malloc(n*sizeof(int));
	str=(int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		s=1+rand()%8;
		mas[i]=(int*)malloc(s*sizeof(int));
		str[i]=s;
	}
	ran(mas,str,n);
	prin(mas,str,n);
	free(str);
	for(int i=0;i<n;i++) free(mas[i]);
	free(mas);
	return 0;
}
