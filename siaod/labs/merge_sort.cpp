#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

struct spis {
	spis *next;
	int data;
}*head,*tail;

struct Queue {
	spis *head;
	spis *tail;
};


void Merge(spis **a, int q, spis **b, int r, Queue *c, int &C, int &M) {
	while (q != 0 && r != 0) {
		C++;
		if ((*a)->data <= (*b)->data) {
			M++;
			c->tail->next = *a;
			c->tail = *a;
			*a = (*a)->next;
			q--;
		} else {
			M++;
			c->tail->next = *b;
			c->tail = *b;
			*b = (*b)->next;
			r--;
		}
	}
	while (q > 0) {
		M++;
		c->tail->next = *a;
		c->tail = *a;
		*a = (*a)->next;
		q--;
	}
	while (r > 0) {
		M++;
		c->tail->next = *b;
		c->tail = *b;
		*b = (*b)->next;
		r--;
	}
}

int Split(spis *S, spis **a, spis **b, int &M) {
	spis *k, *p;
	*a = S;
	*b = S->next;
	int n = 1;
	k = *a;
	p = *b;
	while (p != NULL) {
		n++;
		k->next = p->next;
		k = p;
		p = p->next;
	}
	M += n;
	return n;
}

void MergeSort(spis *(&S), spis *(&tail), int &C, int &M) {
	C = M = 0;
	spis *a;
	spis *b;
	int n = Split(S, &a, &b, M);
	int p = 1; // ?????????????? ?????? ?????
	int q, r;  // ??????????? ?????? ????? a ? b
	Queue c[2];
	while (p < n) {
		c[0].tail = (spis *)&(c[0].head);
		c[1].tail = (spis *)&(c[1].head);
		int i = 0;
		int m = n; // ??????? ???-?? ????????? ? a ? b
		while (m > 0) {
			if (m >= p) q = p;
			else q = m;
			m = m - q;
			if (m >= p) r = p;
			else r = m;
			m = m - r;
			Merge(&a, q, &b, r, &c[i], C, M);
			i = 1 - i;
			cout<<i<<" ";
		}
		a = c[0].head;
		b = c[1].head;
		p = 2 * p;
	}
	c[0].tail->next = NULL;
	S = c[0].head;
	tail = c[0].tail;
	cout<<"{"<<c[0].tail->data<<"}";
}


int main() {
	int M,C;
	spis *p;
	spis mas[40];
	for(int i=0; i<40; i++) {
		mas[i].data=1+i;
	}
	head=new spis;
	tail=(spis*)head;
	for(int i=0; i<40; i++) {
		p=new spis;
		p=&mas[i];
		tail->next=p;
		tail=p;
	}
	tail->next=NULL;
	for(p=head->next; p; p=p->next) printf("%d ",p->data);
	printf("\n");
	MergeSort(head->next,tail,M,C);
	cout<<endl<<endl;
	for(p=head->next; p; p=p->next) printf("%d ",p->data);
	return 0;

}
