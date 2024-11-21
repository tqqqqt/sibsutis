#define _USE_MATH_DEFINES

#include<iostream>
#include<cmath>
#include<vector>
#include<complex>

const int n = 10;

using namespace std;

long double* firstF () {
	long double* temp = new long double[n];
	for (int i = 1; i <= n; i++) {
		temp[i - 1] = pow(i, 2);
	}
	return temp;
}

long double* secondF() {
	long double* temp = new long double[n];
	for (int i = 1; i <= n; i++) {
		temp[i - 1] = pow(i, (3 /(long double) 2));
	}
	return temp;
}

long double* thirdF() {
	long double* temp = new long double[n];
	for (int i = 1; i <= n; i++) {
		temp[i - 1] = i * (long double)log(i);
	}
	return temp;
}

int main() {
	long double* mas = firstF();
	//long double* mas = secondF();
	//long double* mas = thirdF();
	for (int i = 0; i < n; i++) cout << mas[i] << " ";
	const complex<long double> iSqrt = sqrt(complex<double>(-1, 0));  //iSqrt.real() iSqrt.imag()
	vector<long double> res;
	for (int i = 1; i <= n; i++) {
		long double geomSum = 0, temp=0;
		for (int j = 0; j < n; j++) {
			geomSum += (long double) exp(-2 *(long double) M_PI * iSqrt.imag() * (((i - 1) *(long double) j) /(long double) n)) * mas[j];
		}
		temp = (1 /(long double) n) *(long double) geomSum;
		res.push_back(temp);
	}
	cout << endl << endl << " Pryamoe:" << endl;
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << endl << endl << " Obrat:" << endl;
	for (int i = 1; i <= n; i++) {
		long double geomSum = 0;
		for (int j = 0; j < n; j++) {
			geomSum += (long double)exp(2 * (long double)M_PI * iSqrt.imag() * (((i - 1) * (long double)j) / (long double)n)) * res[j];
		}
		cout << geomSum << " ";
	}
}
