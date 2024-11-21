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
		temp[i] = i + 1;
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

int main() {
	int *mas=firstF();
//	int *mas=secondF();
	cout<<"Iznachal massiv: ";
	for(int i=0; i<n; i++) cout<<mas[i]<<" ";
	cout<<endl<<endl;

	discretPreobrazFurie(mas);
	cout<<endl<<endl;
}
