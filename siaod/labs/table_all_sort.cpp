#include <iostream>
#include <ctime>
#include <cmath>
#include <locale.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
}


void FillRand(int a[], int n) //заполнение массива рандомными числами 
{
    srand(time(NULL));
    for (int i = 1; i <= n; i++)
        a[i] = rand() % n;
}


void PrintMas (int a[], int n)
{
	for (int i=1; i<=n; i++) 
		cout << a[i] <<" ";
	cout <<endl;
}

void SelectSort (int a[], int n)
{
	int C=0, M=0, k, add;
	for (int i=1; i<=n-1; i++) 
	{
		k=i;
		for (int j=i+1; j<=n; j++) 
		{
			C++;
			if (a[j]<a[k]) k=j;
		}
		add=a[i];
		a[i]=a[k];
		a[k]=add;
		M+=3;
	}
	cout << setw(15) << C + M << "     ";
}

void BubbleSort(int a[], int n) 
{
    int k, C = 0, M = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = n; j >= i + 1; j--) {
            C++;
            if (a[j] < a[j - 1]) {
                k = a[j];
                a[j] = a[j - 1];
                a[j - 1] = k;
                M += 3;
            }
        }
    }
    cout << setw(15) << C + M << "     ";
}

void ShakerSort(int a[], int n)
{
    int L = 1, R = n, k = n, t, M = 0, C = 0; 
    while (L < R) {
        for (int j = R; j >= L + 1; j--) {
            C++;
            if (a[j] < a[j - 1]) {
                t = a[j];
                a[j] = a[j - 1];
                a[j - 1] = t;
                k = j;
                M += 3;
            }
        }
        L = k;
        for (int j = L; j <= R - 1; j++) {
            C++;
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                k = j;
                M += 3;
            }
        }
        R = k;
   }
   cout << setw(15) << C + M << "     ";
}

void InsertSort(int a[], int n) 
{
    int t, j, M = 0, C = 0;
    for (int i = 2; i <= n; i++) {
    	M++;
        t = a[i];
        j = i - 1; 
        while ((j > 0) && (t < a[j])) {
            C++;
            a[j + 1] = a[j];
            j--;
            M ++;
        }
        a[j + 1] = t; 
        M++;
	}
	cout << setw(15) << C + M << "     ";
}

int ShellSort(int a[], int n)
{
    int h = 1, C = 0, M = 0, j, t, i;
    int m = log10(n)/log10(2) - 1;
    for (int f = 1; f < m; f++) 
        h = 2 * h + 1;

    for (int k = h; k >= 1; k /= 2) {
        for (i = k+1; i <= n; i++) {
            t = a[i];
            j = i - k;

            while((j > 0) && (t < a[j])) {
                C++;
                a[j + k] = a[j];
                j = j - k;
                M++;
            }
            a[j + k] = t;
            M++;
        }
    }
    cout << setw(15) << C + M << "     ";
}

int Heapify(int a[], int L, int n, int *M, int *C)
{
	//int C, M;
    int R = n;
    int x = a[L];
    int i = L;
    *M+=1;

    do {
        int j = 2 * i;
      //  *C+=1;
        if (j > R) break;
        *C+=1;
        if (j < R && a[j + 1] <= a[j])
            j++;
        *C+=1;
        if (x <= a[j]) break;
        a[i] = a[j];
        i = j;
        *M+=1;
    } while (true);

    a[i] = x;
    *M+=1;
    
}

int HeapSort(int a[], int n, int *M, int *C)
{
	//int C=0, M=0;
	//int *C, *M;
    int L = n / 2;
    while (L > 0) {
        Heapify(a, L, n, M, C );   
        L--;
    }
	
    int R = n, t;
    while (R > 1) {
    	*M+=3;
        t = a[1];
        a[1] = a[R];
        a[R] = t;
        R--;
        Heapify(a, 1, R, M, C);
    }
   
}

void QuickSort(int a[], int L, int R)
{
    int M = 0, C = 0, k;
    int i = L, j = R;
    int x = a[L];

    while (i <= j){
        C++;
        while (a[i] < x){
            C++;
            i++;
        }
        while (a[j] > x){
            C++;
            j--;
        } 
        if (i <= j){
            k = a[i];
            a[i] = a[j];
            a[j] = k;
            M +=3;
            i++;
            j--;
        }
    }
    if (L < j) QuickSort(a,L,j);
    if (i < R) QuickSort(a,i,R);
    cout << setw(15) << C + M << "     ";
}

int main()
{
	setlocale (LC_ALL, "Russian");
	int n;
    cout  <<"N  " <<"|" /*<<"    Rand(Select)  " <<setw(15) <<"      Rand(Bubble)" <<setw(15) <<"        Rand(Shaker)" <<setw(15) <<"        Rand(Insert)" <<setw(15) <<"         Rand(Shell)"  <<setw(15) */ <<"        Inc(Heap)" <<setw(15) <<"        Dec(Heap)" <<setw(15) <<"        Rand(Heap)"   <<endl;
    for (int n=100; n<=500; n+=100)
    {
    	int* a;
        a = new int[n];
    	cout <<n <<"|";
    	
    //	FillRand(a, n);
    //	SelectSort(a, n);
    	
    //	FillRand(a, n);
    //	BubbleSort(a, n);
    	
    //	FillRand(a, n);
    //	ShakerSort(a, n);
    	
    //	FillRand(a, n);
    //	InsertSort(a, n);
    	
    //	FillRand(a, n);
    //	ShellSort(a, n);
    	int C=0, M=0;
    	FillInc(a, n);
    	HeapSort(a, n, &M, &C);
    	cout <<setw(15) <<C+M;
    	
        C=0, M=0;
    	FillDec(a, n);
    	HeapSort(a,n, &M, &C);
    	cout <<setw(15) <<C+M;
    	
    	C=0, M=0;
    	FillRand(a, n);
    	HeapSort(a,n, &M, &C);
    	cout <<setw(15) <<C+M;
    	
    //	FillRand(a,n);
    //	QuickSort(a,1,n);
    	
    	cout <<endl;
    	
    	
	}

   
    return 0;
}
