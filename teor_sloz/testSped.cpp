#include <iostream>
#include <math.h>
using namespace std;

void ttest(int N){
	if(N<=1) return;
	ttest(N/2);
	double pi=3.14159265, pii=pi*2;
	double a,b,c,d,e;
	for(int i=0;i<N/2;i++){
		a=pi*pii-pii*pi;
		b=pi*pii+pi*pii;
		c=a+b;
		d=a-b;
		e=a*b;
	}
}

int main(){
	double pi=3.14159265, pii=pi*2;
	double a,b,c,d,e;
	for(int i=0;i<2;i++){
		for(int ii=0;ii<10000;ii++){
			for(int j=0;j<10000;j++){
				a=pi*pii-pii*pi;
				b=pi*pii+pi*pii;
				c=a+b;
				d=a-b;
				e=a*b;
			}
		}	
	}
	
	cout<<"end 1\n";
	
	ttest(pow(2,24));
	cout<<"end 2";
}
