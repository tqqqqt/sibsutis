#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;

const int n=4, nn=3, nnn=n+nn-1;
const double pi=3.141592;

double** DiscretPreobrazFurie(int mas[], int N);
void ObratDiscretPreobrazFurie(double masFurie[][2], int N);
double** PolyBistrPreobrazFurie(int mas[], int N);
void ObratnoePolybistrPreobrazFurie(double resMasFurie[][2], int N);

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
	
	cout<<"\n \n --------------------------------\n Discrentoe preobraz: \n Pryamoe: \n "<<endl<<endl;
	int masA[n]={1, 2, 3, 4}, masB[n]={5, 6, 7, 8};
	cout<<"A massive: ";
	for(int i=0;i<n;i++) cout<<masA[i]<<" ";
	cout<<endl<<"B massive: ";
	for(int i=0;i<n;i++) cout<<masB[i]<<" ";
	cout<<endl;
	
	int longMasA[2*n]{}, longMasB[2*n]{};
	for(int i=0;i<n;i++){
		longMasA[i]=masA[i];
		longMasB[i]=masB[i];
	}
	cout<<endl<<"FA: "<<endl;
	double **FA=DiscretPreobrazFurie(longMasA,2*n);
	cout<<endl<<"FB: "<<endl;
	double **FB=DiscretPreobrazFurie(longMasB,2*n);
	double FC[2*n][2];
	cout<<endl<<"FC: "<<endl;
	for(int i=0;i<2*n;i++){
		FC[i][0]=(FA[i][0]*FB[i][0] - FA[i][1]*FB[i][1]);
		FC[i][1]=(FA[i][0]*FB[i][1] + FA[i][1]*FB[i][0]);
		FC[i][0]*=2.0*n;
		FC[i][1]*=2.0*n;
		printf("%f + %f * i\n",FC[i][0],FC[i][1]);
	}
	ObratDiscretPreobrazFurie(FC,2*n);
	
	cout<<"\n \n --------------------------------\n Poly bistr preobraz: \n Pryamoe: \n "<<endl<<endl;
	cout<<"A massive: ";
	for(int i=0;i<n;i++) cout<<masA[i]<<" ";
	cout<<endl<<"B massive: ";
	for(int i=0;i<n;i++) cout<<masB[i]<<" ";
	cout<<endl;
	
	cout<<endl<<"FA: "<<endl;
	double **FA2=PolyBistrPreobrazFurie(longMasA,2*n);
	cout<<endl<<"FB: "<<endl;
	double **FB2=PolyBistrPreobrazFurie(longMasB,2*n);
	double FC2[2*n][2];
	cout<<endl<<"FC: "<<endl;
	for(int i=0;i<2*n;i++){
		FC2[i][0]=(FA2[i][0]*FB2[i][0] - FA2[i][1]*FB2[i][1]);
		FC2[i][1]=(FA2[i][0]*FB2[i][1] + FA2[i][1]*FB2[i][0]);
		FC2[i][0]*=2.0*n;
		FC2[i][1]*=2.0*n;
		printf("%f + %f * i\n",FC2[i][0],FC2[i][1]);
	}
	ObratnoePolybistrPreobrazFurie(FC2,2*n);
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
	cout<<"\n Obratnoe:"<<endl;
	double masObrat[N][2];
	for(int i=0; i<N; i++) {
		masObrat[i][0]=0;
		masObrat[i][1]=0;
		for(int j=0; j<N; j++) {
			masObrat[i][0] += (masFurie[j][0] * cos(2.0 * pi * i * j / N) - masFurie[j][1] * sin(2.0 * pi * i * j / N));
			masObrat[i][1] += (masFurie[j][1] * cos(2.0 * pi * i * j / N) + masFurie[j][0] * sin(2.0 * pi * i * j / N));
		}
	}
	for(int i=0;i<N-1;i++) printf("%f + %f * i\n",masObrat[i][0],masObrat[i][1]);
}


