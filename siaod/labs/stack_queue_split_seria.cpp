#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>

using namespace std;

int C = 0;
int M = 0;

struct Stack{
	Stack *Next;
	int Data;
};

struct Queue {
	Stack *Head;
	Stack *Tail;
};

void SLSeria(Stack *a, Stack *b, Stack **queue_tail, int q, int r) {	
	Stack *c = *queue_tail;
	while (q != 0 && r != 0) {
		C++;
		if (a->Data <= b->Data) {
			c->Next = a;
			c = a;
			a = a->Next;
			M++;
			q--;
		} else {
			c->Next = b;
			c = b;
			b = b->Next;
			M++;
			r--;
		}
	}
	while (q > 0) {
		c->Next = a;
		c = a;
		a = a->Next;
		M++;
		q--;
	}
	while (r > 0) {
		c->Next = b;
		c = b;
		b = b->Next;
		M++;
		r--;
	}
}

void Inc(Stack **stack_head, int n) {
	Stack *t;
	for (int i = 0; i < n; i++) {
		t = new Stack;
		t->Data = n - i;
		t->Next = *stack_head;
		*stack_head = t;
	}
}

void Dec(Stack **stack_head, int n) {
	Stack *t;
	for (int i = 0; i < n; i++) {
		t = new Stack;
		t->Data = i;
		t->Next = *stack_head;
		*stack_head = t;
	}
}

void Random(Stack **stack_head, int n) {
	Stack *t;
	for (int i = 0; i < n; i++) {
		t = new Stack;
		t->Data = rand() % 20;
		t->Next = *stack_head;
		*stack_head = t;
	}
}

void Sum(Stack *stack_head) {
	int sum = 0;
	Stack *t = stack_head;
	while (t) {
		sum += t->Data;
		t = t->Next;
	}
cout << endl << "Sum: " << sum << endl;
}

void Seria(Stack *stack_head) {
	int ser = 1;
	Stack *t = stack_head;
	while (t->Next) {
		if (t->Data > t->Next->Data) {
			ser++;
		}
		t = t->Next;
	}
	cout << "Seria: " << ser << endl;
}

void Printer(Stack *stack_head) {
	Stack *t = stack_head;
	while (t) {
		cout << t->Data << " ";
		t = t->Next;
	}
	cout << endl;
}

void Delete(Stack **stack_head) {	
	if (*stack_head == NULL)
	return;
	Stack *t = *stack_head, *prev;
	while (t) {
		prev = t;
		t = t->Next;
		delete prev;
	}
	*stack_head = NULL;
}

void Sort(Stack *stack_head) {
	Stack *left = stack_head;
	Stack *right = stack_head->Next;
	Stack *t = new Stack;
	while (left->Next) {
		while (right) {
			if (left->Data > right->Data) {
				t->Data = left->Data;
				left->Data = right->Data;
				right->Data = t->Data;
			}
			right = right->Next;
		}
		left = left->Next;
		right = left->Next;
	}
}

void Split(Stack *head, Stack **a, Stack **b, int n) {
	Stack *k;
	Stack *p;
	*a = head;
	*b = head->Next;
	n = 1;
	k = *a;
	p = *b;
	while (p!=NULL) {
		n++;
		k->Next = p->Next;
		k = p;
		p = p->Next;
	}
}

int main(){
	srand(time(NULL));
	int q=15;
	int r=12;
	C = 0;
	M = 0;
	cout << "q = " << q << endl;
	cout << "r = " << r << endl;
	Stack *stack1;
	Stack *stack2;
	Stack *stack3;
	Queue *queue;
	stack1 = NULL;
	stack2 = NULL;
	Inc(&stack1, q);
	Inc(&stack2, r);
	cout << endl << "First spis" << endl;
	Printer(stack1);
	Sort(stack1);
	cout << endl << "Sort 1 spis" << endl;
	Printer(stack1);
	Sum(stack1);
	Seria(stack1);
	cout << endl << "Second spis" << endl;
	Printer(stack2);
	Sort(stack2);
	cout << endl << "Sort 2 spis" << endl;
	Printer(stack2);
	Sum(stack2);
	Seria(stack2);
	queue->Tail = (Stack *)&queue->Head;
	SLSeria(stack1, stack2, &queue->Tail, q, r);
	cout << endl << "Queue obtained by merging two lists:" << endl;
	Printer(queue->Head);
	Sum(queue->Head);
	Seria(queue->Head);
	cout << "C(fact) = " << C << endl;
	if (q >= r) {
		cout << r << " <= C(teor) <= " << r + q - 1 << endl;
	} else
		cout << q << " <= C(teor) <= " << r + q - 1 << endl;
	cout << "M(fact) = " << M << endl;
	cout << "M(teor) = " << q + r << endl << endl;

	C = 0;
	M = 0;
	cout << endl;
	Delete(&queue->Head);
	stack1 = NULL;
	stack2 = NULL;
	
	Dec(&stack1, q);
	Dec(&stack2, r);
	
	cout << endl << "First spis" << endl;
	Printer(stack1);
	
	Sort(stack1);
	cout << endl << "Sort 1 spis" << endl;
	Printer(stack1);
	Sum(stack1);
	Seria(stack1);
	
	cout << endl << "Second spis" << endl;
	Printer(stack2);
	
	Sort(stack2);
	cout << endl << "Sort 2 spis" << endl;
	Printer(stack2);
	Sum(stack2);
	Seria(stack2);
	queue->Tail = (Stack *)&queue->Head;
	cout  << "Queue obtained by merging two lists:" << endl;
	SLSeria(stack1, stack2, &queue->Tail, q, r);
	Printer(queue->Head);
	Sum(queue->Head);
	Seria(queue->Head);
	cout << "C(fact) = " << C << endl;
	if (q >= r) {
		cout << r << " <= C(teor) <= " << r + q - 1 << endl;
	} else
		cout << q << " <= C(teor) <= " << r + q - 1 << endl;
	cout << "M(fact) = " << M << endl;
	cout << "M(teor) = " << q + r << endl << endl;

	C = 0;
	M = 0;
	cout << endl;
	Delete(&queue->Head);
	stack1 = NULL;
	stack2 = NULL;
	Random(&stack1, q);
	Random(&stack2, r);
	cout << endl << "First spis" << endl;
	Printer(stack1);
	Sort(stack1);
	cout << endl << "Sort 1 spis" << endl;
	Printer(stack1);
	Sum(stack1);
	Seria(stack1);
	cout << endl << "Second spis" << endl;
	Printer(stack2);
	Sort(stack2);
	cout << endl << "Sort 2 spis" << endl;
	Printer(stack2);
	Sum(stack2);
	Seria(stack2);
	queue->Tail = (Stack *)&queue->Head;
	cout << endl << "Queue obtained by merging two lists:" << endl;
	SLSeria(stack1, stack2, &queue->Tail, q, r);
	Printer(queue->Head);
	Sum(queue->Head);
	Seria(queue->Head);
	if (q >= r) {
		cout << r << " <= C(teor) <= " << r + q - 1 << endl;
	} else
		cout << q << " <= C(teor) <= " << r + q - 1 << endl;
	cout << "M(fact) = " << M << endl;
	cout << "M(teor) = " << q + r << endl << endl;
	Delete(&queue->Head);
}
