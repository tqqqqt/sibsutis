#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>

int main(){
	int64_t n=40000;
	double *mas1=malloc(sizeof(double)*n), *mas2=malloc(sizeof(double)*n);
	int i=0,j=0;
	for(i;i<n;i++){
		double temp=0;
		for(j=0;j<n;j++){
			temp+=j*cos((double)(-2.0*3.141592*i*j/n));
		}
		mas1[i]=temp;
	}
	for(i=0;i<n;i++){
		double temp=0;
		for(j=0;j<n;j++){
			temp+=j*sin((double)(-2.0*3.141592*i*j/n));
		}
		mas2[i]=temp;
	}
	double *resMas=malloc(sizeof(double)*n);
	for(i=0;i<n;i++){
		resMas[i]=mas1[i]+mas2[i];
		if(i>39994) fprintf(stdout,"%d - %f\n",i,resMas[i]);
	}
	return 0;
}
