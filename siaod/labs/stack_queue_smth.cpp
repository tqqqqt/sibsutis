#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int C, M;
int b[5][4];

struct stack {
	struct stack *next;
	int data;
};

struct Queue {
	stack *head;
	stack *tail;
};

void Inc(struct stack **head, int n) {
	struct stack *r;
	for (int i = 0; i < n; i++) {
		r = (stack *)malloc(sizeof(struct stack));
		r->data = n - i;
		r->next = *head;
		*head = r;
	}
}

void Dec(struct stack **head, int n) {
	struct stack *r;
	for (int i = 0; i < n; i++) {
		r = (stack *)malloc(sizeof(struct stack));
		r->data = i;
		r->next = *head;
		*head = r;
	}
}

void Rand(struct stack **head, int n) {
	srand(time(0));
	struct stack *r;
	for (int i = 0; i < n; i++) {
		r = (stack *)malloc(sizeof(struct stack));
		r->data = rand() % 20;
		r->next = *head;
		*head = r;
	}
}

void Printer(struct stack *head) {
	struct stack *r = head;
	while (r != NULL) {
		printf("%d ", r->data);
		r = r->next;
	}
printf("\n");
}

void Summ(struct stack *head) {
	struct stack *r = head;
	int Sum = 0;
	while (r != NULL) {
		Sum += r->data;
		r = r->next;
	}
printf(" Sum = %d \n", Sum);
}

void Seria(struct stack *head) {
	struct stack *r;
	int Ser = 1;
	if (head != NULL) {
		struct stack *r = head, *q = r->next;
		while (q != NULL) {
			if (r->data > q->data)
				Ser++;
				r = r->next;
				q = r->next;
		}
		printf(" Seria = %d \n ", Ser);
	}
}

void DeleteSt(struct stack **head) {
	struct stack *r = *head;
	while (r != NULL) {
		*head = r->next;
		free(r);
		r = *head;			
	}
}

void Move(struct stack **head, struct stack **tail) {
	(*tail)->next = *head;
	*tail = *head;
	*head = (*head)->next;
	(*tail)->next = NULL;
}

void SLSeria(stack **head_a, stack **head_b, stack **tail, int q, int r) {
	while (q != 0 && r != 0) {
		C++;
		if ((*head_a)->data <= (*head_b)->data) {
		Move(head_a, tail);
		M+=2;
		q--;
	} else {
		Move(head_b, tail);
		M+=2;
		r--;
	}
	}
	while (q > 0) {
		Move(head_a, tail);
		M+=2;
		q--;
	}
	while (r > 0) {
		Move(head_b, tail);
		M+=2;
		r--;
	}
}

void Split(stack **head, stack **head_a, stack **head_b) {
	stack *k, *p;
	*head_a = *head;
	*head_b = (*head)->next;
	k = *head_a;
	p = *head_b;
	M += 4;
	while (p != NULL) {
		k->next = p->next;
		k = p;
		p = p->next;
		M += 2;
	}
}

void MergeSort(stack **head, stack **tail, int n) {
	M = 0, C = 0;
	int i, m, q, p = 1, r;
	stack *a = NULL, *b = NULL;
	Queue c[2];
	Split(head, &a, &b);
	while (p < n) {
		c[0].tail = (stack *)&c[0].head;
		c[1].tail = (stack *)&c[1].head;
		i = 0;
		m = n;
	while (m > 0) {
		if (m >= p)
		q = p;
		else
			q = m;
			m -= q;
			if (m >= p)
			r = p;
				else
					r = m;
					m -= r;
					SLSeria(&a, &b, &c[i].tail, q, r);
					i = 1 - i;
	}
	a = c[0].head;
	b = c[1].head;
	p *= 2;
	}
	c[0].tail->next = NULL;
	*head = c[0].head;
}

void tabl() {
	int n = 500, compare = 0, move = 0, matry = 1, matrx = 0;
	srand(time(0));
	stack *head, *tail;
	head = NULL;
	tail = (stack *)&head;
	b[0][0] = 100;
	b[1][0] = 200;
	b[2][0] = 300;
	b[3][0] = 400;
	b[4][0] = 500;
	M = 0;
	C = 0;

	for (int i = 400; i >= 0; i -= 100) {
		Rand(&head, n - i);
		MergeSort(&head, &tail, n - i);
		b[matrx][matry] = M + C;
		M = 0;
		C = 0;
		matry++;
		Dec(&head, n - i);
		MergeSort(&head, &tail, n - i);
		b[matrx][matry] = M + C;
		M = 0;
		C = 0;
		matry++;
		Inc(&head, n - i);
		MergeSort(&head, &tail, n - i);
		b[matrx][matry] = M + C;
		M = 0;
		C = 0;
		matrx++;
		matry = 1;
		DeleteSt(&head);
	}
	printf("\n");
	printf(" N Rand Dec Inc");
	for (int i = 0; i < 5; i++) {
		printf("\n\n");
	for (int j = 0; j < 4; j++) {
		printf("%d ", b[i][j]);
	}
	}
}

int main() {
	stack *head, *tail;
	head = NULL;
	tail = (stack *)&head;
	int n = 10;
	
	Rand(&head, n);
	Printer(head);
	MergeSort(&head, &tail, n);
	Printer(head);
	
	printf("C(teor) = %f \n", (n * log2(n)));
	printf("M(teor) = %f \n", (n * log2(n) + n));
	printf("C(prac) = %d \n", C);
	printf("M(prac) = %d \n", M);
	Seria(head);
	Summ(head);
	DeleteSt(&head);
	printf("\n");
	
	Inc(&head, n);
	Printer(head);
	MergeSort(&head, &tail, n);
	Printer(head);
	
	printf("C(prac) = %d \n", C);
	printf("M(prac) = %d \n", M);
	Seria(head);
	Summ(head);
	DeleteSt(&head);
	printf("\n");
	
	Dec(&head, n);
	Printer(head);
	MergeSort(&head, &tail, n);
	Printer(head);
	
	printf("C(prac) = %d \n", C);
	printf("M(prac) = %d \n", M);
	Seria(head);
	Summ(head);
	DeleteSt(&head);
	printf("\n");
	tabl();
	return 0;
}
