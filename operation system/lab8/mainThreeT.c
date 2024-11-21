#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

typedef int (*fun)(double*,int,int,int,int,int*);

typedef struct{
	void* function;
	double *mas;
	int start;
	int rigthSize;
	int n;
	int numFlag;
} argum;

int flags[3]={1,1,1};

int CalculMembers(double *mas, int start, int n, int nn, int num, int *p){
	int i=start, j=0;
	for(i;i<n;i++){
		double temp=0;
		for(j=0;j<nn;j++){
			temp+=j*cos((double)(-2.0*3.141592*i*j/n));
		}
		mas[i]=temp;
	}
	p[num]=0;
	return 0;
}

void ArgumentCreate(argum *arguments, int num){
	if(num==0){
	       	arguments->start=0;
	        arguments->rigthSize=20000;
       		arguments->n=40000;
		arguments->numFlag=0;
	}
	else if(num==1){
	        arguments->start=20000;
       		arguments->rigthSize=40000;
        	arguments->n=40000;
		arguments->numFlag=1;
	}
	else if(num==2){
	        arguments->start=0;
        	arguments->rigthSize=20000;
        	arguments->n=40000;
		arguments->numFlag=2;
	}
}

void* my_thread(void*);

int main(){
	int64_t n=40000;
	double *mas1=malloc(sizeof(double)*n), *mas2=malloc(sizeof(double)*n);
	pthread_t th_id1, th_id2, th_id3;
	argum *arguments1, *arguments2, *arguments3;
	arguments1=malloc(sizeof(argum));
	arguments2=malloc(sizeof(argum));
	arguments3=malloc(sizeof(argum));

	ArgumentCreate(arguments1,0);
	arguments1->mas=mas1;
	arguments1->function=(void*)CalculMembers; 
	pthread_create(&th_id1,NULL,&my_thread,(void*)arguments1);

	ArgumentCreate(arguments2,1);
	arguments2->mas=mas1;
	arguments2->function=(void*)CalculMembers;
	pthread_create(&th_id2,NULL,&my_thread,(void*)arguments2);
	
	ArgumentCreate(arguments3,2);
	arguments3->mas=mas2;
	arguments3->function=(void*)CalculMembers;
	pthread_create(&th_id3,NULL,&my_thread,(void*)arguments3);
	
	int i=20000,j=0;
	for(i;i<n;i++){
		double temp=0;
		for(j=0;j<n;j++){
			temp+=j*sin((double)(-2.0*3.141592*i*j/n));
		}
		mas2[i]=temp;
	}
	while(flags[0] || flags[1] || flags[2]){
		fprintf(stdout,"wait %d - %d - %d\n",flags[0],flags[1],flags[2]);
		sleep(1);
	}
	
	double *mas3=malloc(sizeof(double)*n);
	for(i=0;i<n;i++){
		mas3[i]=mas1[i]+mas2[i];
		if(i>39994) fprintf(stdout,"%d - %f\n",i,mas3[i]);
	}
	return 0;
}

void* my_thread(void* arg){
	argum *arguments=arg;
	((fun)(arguments->function))(arguments->mas,arguments->start,arguments->rigthSize,arguments->n,arguments->numFlag,flags);
}
