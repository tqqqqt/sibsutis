#include <iostream>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

#define N 256
#define WINDOW 5

struct Symbol {
	unsigned char s;
	double p;
};

void quicksort(Symbol *arr, int n);
float Round(float var);
void Arithmetic(fstream *in, fstream *out, int count);
string toBinary(double n, int len);

int *L;
int **C;
double *Q;
Symbol *P;

int main(void) {
//	srand(time(NULL));

	Symbol p_temp[N];
	int bytes[N] = {0};
	int count_in = 0;
	int count_in_real = 0;
	int count_out = 0;
	int i, j;
	unsigned char x;
	fstream infile1;
	fstream infile2;
	fstream outfile1;
	fstream outfile2;
	infile1.open("1.txt", ios::binary | ios::in);

	while (infile1 >> x) {
		bytes[x]++;
		count_in++;
	}

	infile1.close();

	for (i = 0; i < N; ++i) {
		p_temp[i].s = i;

		if (bytes[i]) {
			p_temp[i].p = (double)bytes[i] / (double)count_in;
			count_in_real++;
		} else {
			p_temp[i].p = 0;
		}
	}

	P = new Symbol[count_in_real];
	Q = new double[count_in_real+1];

	for (i = 0, j = 0; i < count_in_real; i++) {
		for (; j < N; j++)
			if (p_temp[j].p != 0)
				break;

		P[i] = p_temp[j];
		Q[i+1] = Q[i] + P[i].p;
		j++;

		// cout << P[i].s << " " << P[i].p << " " << Q[i+1] << "\n";
	}

	infile2.open("1.txt", ios::binary | ios::in);
	outfile1.open("file.out");
	Arithmetic(&infile2, &outfile1, count_in_real);
	infile2.close();
	outfile1.close();

	outfile2.open("file.out", ios::binary | ios::in);

	while (outfile2 >> x)
		count_out++;

	cout << (float)count_out / (float)(count_in * 8) << "\n";

	outfile2.close();

	return 0;
}

void Arithmetic(fstream *in, fstream *out, int count) {
	double l[WINDOW+1];
	double h[WINDOW+1];
	double r[WINDOW+1];
	int m;
	unsigned char x;
	unsigned char a[WINDOW];

	while (*in >> x) {
		l[0] = 0;
		h[0] = 1;
		r[0] = 1;
		a[0] = x;

		for (int i = 1; i < WINDOW; ++i)
			(*in).read((char*)&a[i], 1);

		for (int i = 0; i < WINDOW; ++i) {
			for (int j = 0; j < count; ++j) {
				if (P[j].s == a[i]) {
					m = j + 1;
					break;
				}
			}

			l[i+1] = l[i] + r[i] * Q[m-1];
			h[i+1] = l[i] + r[i] * Q[m];
			r[i+1] = h[i+1] - l[i+1];
			// cout << l[i+1] << " " << h[i+1] << " " << r[i+1] << "\n";
		}

		// cout << "-----------------------------\n\n";
		// cout << l << " " << h << " " << r << "\n";
		// cout << h[WINDOW] << " " << toBinary(h[WINDOW], -floor(log2(r[WINDOW]))) << "\n";
		// cout << r[WINDOW].f;
		// for (int pos = 31; pos != 0; --pos) {
			// cout << (r[WINDOW].i>>pos&1);
		// }
		
		(*out) << toBinary(h[WINDOW], -floor(log2(r[WINDOW])));
	}
}

string toBinary(double n, int len)
{
	if (n >= 1 || n <= 0)
		return "ERROR";
	
	string tmp = "";
	string answer = "";
	double frac = 0.5;

	while (n > 0)
	{
		// if (answer.length() == len)
		// 	return answer;

		// Multiply n by 2 to check it 1 or 0
		double b = n * 2;
		if (b >= 1)
		{
			tmp.append("1");
			n = b - 1;
		}
		else
		{
			tmp.append("0");
			n = b;
		}
	}

	for (int i = tmp.size() - 1; i > tmp.size() - len - 1; i--)
		answer += tmp[i];
	
	return answer;
}

void quicksort(Symbol *arr, int n) {
	int j, k, i;
	Symbol temp;

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

float AverageLengthCodeWord(Symbol* P) {
	float sum = 0;

	for (int i = 0; i < N; i++)
		if (L[i] > 0)
			sum += P[i].p * L[i];

	return sum;
}

float Round(float var) {
	float value = (int)(var * 10000 + .5);

	return (float)value / 10000;
}
