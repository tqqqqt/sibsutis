#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n=20, nnn=n+n-1;
const double pi=3.141592;

int complUmn=0;

double** DiscretPreobrazFurie(int mas[], int N);
void ObratDiscretPreobrazFurie(double masFurie[][2], int N);

void Svertka(int a[n], int b[n]){
	int c[nnn], sum=0;
	for(int i=0;i<nnn;i++) c[i]=0;
	for(int needN=0;needN<nnn;needN++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(i+j==needN){
					c[needN]+=a[i]*b[j];
				}
			}
		}
	}
	cout<<"C: ";
	for(int i=0;i<nnn;i++){
		cout<<c[i]<<" ";
		sum+=c[i];
	}
	cout<<"\n Sum = "<<sum;
}

int main(){
	int a[n], b[n];
	for(int i=0;i<n;i++){
		a[i]=i;
		b[i]=n+i;
	}
	
	cout<<"A: ";
	for(int i=0;i<n;i++) cout<<a[i]<<" ";
	cout<<endl<<"B: ";
	for(int i=0;i<n;i++) cout<<b[i]<<" ";
	cout<<endl;
	
	Svertka(a,b);
	
	int longMasA[2*n]{}, longMasB[2*n]{};
	for(int i=0;i<n;i++){
		longMasA[i]=a[i];
		longMasB[i]=b[i];
	}
	cout<<endl<<endl<<"A: "<<endl;
	double **FA=DiscretPreobrazFurie(longMasA,2*n);
	cout<<endl<<"B: "<<endl;
	double **FB=DiscretPreobrazFurie(longMasB,2*n);
	double FC[2*n][2];
	cout<<endl<<"C: "<<endl;
	for(int i=0;i<2*n;i++){
		FC[i][0]=(FA[i][0]*FB[i][0] - FA[i][1]*FB[i][1]);
		FC[i][1]=(FA[i][0]*FB[i][1] + FA[i][1]*FB[i][0]);
		complUmn+=1;
		FC[i][0]*=2.0*n;
		FC[i][1]*=2.0*n;
		printf("%f + %f * i\n",FC[i][0],FC[i][1]);
	}
	ObratDiscretPreobrazFurie(FC,2*n);
	cout<<"\n Compl Umn = "<<complUmn<<'\n';
}

double** DiscretPreobrazFurie(int mas[], int N) {
	double** masFurie=new double*[N];
	for(int i=0; i<N; i++) masFurie[i]=new double[2];
	double sumRe, sumIm;
	for (int i = 0; i < N; i++) {
		sumRe=0;
		sumIm=0;
		for (int j = 0; j < N; j++) {
			sumRe+=mas[j] * cos(-2.0 * pi * i * j / N);
			sumIm+=mas[j] * sin(-2.0 * pi * i * j / N);
		}
		masFurie[i][0]=sumRe/N;
		masFurie[i][1]=sumIm/N;
		printf("%f - %f * i\n", masFurie[i][0], masFurie[i][1]);
	}
	return masFurie;
}

void ObratDiscretPreobrazFurie(double masFurie[][2], int N){
	cout<<endl;
	double masObrat[N][2];
	for(int i=0; i<N; i++) {
		masObrat[i][0]=0;
		masObrat[i][1]=0;
		for(int j=0; j<N; j++) {
			masObrat[i][0] += (masFurie[j][0] * cos(2.0 * pi * i * j / N) - masFurie[j][1] * sin(2.0 * pi * i * j / N));
			masObrat[i][1] += (masFurie[j][1] * cos(2.0 * pi * i * j / N) + masFurie[j][0] * sin(2.0 * pi * i * j / N));
			complUmn+=1;
		}
	}
	for(int i=0;i<N-1;i++) printf("%f + %f * i\n",masObrat[i][0],masObrat[i][1]);
}
