#include <iostream>
#include <ctime>
#include <cmath>
#include <locale.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

void FillInc(int a[], int n) //заполнение массива возрастающими числами 
{
	for (int i=1; i<=n; i++) 
		a[i]=i;
}

void FillDec(int a[], int n) //заполнение массива убывающими числами
{
    for (int j = n, i = 1; i <= n; j--, i++)
        a[i] = j;
        return;
}


void FillRand(int a[], int n) //заполнение массива рандомными числами 
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
        a[i] = rand() % n;
        return;
}

void PrintMas (int a[], int n)
{
	for (int i=1; i<=n; i++) 
		cout << a[i] <<" ";
	cout <<endl;
}

void InsertSort(int a[], int n) 
{
    int t, j;
    for (int i = 2; i <= n; i++) {
        t = a[i];
        j = i - 1;
         while ((j > 0) && (t < a[j])) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = t; 
    }
}

void BSearch1 (int a[], int n, int X)
{
	int L=1, R=n, m=0, C=0; 
	bool found=0;
	while (L<=R) 
	{
		m=(L+R)/2;
		C++;
		if (a[m]==X) 
		{
			found=1;
		}
		C++;
		if (a[m]<X) L=m+1;
		else R=m-1;
	}
	cout <<setw(15) <<C;
}

void BSearch2 (int a[], int n, int X)
{
	int L=1, R=n, m=0, C=0; 
	bool found=0;
	while (L<R) 
	{
		m=(L+R)/2;
		C++;
		if (a[m]<X) L=m+1;
		else R=m;
	}
	C++;
	if (a[R]==X) found=1;
	else found=0;
	cout <<setw(15) <<C;
}

void BSearchAll1 (int a[], int n, int X)
{
	int L=1, R=n, m=0, k=0, C=0; 
	while (L<=R) 
	{
		m=(L+R)/2;
		C++;
		if (a[m]==X) 
		{
			k++;
			for (int left=1; left<m; left++)
			{
				C++;
				if (a[left]==X) ;
			}
			int M=m+1;
			for (M; M<=n; M++)
			{
				C++;
				if (a[M]==X);
			}
		}
		C++;
		if (a[m]<X) L=m+1;
		else R=m-1;
	}
	if (k==0) ;
	cout <<setw(15) <<C;
}

void BSearchAll2 (int a[], int n, int X)
{
	int L=1, R=n, m=0, k=0, C=0; 
	while (L<R) 
	{
		m=(L+R)/2;
		C++;
		if (a[m]<X) L=m+1;
		else R=m;
	}
	C++;
	if (a[R]==X) 
	{
		int M=R+1;
		for (M; M<=n; M++)
		{
			C++;
			if (a[M]==X) ;
		}
	}
	cout <<setw(15) <<C;
}

int main() 
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout <<"N  |" <<"    C(BSearch1)" <<"    C(BSearch2)"  <<"   C(BSearchAll1)" <<"   C(BSearchAll2)"<<endl;
	for (int n=100; n<=1000; n+=100)
	{
		int* a;
        a = new int[n];
		cout <<n <<"|";
		
		FillInc(a,n);
		BSearch1(a,n,5);
		
		FillInc(a,n);
		BSearch2(a,n,5);
		
		FillRand(a, n);
    	InsertSort(a, n);
		BSearchAll1(a, n, 5);
	
		FillRand(a, n);
    	InsertSort(a, n);
		BSearchAll2 (a, n, 5);
		
		cout <<endl;
	}
}
