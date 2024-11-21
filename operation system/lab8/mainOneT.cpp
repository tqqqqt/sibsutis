#include<stdio.h>
#include<thread>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

typedef int (*fun)(double*,int,int*);

typedef struct{
	void* function;
	double *mas;
	int n;
} argum;

int flags=1;

int CalculMembers(double *mas, int n, int *p){
	int i=0, j=0;
	for(i;i<n;i++){
		double temp=0;
		for(j=0;j<n;j++){
			temp+=j*cos((double)(-2.0*3.141592*i*j/n));
		}
		mas[i]=temp;
	}
	*p=0;
	return 0;
}

void* my_thread1(void*);

int main(){
	int64_t n=40000;
	double *mas1=new double[n], *mas2=new double[n];
	argum *arguments;
	arguments=new argum;
	arguments->function=(void*)CalculMembers;
	arguments->mas=mas1;
	arguments->n=n;
	std::thread th_id1(my_thread1,(void*)arguments); 

	//pthread_create(&th_id1,NULL,&my_thread1,(void*)arguments);
	int i=0,j=0;
	for(i;i<n;i++){
		double temp=0;
		for(j=0;j<n;j++){
			temp+=j*sin((double)(-2.0*3.141592*i*j/n));
		}
		mas2[i]=temp;
	}
	//while(flags){
	//	printf("wait\n");
	//	sleep(1);
	//}
	th_id1.join();
	double *mas3=new double[n];
	for(i=0;i<n;i++){
		mas3[i]=mas1[i]+mas2[i];
		if(i>39994) printf("%d - %f\n",i,mas3[i]);
	}
	return 0;
}

void* my_thread1(void* arg){
	argum *arguments=(argum*)arg;
	((fun)(arguments->function))(arguments->mas,arguments->n,&flags);
}
