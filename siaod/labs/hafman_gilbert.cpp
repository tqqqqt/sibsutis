#include <iostream>
#include <fstream>
#include <math.h>

const int N=256;
const int ss=100;

using namespace std;

struct data_read {
	int symbol;
	float p;
};

int Up(int n, double q, data_read *p) {
	int j=1;
	for(int i=n-1; i>=2; i-=1) {
		if(p[i-1].p<=q) p[i]=p[i-1];
		else {
			j=i;
			break;
		}
	}
	p[j].p=q;
	return j;
}

void Down(int n, int j, int c[N+1][N+1], int *L) {
	int *S=new int[N+1];
	for(int i=1; i<=N; i+=1) S[i]=c[j][i];
	int len_temp=L[j];
	for(int i=j; i<=n-2; i+=1) {
		for(int o=1; o<=N; o+=1) c[i][o]=c[i+1][o];
		L[i]=L[i+1];
	}
	for(int i=1; i<=N; i+=1) c[n-1][i]=S[i];
	for(int i=1; i<=N; i+=1) c[n][i]=S[i];
	c[n-1][len_temp+1]=0;
	c[n][len_temp+1]=1;
	L[n-1]=len_temp+1;
	L[n]=len_temp+1;
	delete[] S;
}

void Huffman(int n, data_read *p, int c[N+1][N+1], int *L) {
	double q;
	int j;
	if(n==2) {
		c[1][1]=0;
		L[1]=1;
		c[2][1]=1;
		L[2]=1;
	} else {
		q=p[n-1].p+p[n].p;
		j=Up(n,q,p);
		Huffman(n-1,p,c,L);
		Down(n,j,c,L);
	}
}

void gilbert(int n, data_read *p, int *l, int c[N+1][N+1]) {
	double *Q=new double[n];
	double pr=0;
	for(int i=0; i<n; i+=1) {
		Q[i]=pr+p[i].p/(double)2;
		pr=pr+p[i].p;
		l[i]=-ceil(log2(p[i].p))+1;
	}
	for(int i=0; i<n; i+=1) {
		for(int j=0; j<l[i]; j+=1) {
			Q[i]=Q[i]*2;
			c[i][j]=trunc(Q[i]);
			if(Q[i]>1) Q[i]=Q[i]-1;
		}
	}
	delete[] Q;
}

void quicksort(data_read *arr, int n, int flag) {
	int j, k, i, nn;
	data_read temp;

	if(flag==1){
		nn=n;
		i=1;
	} 
	else {
		nn=n-1;
		i=0;
	}
	for (i; i<n-1; i++) {
		k = i;

		for (j=i+1; j<=n; j++) {
			if(flag==1) {
				if(arr[j].p > arr[k].p) k=j;
			} else if(flag==2) {
				if (arr[j].symbol < arr[k].symbol) k = j;
			}
		}

		temp = arr[i];
		arr[i] = arr[k];
		arr[k] = temp;
	}
}

double entrop(data_read *p, int n) {
	double h=0;
	for(int i=0; i<n; i++) h+=-p[i].p*(log2(p[i].p));
	return h;
}

double l_srd(data_read *p, int *l, int n) {
	double ll=0;
	for(int i=0; i<=n; i++)	ll+=l[i]*p[i].p;
	return ll;
}

double l_srd_huf(data_read *p, int *l, int n) {
	double ll=0;
	for(int i=1; i<=n; i++)	ll+=l[i]*p[i].p;
	return ll;
}

int main() {
	int bytes[N] {};
	int count=0, sum = 0, ii=0, iii=1;
	int c[N+1][N+1] {}, l[N+1] {};
	unsigned char x;
	std::ifstream infile;
	infile.open("1.txt", ios::binary | ios::in);
	while (true) {
		infile.read((char*)&x, 1);
		if(infile.eof()) break;
		bytes[x]++;
		sum++;
	}
	for(int i=0; i<N; i++) if(bytes[i]!=0) count+=1;
	data_read *P=new data_read[count+1]{}, *P2=new data_read[count];
	int *pp=new int[count+1]{}, *pp2=new int[count]{};
	double *ppp=new double[count+1]{}, *ppp2=new double[count]{};
	for (int i = 0; i < N; ++i) {
		if(bytes[i]!=0) {
			P2[ii].symbol = i;
			P2[ii].p = (float)bytes[i] / (float)sum;
			P[iii].symbol = i;
			P[iii].p = (float)bytes[i] / (float)sum;
			ii+=1; iii+=1;
		}
	}
	for(int i=1; i<=count; i++) cout << "["<<i<<"] "<<P[i].symbol <<" |\t"<<(char)P[i].symbol<<"\t|\t"<<bytes[P[i].symbol]<< "\t|\t" << P[i].p << "\n";

	cout<<endl<<endl;
	quicksort(P,count,1);
	for(int i=1; i<=count; i++) cout << "["<<i<<"] "<<P[i].symbol <<" |\t"<<(char)P[i].symbol<<"\t|\t"<<bytes[P[i].symbol]<< "\t|\t" << P[i].p << "\n";
	for(int i=1; i<=count; i+=1) {
		pp[i]=P[i].symbol;
		ppp[i]=P[i].p;
	}
	cout<<endl<<endl;
	double entropi = entrop(P2,count);
	Huffman(count,P,c,l);
	std::cout<<" Haffman:"<<std::endl;
	for(int i=1; i<=count; i+=1) {
		if(P[i].symbol!=pp[i] || P[i].p!=ppp[i]) {
			P[i].symbol=pp[i];
			P[i].p=ppp[i];
		}
		cout<<"  "<<(char)P[i].symbol<<" \t["<<P[i].p<<"]\t - ["<<l[i]<<"] \t - \t";
		for(int j=1; j<=l[i]; j+=1) {
			cout<<c[i][j];
		}
		cout<<endl;
	}
	std::cout<<" H = "<<entropi<<std::endl<<" L srd = "<<l_srd_huf(P,l,count)<<std::endl<<std::endl<<std::endl;

	quicksort(P2,count,2);
	for(int i=0; i<count; i+=1) {
		pp2[i]=P2[i].symbol;
		ppp2[i]=P2[i].p;
	}
	std::cout<<" Gilbert:"<<std::endl;
	gilbert(count,P2,l,c);
	for(int i=0; i<count; i+=1) {
		if(P2[i].symbol!=pp2[i] || P2[i].p!=ppp2[i]) {
			P2[i].symbol=pp2[i];
			P2[i].p=ppp2[i];
		}
		cout<<"  "<<(char)P2[i].symbol<<" \t["<<P2[i].p<<"]\t - ["<<l[i]<<"] \t - \t";
		for(int j=0; j<l[i]; j+=1) {
			cout<<c[i][j];
		}
		cout<<endl;
	}
	std::cout<<" H = "<<entropi<<std::endl<<" L srd = "<<l_srd(P2,l,count)<<std::endl<<std::endl<<std::endl;

	delete[] ppp;
	delete[] pp;
	delete[] P;
	delete[] ppp2;
	delete[] pp2;
	delete[] P2;
	return 0;
}
