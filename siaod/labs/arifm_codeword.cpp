#include <iostream>
#include <fstream>
#include <math.h>

const int N = 256;
const char nam[] = "1.txt";

using namespace std;

struct data_read {
	int sy;
	double p;
};

void arifm(int count, data_read* P, int n) {
	long double temp_r=1;

	std::ifstream file;
	file.open(nam, ios::binary | ios::in);

	long double* l = new long double[n + 1] {} , * h = new long double[n + 1] {} ;
	long double *r=new long double[n+1] {};
	double *q=new double[count + 1] {};
	int i = 0, m = 0;
	unsigned char c;
	q[0] = 0;
	r[0] = 1;
	h[0] = 1;
	l[0] = 0;
	for (int f = 1; f <= count; f += 1) {
		q[f] = q[f-1] + P[f].p;
	}
	while (true) {
		file.read((char*)&c, 1);
		if (file.eof()) break;
		i += 1;
		for (int j = 1; j <= count; j += 1) {
			if ((int)c == P[j].sy) {
				m = j;
				break;
			}
		}
		l[i] = l[i - 1] + r[i - 1] * q[m-1];
		h[i] = l[i - 1] + r[i - 1] * q[m];
		r[i] = h[i] - l[i];
		if(r[i]<temp_r && r[i]!=0) temp_r=r[i];
		if(r[i]==0) break;
		std::cout<<"["<<i<<"] "<<l[i]<<" -- "<<h[i]<<" --- "<<r[i]<<std::endl;
	}
	std::cout<<"["<<i<<"] "<<l[i]<<" -- "<<h[i]<<" --- "<<r[i]<<std::endl;
	long double res=l[i];
	int size=0;
	size=-floor(log2(temp_r));
	delete[] l;
	delete[] h;
	delete[] r;
	int *cc=new int[size];
	cout<<" Size code word = "<<size<<endl<<endl<<" Code word - ";
	for(int i=0; i<size; i+=1) {
		res=res*2;
		cc[i]=trunc(res);
		if(res>=1) res=res-1;
		std::cout<<cc[i];
	}
	delete[] cc;
	cout<<endl<<endl<<"{{"<<(float)size/n<<"}}";
	std::cout<<std::endl<<std::endl;
	file.close();
}

int main() {
	int bytes[N] {};
	int count = 0, sum = 0, ii = 1;
	int c[N + 1][N + 1] {}, l[N + 1] {};
	unsigned char x;
	std::ifstream infile;
	infile.open(nam, ios::binary | ios::in);
	while (true) {
		infile.read((char*)&x, 1);
		if (infile.eof()) break;
		bytes[x]++;
		sum++;
	}
	for (int i = 0; i < N; i++) if (bytes[i] != 0) count += 1;
	data_read* P = new data_read[count + 1] {};
	int* pp = new int[count + 1] {};
	double* ppp = new double[count + 1] {};
	for (int i = 0; i < N; ++i) {
		if (bytes[i] != 0) {
			P[ii].sy = i;
			P[ii].p = (float)bytes[i] / (float)sum;
			ii += 1;
		}
	}
	std::cout << std::endl << std::endl;
	for (int i = 1; i <= count; i++) cout << "[" << i << "] " << P[i].sy << " |\t" << (char)P[i].sy << "\t|\t" << P[i].p << "\n";
	arifm(count, P, sum);
	delete[] P;
	delete[] pp;
	delete[] ppp;
	infile.close();
	return 0;
}
