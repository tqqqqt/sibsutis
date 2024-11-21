#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n=4, nn=3, nnn=n+nn-1;

void Svertka(int a[n], int b[nn]){
	int c[nnn], sum=0;
	for(int i=0;i<nnn;i++) c[i]=0;
	for(int needN=0;needN<nnn;needN++){
		for(int i=0;i<n;i++){
			for(int j=0;j<nn;j++){
				if(i+j==needN){
					c[needN]+=a[i]*b[j];
				}
			}
		}
	}
	cout<<"C massive: ";
	for(int i=0;i<nnn;i++){
		cout<<c[i]<<" ";
		sum+=c[i];
	}
	cout<<"\n Sum = "<<sum;
}

int main(){
//	int a[n], b[nn];
//	for(int i=0;i<n;i++) a[i]=1+rand()%10;
//	for(int i=0;i<nn;i++) b[i]=1+rand()%10;
	int a[n]={1, 2, 3, 4}, b[nn]={5, 6, 7};
	
	cout<<"A massive: ";
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
	cout<<endl<<"B massive: ";
	for(int i=0;i<nn;i++) cout<<b[i]<<" ";
	cout<<endl;
	
	Svertka(a,b);
}