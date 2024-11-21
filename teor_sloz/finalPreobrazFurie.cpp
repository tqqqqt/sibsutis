#include<iostream>
#include<cmath>
using namespace std;

const int n=4;
const double pi = 3.141592;

int* firstF () {
	int* temp = new int[n];
	for (int i = 0; i <= n; i++) {
		temp[i] = i * i;
	}
	return temp;
}

int* secondF() {
	int* temp = new int[n];
	for (int i = 0; i < n; i++) {
		temp[i] = i;
	}
	return temp;
}

void discretPreobrazFurie(int mas[n]) {
	double** masFurie=new double*[n];
	for(int i=0; i<n; i++) masFurie[i]=new double[2];

	double sumRe, sumIm;
	cout<<"Discret furie: \n Prymoe:"<<endl;
	for (int i = 0; i < n; i++) {
		sumRe=0;
		sumIm=0;
		for (int j = 0; j < n; j++) {
			sumRe+=mas[j] * cos(-2.0 * pi * i * j / n);
			sumIm+=mas[j] * sin(-2.0 * pi * i * j / n);
		}
		masFurie[i][0]=sumRe/n;
		masFurie[i][1]=sumIm/n;
		printf("%f - %f * i\n", masFurie[i][0], masFurie[i][1]);
	}
	cout<<"------------------------ \n Obratnoe:"<<endl;
	double masObrat[n][2];
	for(int i=0; i<n; i++) {
		masObrat[i][0]=0;
		masObrat[i][1]=0;
		for(int j=0; j<n; j++) {
			masObrat[i][0] += (masFurie[j][0] * cos(2.0 * pi * i * j / n) - masFurie[j][1] * sin(2.0 * pi * i * j / n));
			masObrat[i][1] += (masFurie[j][1] * cos(2.0 * pi * i * j / n) + masFurie[j][0] * sin(2.0 * pi * i * j / n));
		}
	}
	for(int i=0;i<n;i++) printf("%f + %f * i\n",masObrat[i][0],masObrat[i][1]);
}

void polyBistrPreobrazFurie(int mas[n]){
	double** masFurie=new double*[n], **resMasFurie=new double*[n];
	for(int i=0; i<n; i++){
		masFurie[i]=new double[2];
		resMasFurie[i]=new double[2];
	}

	int p1=2, p2=n/2;
	double sumRe, sumIm;
	cout<<"Poly bistr Furie: \n Prymoe:"<<endl;
	for(int k1=0;k1<p1;k1++){
		for(int j2=0;j2<p2;j2++){
			for(int j1=0;j1<p1;j1++){
				masFurie[k1+j2*p1][0]+=mas[j2+p2*j1] * cos(-2.0 * pi * j1 * k1 / p1);
				masFurie[k1+j2*p1][1]+=mas[j2+p2*j1] * sin(-2.0 * pi * j1 * k1 / p1);
			}
			masFurie[k1+p1*j2][0]/=p1;
			masFurie[k1+p1*j2][1]/=p1;
		}
	}
	for(int k1=0;k1<p1;k1++){
		for(int k2=0;k2<p2;k2++){
			for(int j2=0;j2<p2;j2++){
				resMasFurie[k1+k2*p1][0]+=(masFurie[k1 + p1 * j2][0] * cos(-2.0 * pi * j2 / n * (k1 + p1 * k2)) - masFurie[k1 + p1 * j2][1] * sin(-2.0 * pi * j2 / n * (k1 + p1 * k2)));
				resMasFurie[k1+k2*p1][1]+=(masFurie[k1 + p1 * j2][0] * sin(-2.0 * pi * j2 / n * (k1 + p1 * k2)) + masFurie[k1 + p1 * j2][1] * cos(-2.0 * pi * j2 / n * (k1 + p1 * k2)));
			}
			resMasFurie[k1+k2*p1][0]/=p2;
			resMasFurie[k1+k2*p1][1]/=p2;
		}
	}
	for(int i=0;i<n;i++){
		printf("%f + %f * i\n",resMasFurie[i][0],resMasFurie[i][1]);
	}
	cout<<"------------------------ \n Obratnoe:"<<endl;
	double masObrat[n][2], resMasObrat[n][2];
	for(int k1=0;k1<p1;k1++){
		for(int j2=0;j2<p2;j2++){
			for(int j1=0;j1<p1;j1++){
				masObrat[k1+j2*p1][0]+=(resMasFurie[j2+p2*j1][0]*cos(2.0 * pi * j1 * k1 / p1) - resMasFurie[j2+p2*j1][1]*sin(2.0 * pi * j1 * k1 / p1));
				masObrat[k1+j2*p1][1]+=(resMasFurie[j2+p2*j1][0]*sin(2.0 * pi * j1 * k1 / p1) + resMasFurie[j2+p2*j1][1]*cos(2.0 * pi * j1 * k1 / p1));
			}
		}
	}
	for(int k1=0;k1<p1;k1++){
		for(int k2=0;k2<p2;k2++){
			for(int j2=0;j2<p2;j2++){
				resMasObrat[k1+k2*p1][0]+=masObrat[k1+p1*j2][0]*cos(2.0 * pi * j2 / n * (k1 + p1 * k2)) - masObrat[k1+p1*j2][1]*sin(2.0 * pi * j2 / n * (k1 + p1 * k2));
				resMasObrat[k1+k2*p1][1]+=masObrat[k1+p1*j2][1]*cos(2.0 * pi * j2 / n * (k1 + p1 * k2)) + masObrat[k1+p1*j2][0]*sin(2.0 * pi * j2 / n * (k1 + p1 * k2));
			}
		}
	}
	for(int i=0;i<n;i++) printf("%f + %f * i\n",resMasObrat[i][0],resMasObrat[i][1]);
}

int main() {
	int *mas=firstF();
//	int *mas=secondF();
	cout<<"Iznachal massiv: ";
	for(int i=0; i<n; i++) cout<<mas[i]<<" ";
	cout<<endl<<endl;

	discretPreobrazFurie(mas);
	cout<<endl<<endl;
	
	polyBistrPreobrazFurie(mas);
	cout<<endl<<endl;
}
