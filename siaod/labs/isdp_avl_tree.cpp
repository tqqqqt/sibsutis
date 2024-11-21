#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

const int size_array = 100;

struct vertex
{
	int data;
	int Bal;
	vertex* left;
	vertex* right;
} *root, * root_1;

void build_sdp_recursion(int D, vertex*& p);
void AVL(int D, vertex*& p);
void BYPASS_LEFT_RIGHT(vertex* p);
void Bypass_Up_Down(vertex* p);
void Bypass_Down_Up(vertex* p);
int size(vertex* p);
int control_summa(vertex* p);
int height(vertex* p);
int middle_height(vertex* p, int l);
void search(vertex* Root, int D);

int main()
{
	int B[size_array];
	int size_vertex, summa, h, count = 0, sum = 0;
	float middle_h;

	for (int i = 0; i < size_array; i++) {
		B[i] = i+1;
	}

	root = (struct vertex*)malloc(sizeof(struct vertex));
	root = NULL;
	root_1 = (struct vertex*)malloc(sizeof(struct vertex));
	root_1 = NULL;

	for (int i = 0; i < size_array; i++) {
		build_sdp_recursion(B[i], root);
	}

	for (int i = 0; i < size_array; i++) {
		AVL(B[i], root_1);
	}

	size_vertex = size(root);
	summa = control_summa(root);
	h = height(root);
	middle_h = middle_height(root, 1) / float(size_vertex);

	cout << root_1->data << endl;

	cout << "________________________________________________________________________________________________________________________";
	cout << "Bypass_Left_Right(AVL):" << endl;
	BYPASS_LEFT_RIGHT(root_1);
	cout << endl;
	cout << "Bypass_Up_Down(AVL):" << endl;
	Bypass_Up_Down(root_1);
	cout << endl;
	cout << "Bypass_Down_Up(AVL):" << endl;
	Bypass_Down_Up(root_1);
	cout << endl << "------------------------------------------------------------------------------------------------------------------------" << endl;


	int size_vertex_avl = size(root_1);
	int summa_avl = control_summa(root_1);
	int h_avl = height(root_1);
	float middle_h_avl = middle_height(root_1, 1) / float(size_vertex_avl);


	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "| n=100 | Size | Control Summa | Height | Middle height |" << endl;
	cout << "|_______|______|_______________|________|_______________|" << endl;
	cout << "| ISDP  | " << size_vertex << "  |     " << summa << "      |    " << h << "   |      " << middle_h << "      |" << endl;
	cout << "|-------|------|---------------|--------|---------------|" << endl;
	cout << "|  AVL  | " << size_vertex_avl << "  |     " << summa_avl << "      |    " << h_avl << "   |    " << middle_h_avl << "     |" << endl;
	cout << "|_______|______|_______________|________|_______________|" << endl;

	return 0;
}

void build_sdp_recursion(int D, vertex*& p)
{
	if (p == NULL)
	{
		p = (struct vertex*)malloc(sizeof(struct vertex));
		p->data = D;
		p->left = NULL;
		p->right = NULL;
	}
	else if (D < p->data)
	{
		build_sdp_recursion(D, p->left);
	}
	else if (D >= p->data)
	{
		build_sdp_recursion(D, p->right);
	}
	else
	{
		cout << "The vertex exists in the tree!" << endl;
	}
}

void LL(vertex *&p)
{
	vertex *q;
	q = p->left;
	p->Bal = 0;
	q->Bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR(vertex *&p)
{
	vertex *q;
	q = p->right;
	p->Bal = 0;
	q->Bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
}

void RL(vertex *&p)
{
	vertex *q, *r;
	q = p->right;
	r = q->left;
	if (r->Bal > 0)
	{
		p->Bal = -1;
	}
	else
	{
		p->Bal = 0;
	}
	if (r->Bal < 0)
	{
		q->Bal = 1;
	}
	else
	{
		q->Bal = 0;
	}
	r->Bal = 0;
	q->left = r->right;
	p->right = r->left;
	r->left = p;
	r->right = q;
	p = r;
}

void LR(vertex *&p)
{
	vertex *q, *r;
	q = p->left;
	r = q->right;
	if (r->Bal < 0)
	{
		p->Bal = 1;
	}
	else
	{
		p->Bal = 0;
	}
	if (r->Bal > 0)
	{
		q->Bal = -1;
	}
	else
	{
		q->Bal = 0;
	}
	r->Bal = 0;
	q->right = r->left;
	p->left = r->right;
	r->left = q;
	r->right = p;
	p = r;
}

void AVL(int D, vertex *&p)
{
	bool rost;
    if(p == NULL)
	{
        p = new vertex;
        p->data = D;
        p->left = NULL;
        p->right = NULL;
        p->Bal = 0;
        rost = true;
    }
	else if(p->data > D)
	{
        AVL(D, p->left);
        if (rost == true)
		{
            if (p->Bal > 0)
			{
                p->Bal = 0;
                rost = false;
            }
			else if(p->Bal == 0)
			{
                p->Bal = -1;
                rost = true;
            }
			else
			{
                if (p->left->Bal < 0)
				{
                    LL(p);
                    rost = false;
                }
				else
				{
                    LR(p);
                    rost = false;
                }
            }
        }
    }
	else if (p->data < D)
	{
        AVL(D, p->right);
        if (rost == true)
		{
            if(p->Bal < 0)
			{
                p->Bal = 0;
                rost = false;
            }
			else if (p->Bal == 0)
			{
                p->Bal = 1;
                rost = true;
            }
			else
			{
                if(p->right->Bal > 0)
				{
                    RR(p);
                    rost = false;
                }
				else
				{
                    RL(p);
                    rost = false;
                }
            }
        }
    }
	else cout << "Vertex already in tree!";
}

void BYPASS_LEFT_RIGHT(vertex* p)
{
	if (p != NULL)
	{
		BYPASS_LEFT_RIGHT(p->left);
		cout << p->data << " ";
		BYPASS_LEFT_RIGHT(p->right);
	}
}

void Bypass_Up_Down(vertex* p) {
	if (p != NULL)
	{
		cout << p->data << " ";
		Bypass_Up_Down(p->left);
		Bypass_Up_Down(p->right);
	}
}

void Bypass_Down_Up(vertex* p) {
	if (p != NULL)
	{
		Bypass_Up_Down(p->left);
		Bypass_Up_Down(p->right);
		cout << p->data << " ";
	}
}

int size(vertex* p)
{
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int control_summa(vertex* p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + control_summa(p->left) + control_summa(p->right);
	return n;
}

int height(vertex* p)
{
	int n = 0;
	if (p == NULL) n = 0;
	else n = 1 + max(height(p->left), height(p->right));
	return n;
}

int middle_height(vertex* p, int l)
{
	int s;
	if (p == NULL) s = 0;
	else s = l + middle_height(p->left, l + 1) + middle_height(p->right, l + 1);
	return s;
}

void search(vertex* Root, int D)
{
	vertex* p = (struct vertex*)malloc(sizeof(struct vertex));
	p = Root;
	while (p != NULL)
	{
		if (D < p->data) p = p->left;
		else if (D > p->data) p = p->right;
		else break;
	}
	if (p != NULL) cout << "Vertex found: " << p << "  | with value - " << p->data << endl;
	else cout << "Vertex not found" << endl;
}

