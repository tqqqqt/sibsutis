#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

const int N = 256;

struct data_symbol {
	int symbol;
	float p;
};

void Shenon(data_symbol *P, int *L, int C[N][N]) {
	float *Q = new float[N+1];
	Q[0] = 0;
	for (int i = 1; i < N+1; ++i) {
		Q[i] = Q[i-1] + P[i-1].p;
		L[i-1] = ceil(-log2(P[i-1].p));
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < L[i]; ++j) {
			Q[i] *= 2;
			C[i][j] = trunc(Q[i]);
			if (Q[i] >= 1) {
				Q[i] -= 1;
			}
		}
	}
	delete[] Q;
}

int med(int l, int r, data_symbol *p) {
	double sr=0, sl=0;
	int m=0;
	for(int i=l; i<=r; i+=1) {
		sl=sl+p[i].p;
	}
	sr=p[r].p;
	m=r;
	while(sl>=sr) {
		m=m-1;
		sl=sl-p[m].p;
		sr=sr+p[m].p;
	}
	return m;
}

void fano(int l, int r, int k, int c[N][N], int *len, data_symbol *p) {
	int m=0;
	if(l<r) {
		k=k+1;
		m=med(l,r,p);
		for(int i=l; i<=r; i+=1) {
			if(i<=m) {
				c[i][k]=0;
				len[i]=len[i]+1;
			} else {
				c[i][k]=1;
				len[i]=len[i]+1;
			}
		}
		fano(l,m,k,c,len,p);
		fano(m+1,r-1,k,c,len,p);
	}
}

double entrop(data_symbol *p) {
	double h=0;
	for(int i=0; i<=N; i++) if(p[i].p!=0) h+=p[i].p*(-log2(p[i].p));
	return h;
}

double l_srd(data_symbol *p, int *l) {
	double ll=0;
	for(int i=0; i<=N; i++)	ll+=l[i]*p[i].p;
	return ll;
}

void quicksort(data_symbol *arr, int n) {
	int j, k, i;
	data_symbol temp;

	for (i=0; i<n-1; i++) {
		k = i;

		for (j=i+1; j<n; j++) {
			if (arr[j].p > arr[k].p) k = j;
		}

		temp = arr[i];
		arr[i] = arr[k];
		arr[k] = temp;
	}
}

int main() {
	int l[N] {}, ll[N] {}, k=-1;
	int c[N][N] {}, cc[N][N] {};
	data_symbol mas[N];
	int bytes[N] {};
	int sum = 0;
	unsigned char x;
	ifstream infile;
	infile.open("1.txt", ios::binary | ios::in);
	while (true) {
		infile.read((char*)&x, 1);
		if(infile.eof()) break;
		bytes[x]++;
		sum++;
	}
	for (int i = 0; i < N; ++i) {
		mas[i].symbol = i;
		mas[i].p = (float)bytes[i] / (float)sum;
	}
	quicksort(mas, N);

	Shenon(mas,l,c);
	std::cout<<std::endl<<std::endl<<" Shenon:"<<std::endl;
	for (int i = 0; i < N; ++i) {
		if(mas[i].p!=0) {
			cout << (char)mas[i].symbol << "\t|\t" << mas[i].p << "\t|\t";
			for (int j = 0; j < l[i]; ++j) {
				cout << c[i][j] << "";
			}
			cout << "\t|\t" << l[i] << "\n";
		}
	}
	std::cout<<" H = "<<entrop(mas)<<std::endl<<" L srd = "<<l_srd(mas,l)<<std::endl<<std::endl<<std::endl;
	std::cout<<std::endl<<" Fano:"<<std::endl;
	fano(0,255,k,cc,ll,mas);
	for(int i=0; i<N; i+=1) {
		if(mas[i].p!=0) {
			cout << (char)mas[i].symbol << "\t|\t" << mas[i].p << "\t|\t";
			for (int j = 0; j < ll[i]; ++j) {
				cout << cc[i][j] << "";
			}
			cout << "\t|\t" << ll[i] << "\n";
		}
	}
	std::cout<<" H = "<<entrop(mas)<<std::endl<<" L srd = "<<l_srd(mas,ll)<<std::endl<<std::endl<<std::endl;
	return 0;
}
