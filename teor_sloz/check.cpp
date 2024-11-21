#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#define eps 1e-6 
#define PI 3.14159265354
typedef std::complex<double> complex_t;
using namespace std;
 
//Calculation of rotation factor 
complex_t W(int k,int n,int N){
	return complex_t(cos(2*PI*k*n/N),-sin(2*PI*k*n/N));
}
 
 //Format zero 
complex_t format(complex_t &c){
	if(fabs(c.real())<eps) c.real()=0;
	if(fabs(c.imag())<eps) c.imag()=0;
	return c;
}
 
double format(double &c){
	if(fabs(c)<eps) c=0;
	return c;
}
 
 //Ensure that N is 2 to the power of n
int bitlen(int N){
	int n=0;
	while((N&1)==0){
		n++;
		N>>=1;
	}
	return n;
}
 
 
 int reverse_bit(int n,int len){//bit reverse 
	int tmp=0;
	while(len--){
		tmp+=((n&1)<<len);
		n>>=1;
	}
	return tmp;
 
}
 
 //Ordinal rearrangement 
void resort(vector<complex_t> &x_n,int N){
	vector<complex_t> v(x_n);
	int len=bitlen(N);
	for(int i=0;i<N;++i){
		x_n[i]=v[reverse_bit(i,len)];
	}
}
 
 
 //Base 2, FFT algorithm implementation, O(nlogn) complexity
void FFT(vector<complex_t> &x_n){
	int N=x_n.size();
	int r=bitlen(N);
	
	vector<complex_t> W(N);
 
	 //Calculate the rotation factor in advance 
	for(int i=0;i<N;++i){
		double angle=-i*2*PI/N;
		W[i]=complex_t(cos(angle),sin(angle));
	}
	
	
	 for(int k=0;k<r;++k){//number of iterations 
		for(int j=0;j<(1<<k);++j){
			int butterfly=1<<(r-k);
			int p=j*butterfly;
			int s=p+butterfly/2;
			for(int i=0;i<butterfly/2;++i){
				complex_t c=x_n[i+p]+x_n[i+s];
				x_n[i+s]=(x_n[i+p]-x_n[i+s])*W[i*(1<<k)];
				x_n[i+p]=c;
			}
		}
	}
	
	 //Reorder 
	resort(x_n,N);
	cout<<"end 1\n";
	
}
 
 //IFFT, basically the same as FFT 
void IFFT(vector<complex_t> &x_n){
	int N=x_n.size();
	int r=bitlen(N);
	
	vector<complex_t> W(N);
 
	 //Calculate the rotation factor in advance 
	for(int i=0;i<N;++i){
		 double angle=i*2*PI/N;//The difference between the rotation factor of IFFT and the rotation factor of FFT is a negative sign 
		W[i]=complex_t(cos(angle),sin(angle));
	}
	
	
	 for(int k=0;k<r;++k){//number of iterations 
		for(int j=0;j<(1<<k);++j){
			int butterfly=1<<(r-k);
			int p=j*butterfly;
			int s=p+butterfly/2;
			for(int i=0;i<butterfly/2;++i){
				complex_t c=x_n[i+p]+x_n[i+s];
				x_n[i+s]=(x_n[i+p]-x_n[i+s])*W[i*(1<<k)];
				x_n[i+p]=c;
			}
		}
	}
	
	 //Reorder 
	resort(x_n,N);
	for(int i=0;i<N;++i){
		 x_n[i]/=N;//IFFT and FFT are still one coefficient 
	}
	cout<<"end 2\n";
}
 
void FFT_test(){
	int N=pow(2,24);
	vector<complex_t> x_n;
	complex_t c(0,0);
	for(int i=0;i<N;++i){
		c.real()=i;
		x_n.push_back(c);
	}
	
	FFT(x_n);
	IFFT(x_n);
}
 
 
int main(){
	cout<<"go\n";
	FFT_test();
	cout<<"end";
	return 0;
}
