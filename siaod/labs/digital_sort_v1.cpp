#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

struct spis {
spis* next;
	union {
		int data;
		unsigned char Digit[sizeof(data)];
	};
};

struct tle {
	spis* head;
	spis* tail;
};

void DigitalSortInc(spis*& S, int queueLength) {
	int KDI[4] = { 3,2,1,0 };
	int j, i, d, k;
	spis* p;
	tle Q[256];
	for (j = queueLength - 1; j >= 0; j--) { 
		for (i = 0; i < 256; i++)
			Q[i].tail = (spis*)&Q[i].head;
		p = S;
		k = KDI[j];
		while (p) {
			d = p->Digit[k];
			Q[d].tail->next = p;
			Q[d].tail = p;
			p = p->next;
		}
	p = (spis*)&S; 
	for (i = 0; i < 256; i++) {
		if (Q[i].tail != (spis*)&Q[i].head) {
			p->next = Q[i].head;
			p = Q[i].tail;
		}
	}
	p->next = NULL;
	}
}

void DigitalSortDec(spis*& S, int queueLength) {
	int KDI[4] = { 3,2,1,0 };
	int j, i, d, k;
	spis* p;
	tle Q[256];
	for (j = queueLength - 1; j >= 0; j--) {
		for (i = 255; i >= 0; i--)
			Q[i].tail = (spis*)&Q[i].head;
		p = S;
		k = KDI[j];
		while (p) {
			d = p->Digit[k];
			Q[d].tail->next = p;
			Q[d].tail = p;
			p = p->next;
		}
		p = (spis*)&S;
		for (i = 255; i >= 0; i--) {
			if (Q[i].tail != (spis*)&Q[i].head) {
				p->next = Q[i].head;
				p = Q[i].tail;
			}
		}
		p->next = NULL;
	}
}

spis* rand(int n) {
	spis* head, * q;
	int i;
	head = new spis;
	head->data = rand() % (n * 2) + 1;
	head->next = 0;
	for (i = 1; i < n; i++) {
		q = new spis;
		q->data = rand() % (n * 2) + 1;
		q->next = head;
		head = q;
	}	
	return head;
}

void list(spis* head) {
	spis* p;
	p = head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}

long long int CheckSum(spis* head) {
	long long int sum = 0;
	spis* p;
	p = head;
	while (p != nullptr) {
		sum += p->data;
		p = p->next;
	}
	return sum;
}

int RunNumber(spis* head) {
	spis* p;
	p = head;
	head = p->next;
	int c = 1;
	while (head != NULL) {
		if (head->data < p->data) c++;
		p = p->next;
		head = head->next;
	}
	return c;
}

int main() {
	srand(time(NULL));
	int queueLength = 4, n = 0;
	spis* p;
	setlocale(0, "");
	
	cout << "Введите размер: ";
	cin >> n;
	cout << endl;
	
	cout << "Начальный список" << "(размер " << n << "): " << endl << endl;
	p = rand(n);
	list(p);
	cout << endl << endl;
	
	cout << "Sum = " << CheckSum(p) << ", RunNumber = " << RunNumber(p);
	cout << endl << endl << endl;
	
	cout << "Возрастающий: " << endl << endl;
	DigitalSortInc(p, queueLength);
	list(p);
	cout << endl << endl;
	
	cout << "Sum = " << CheckSum(p) << ", RunNumber = " << RunNumber(p);
	cout << endl << endl << endl;
	cout << "Убывающий: " << endl << endl;
	DigitalSortDec(p, queueLength);
	list(p);
	cout << endl << endl;
	
	cout << "Sum = " << CheckSum(p) << ", RunNumber = " << RunNumber(p);
	cout << endl << endl << endl;
	
	system("PAUSE");
}
