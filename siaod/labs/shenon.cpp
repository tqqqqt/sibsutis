#include <iostream>
#include <math.h>

const int n=6, nn=n+1;

void shenon(double *p, double *q, double *l, double c[nn][nn]){
	p[0]=0; q[0]=0;
	for(int i=1;i<=n;i++){
		q[i]=q[i-1]+p[i];
		l[i]=ceil(-log2(p[i]));
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=l[i];j++){
			q[i-1]=q[i-1]*2;
			c[i][j]=trunc(q[i-1]);
			if(q[i-1]>1) q[i-1]=q[i-1]-1;
		}
	}
}

int main(){
	double p[nn], q[nn]{};
	double l[nn]{};
	double c[nn][nn]{}; 
	p[1]=0.36;
	p[2]=0.18;
	p[3]=0.18;
	p[4]=0.12;
	p[5]=0.09;
	p[6]=0.07;

	shenon(p,q,l,c);
	std::cout<<std::endl<<std::endl;
	for(int i=1;i<=n;i+=1){
		for(int j=1;j<=l[i];j+=1){
			std::cout<<c[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}
