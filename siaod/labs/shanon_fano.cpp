#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int n = 256;

struct Byte
{
	int ASCII_symbol;
	float probability;
};

void quicksortV3(Byte* arr, int n);
void Shannon(Byte* P);
void Fano(Byte* P, int L, int R, int k);
int Median(Byte* P, int L, int R);
float AverageLengthCodeWord(Byte* P);
double Entropy(Byte* P);

float* Q;
int* Length;
int** C;

int main()
{
	srand(time(0));

	Byte P[n];
	int bytes[n] = { 0 };
	int sum = 0;
	unsigned char x;
	ifstream infile;
	infile.open("1.txt", ios::binary | ios::in);

	while (1)
	{
		infile.read((char*)&x, 1);

		if (infile.eof())
			break;

		bytes[x]++;
		sum++;

	}

	for (int i = 0; i < n; ++i)
	{
		P[i].ASCII_symbol = i;
		P[i].probability = (float)bytes[i] / (float)sum;
	}

	quicksortV3(P, n);
	double entropy_text = Entropy(P);

	Q = new float[n + 1];
	Length = new int[n];
	C = new int* [n];
	for (int i = 0; i < n; i++)	C[i] = new int[n];

	Shannon(P);
	float avg_length_code_word_SHANNON = AverageLengthCodeWord(P);

	cout << "SHANNON" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|  Symbol  |  Probability   |   Code Word   |  Length  |" << endl;
	cout << "|----------|----------------|---------------|----------|" << endl;
	for (int i = 0; P[i].probability != 0; i++)
	{
		printf("|%6c    | ", P[i].ASCII_symbol);
		printf("   %5lf    |      ", P[i].probability);
		for (int j = 0; j < Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
	}
	cout << "________________________________________________________" << endl;

	for (int i = 0; i < n; ++i)	delete C[i];
	delete[] Q;
	delete[] Length;
	delete[] C;

	cout << endl << "________________________________________________________" << endl << endl;

	Length = new int[n];
	C = new int* [n];
	for (int i = 0; i < n; i++)	C[i] = new int[n];

	for (int i = 0; i < n; ++i) {
		Length[i] = 0;
	}

	Fano(P, 0, n - 1, -1);
	float avg_length_code_word_FANO = AverageLengthCodeWord(P);

	cout << "FANO" << endl;
	cout << "________________________________________________________" << endl;
	cout << "|  Symbol  |  Probability   |   Code Word   |  Length  |" << endl;
	cout << "|----------|----------------|---------------|----------|" << endl;
	for (int i = 0; P[i].probability != 0; i++)
	{
		printf("|%6c    | ", P[i].ASCII_symbol);
		printf("   %5lf    |      ", P[i].probability);
		for (int j = 0; j < Length[i]; j++)	printf("%d", C[i][j]);
		printf("        | %5d    |", Length[i]);
		printf("\n");
	}
	cout << "________________________________________________________" << endl;

	for (int i = 0; i < n; ++i)	delete C[i];
	delete[] Length;
	delete[] C;

	cout << endl << "________________________________________________________" << endl << endl;
	cout << "________________________________________________" << endl;
	cout << "|Entropy of text | Average length of code word |" << endl;
	cout << "|                |-----------------------------|" << endl;
	cout << "|                | HUFFMAN | SHANNON | FANO | GILBERT-MUR |" << endl;
	cout << "|----------------|---------|---------|---------|" << endl;
	cout << "|     " << entropy_text << "        |         |  " << avg_length_code_word_SHANNON << "  |  " << avg_length_code_word_FANO << "  |       |" << endl;

	return 0;
}

void quicksortV3(Byte* arr, int n)
{
	int j, k, i;
	Byte temp;

	for (i = 0; i < n - 1; i++)
	{
		k = i;

		for (j = i + 1; j < n; j++)
			if (arr[j].probability > arr[k].probability) k = j;

		temp = arr[i];
		arr[i] = arr[k];
		arr[k] = temp;
	}
}

void Shannon(Byte* P)
{
	Q[0] = 0;

	for (int i = 1; i <= n; i++)
	{
		Q[i] = Q[i - 1] + P[i - 1].probability;
		Length[i - 1] = -floor(log2(P[i - 1].probability));
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < Length[i]; j++)
		{
			Q[i] *= 2;
			C[i][j] = floor(Q[i]);
			if (Q[i] >= 1) Q[i] -= 1;
		}
	}
}

void Fano(Byte* P, int L, int R, int k)
{
	int m;
	if (L < R)
	{
		k++;
		m = Median(P, L, R);
		for (int i = L; i <= R; i++)
		{
			if (i <= m) C[i][k] = 0, Length[i]++;
			else
			{
				C[i][k] = 1;
				Length[i]++;
			}
		}
		Fano(P, L, m, k);
		Fano(P, m + 1, R - 1, k);
	}
}

int Median(Byte* P, int L, int R)
{
	double Sum_L = 0;
	for (int i = L; i <= R; i++) Sum_L += P[i].probability;
	double Sum_R = P[R].probability;
	int m = R;
	while (Sum_L >= Sum_R)
	{
		m--;
		Sum_L -= P[m].probability;
		Sum_R += P[m].probability;
	}
	return m;
}

double Entropy(Byte* P)
{
	double sum = 0;
	for (int i = 0; P[i].probability != 0; i++)
	{
		sum += -P[i].probability * log2(P[i].probability);
	}
	return sum;
}

float AverageLengthCodeWord(Byte* P)
{
	float sum = 0;
	for (int i = 0; i < n; i++) sum += P[i].probability * Length[i];
	return sum;
}