double** PolyBistrPreobrazFurie(int mas[], int N){
	double** masFurie=new double*[N], **resMasFurie=new double*[N];
	for(int i=0; i<N; i++){
		masFurie[i]=new double[2];
		resMasFurie[i]=new double[2];
	}
	int p1=2, p2=N/2;
//	cout<<"Poly bistr Furie: \n Prymoe:"<<endl;
	for(int k1=0;k1<p1;k1++){
		for(int j2=0;j2<p2;j2++){
			for(int j1=0;j1<p1;j1++){
				masFurie[k1+p1*j2][0]+=mas[j2+p2*j1] * cos(-2.0 * pi * j1 * k1 / p1);
				masFurie[k1+p1*j2][1]+=mas[j2+p2*j1] * sin(-2.0 * pi * j1 * k1 / p1);
			}
			masFurie[k1+p1*j2][0]/=p1;
			masFurie[k1+p1*j2][1]/=p1;
		}
	}
	for(int k1=0;k1<p1;k1++){
		for(int k2=0;k2<p2;k2++){
			for(int j2=0;j2<p2;j2++){
				resMasFurie[k1+k2*p1][0]+=(masFurie[k1 + p1 * j2][0] * cos(-2.0 * pi * j2 / N * (k1 + p1 * k2)) - masFurie[k1 + p1 * j2][1] * sin(-2.0 * pi * j2 / N * (k1 + p1 * k2)));
				resMasFurie[k1+k2*p1][1]+=(masFurie[k1 + p1 * j2][0] * sin(-2.0 * pi * j2 / N * (k1 + p1 * k2)) + masFurie[k1 + p1 * j2][1] * cos(-2.0 * pi * j2 / N * (k1 + p1 * k2)));
			}
			resMasFurie[k1+k2*p1][0]/=p2;
			resMasFurie[k1+k2*p1][1]/=p2;
		}
	}
	for(int i=0;i<N;i++){
		printf("%f + %f * i\n",resMasFurie[i][0],resMasFurie[i][1]);
	}
	return resMasFurie;
}

void ObratnoePolybistrPreobrazFurie(double resMasFurie[][2], int N){
	cout<<"\n Obratnoe:"<<endl;
	int p1=2, p2=N/2;
	double masObrat[N][2], resMasObrat[N][2];
	for(int k1=0;k1<p1;k1++){
		for(int j2=0;j2<p2;j2++){
			for(int j1=0;j1<p1;j1++){
				masObrat[k1+p1*j2][0]+=(resMasFurie[j2+p2*j1][0]*cos(2.0 * pi * j1 * k1 / p1) - resMasFurie[j2+p2*j1][1]*sin(2.0 * pi * j1 * k1 / p1));
				masObrat[k1+p1*j2][1]+=(resMasFurie[j2+p2*j1][0]*sin(2.0 * pi * j1 * k1 / p1) + resMasFurie[j2+p2*j1][1]*cos(2.0 * pi * j1 * k1 / p1));
			}
		}
	}
	for(int k1=0;k1<p1;k1++){
		for(int k2=0;k2<p2;k2++){
			for(int j2=0;j2<p2;j2++){
				resMasObrat[k1+k2*p1][0]+=masObrat[k1+p1*j2][0]*cos(2.0 * pi * j2 / N * (k1 + p1 * k2)) - masObrat[k1+p1*j2][1]*sin(2.0 * pi * j2 / N * (k1 + p1 * k2));
				resMasObrat[k1+k2*p1][1]+=masObrat[k1+p1*j2][1]*cos(2.0 * pi * j2 / N * (k1 + p1 * k2)) + masObrat[k1+p1*j2][0]*sin(2.0 * pi * j2 / N * (k1 + p1 * k2));
			}
		}
	}
	for(int i=0;i<N-1;i++) printf("%f + %f * i\n",resMasObrat[i][0],resMasObrat[i][1]);
}
