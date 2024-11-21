#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int C, M;
const int n = 500;

struct tLE
{
	tLE *next;
	int data;
} *head, *tail;

struct Queue {
	tLE *head;
	tLE *tail;
};

void FillInc(struct tLE **head);
void FillDec(struct tLE **head);
void FillRand(struct tLE **head);
int CheckSum(struct tLE *head);
int RunNumber(struct tLE *head);
void DeleteElements(struct tLE **head);
void PrintMas(struct tLE *head);
void Split(tLE **head, tLE **head_a, tLE **head_b);
void Merge(tLE **head_a, tLE **head_b, tLE **tail, int q, int r);
void MergeSort(tLE **head, tLE **tail, int n);
void Move(struct tLE **head, struct tLE **tail);


int main()
{
	head = NULL;
	tail = (tLE *)&head;
	int i, sum, count;
	
	printf("---ASCENDING---");
	printf("\n");
	FillInc(&head);
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSum = %d", sum);
	count = RunNumber(head);
	printf("\nRunNumber = %d", count);
	MergeSort(&head, &tail, n);
	printf("\n\nSorted list:\n");
	PrintMas(head);
	printf("\n\nTheoretical compares = %3.2f \n", (n * log2(n)));
	printf("Theoretical moves = %3.2f \n", (n * log2(n) + n));
	printf("Fact compares = %d \n", C);
	printf("Fact moves = %d \n", M);
	printf("Total = %d \n", M+C);
	DeleteElements(&head);
	printf("\n\n");
	
	printf("---DESCENDING---");
	printf("\n");
	FillDec(&head);
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSum = %d", sum);
	count = RunNumber(head);
	printf("\nRunNumber = %d", count);
	MergeSort(&head, &tail, n);
	printf("\n\nSorted list:\n");
	PrintMas(head);
	printf("\n\nTheoretical compares = %3.2f \n", (n * log2(n)));
	printf("Theoretical moves = %3.2f \n", (n * log2(n) + n));
	printf("Fact compares = %d \n", C);
	printf("Fact moves = %d \n", M);
	printf("Total = %d \n", M+C);
	DeleteElements(&head);
	printf("\n\n");
	
	printf("---RANDOM---");
	printf("\n");
	FillRand(&head);
	PrintMas(head);
	sum = CheckSum(head);
	printf("\nSum = %d", sum);
	count = RunNumber(head);
	printf("\nRunNumber = %d", count);
	MergeSort(&head, &tail, n);
	printf("\n\nSorted list:\n");
	PrintMas(head);
	printf("\n\nTheoretical compares = %3.2f \n", (n * log2(n)));
	printf("Theoretical moves = %3.2f \n", (n * log2(n) + n));
	printf("Fact compares = %d \n", C);
	printf("Fact moves = %d \n", M);
	printf("Total = %d \n", M+C);
	DeleteElements(&head);
	printf("\n\n");
	
	return 0;
}

void FillInc(struct tLE **head)
{
	struct tLE *p;
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = n-i;
		p->next = *head;
		*head = p;
	}	
}

void FillDec(struct tLE **head)
{
	struct tLE *p;
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = i+1;
		p->next = *head;
		*head = p;
	}	
}

void FillRand(struct tLE **head)
{
	struct tLE *p;
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		p = (struct tLE*)malloc(sizeof(struct tLE));
		p->data = rand() % 100;
		p->next = *head;
		*head = p;
	}	
}

void PrintMas(struct tLE *head)
{
	struct tLE *p = head;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}

int CheckSum(struct tLE *head)
{
	int sum = 0;
	struct tLE *p = head;
	while (p != NULL)
	{
		sum+= p->data;
		p = p->next;
	}
	
	return sum;
}

int RunNumber(struct tLE *head)
{
	int count = 1;
	if (head != NULL)
	{
		struct tLE *p = head, *q = p->next;
		while (p->next != NULL)
		{
			q = p->next;
			if (p->data <= q->data);
			else count++;
			p = p->next;
		}
		return count;
	}
	else return 0;
}

void DeleteElements(struct tLE **head)
{
	struct tLE *p = *head;
	for (int i = 0; i < n; i++)
	{
		if (head != NULL)
		{
			p = *head;
			*head = p->next;
			free(p);
		}
	}
}

void Move(struct tLE **head, struct tLE **tail)
{
	(*tail)->next = *head;
	*tail = *head;
	*head = (*head)->next;
}

void Split(tLE **head, tLE **head_a, tLE **head_b)
{
	tLE *k, *p;
	*head_a = *head;
	*head_b = (*head)->next;
	k = *head_a;
	p = *head_b;
	M += 4;
	while (p != NULL)
	{
		k->next = p->next;
		k = p;
		p = p->next;
		M += 2;
	}
}

void Merge(tLE **head_a, tLE **head_b, tLE **tail, int q, int r)
{
	while (q != 0 && r != 0)
	{
		C++;
		if ((*head_a)->data <= (*head_b)->data)
		{
		Move(head_a, tail);
		M+=2;
		q--;
		}
		else
		{
		Move(head_b, tail);
		M+=2;
		r--;
		}
	}
	while (q > 0)
	{
		Move(head_a, tail);
		M+=2;
		q--;
	}
	while (r > 0)
	{
		Move(head_b, tail);
		M+=2;
		r--;
	}
}

void MergeSort(tLE **head, tLE **tail, int n)
{
	M = 0, C = 0;
	int i, m, q, p = 1, r;
	tLE *a = NULL, *b = NULL;
	Queue c[2];
	Split(head, &a, &b);
	while (p < n)
	{
		c[0].tail = (tLE *)&c[0].head;
		c[1].tail = (tLE *)&c[1].head;
		i = 0;
		m = n;
		while (m > 0)
		{
			if (m >= p)	q = p;
			else q = m;
			m -= q;
			if (m >= p)	r = p;
			else r = m;
			m -= r;
			Merge(&a, &b, &c[i].tail, q, r);
			i = 1 - i;
		}
		a = c[0].head;
		b = c[1].head;
		p *= 2;
	}
	c[0].tail->next = NULL;
	*head = c[0].head;
}
