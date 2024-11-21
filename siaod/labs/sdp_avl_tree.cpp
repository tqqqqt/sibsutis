#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

const int siz = 10;
bool rost, umen = false;

struct tree {
	int data;
	int Bal;
	tree* left;
	tree* right;
} *root_avl, *root_sdp;

struct mas {
	int data;
	int check;
};

void RL(tree *&p);
void LR(tree *&p);

void LL1(tree *&p) {
	tree *q;
	q = p->left;
	if (q->Bal == 0) {
		q->Bal = 1;
		p->Bal = -1;
		umen = false;
	} else {
		q->Bal = 0;
		p->Bal = 0;
	}
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR1(tree *&p) {
	tree *q;
	q = p->right;
	if (q->Bal == 0) {
		q->Bal = -1;
		p->Bal = 1;
		umen = false;
	} else {
		p->Bal = 0;
		q->Bal = 0;
	}
	p->right = q->left;
	q->left = p;
	p = q;
}

void BL(tree *&p) {
	if (p->Bal == -1) p->Bal = 0;
	else if (p->Bal == 0) {
		p->Bal = 1;
		umen = false;
	} else if (p->Bal == 1) {
		if (p->right->Bal >= 0) RR1(p);
		else RL(p);
	}
}

void BR(tree *&p) {
	if (p->Bal == 1) p->Bal = 0;
	else if (p->Bal == 0) {
		p->Bal = -1;
		umen = false;
	} else if (p->Bal == -1) {
		if (p->left->Bal <= 0) LL1(p);
		else LR(p);
	}
}

void DEL(tree *&q, tree *&r) {
	if (r->right != NULL) {
		DEL(q, r->right);
		if (umen == true) BR(r);
	} else {
		q->data = r->data;
		q = r;
		r = r->left;
		umen = true;
	}
}

tree* Delete_AVL(int x, tree *&p) {
	tree *q, *r;
	if (p == NULL) cout << "no point" << endl;
	else if (x < p->data) {
		Delete_AVL(x, p->left);
		if (umen == true) BL(p);
	} else if (x > p->data) {
		Delete_AVL(x, p->right);
		if (umen == true) BR(p);
	} else {
		q = p;
		if (q->left == NULL) {
			p = q->right;
			umen = true;
		} else if (q->right == NULL) {
			p = q->left;
			umen = true;
		} else {
			r = q;
			DEL(q, r->left);
			if (umen == true) BL(p);
		}
		free(q);
	}
	return p;
}

void sdp(int D, tree*& p);
void AVL(int D, tree*& p);
void obhod(tree *p);
int size(tree* p);
int check_sum(tree* p);
int height(tree* p);
int srh(tree* p, int l);
void check(int *a, struct mas *b);

int main() {
	srand(time(NULL));
	int mas[siz];
	struct mas che[101];
	int s_sdp, s_avl, sum_sdp, sum_avl, h_sdp, h_avl, count = 0, flag, temp, x;
	float srh_sdp, srh_avl;
	root_sdp = (struct tree*)malloc(sizeof(struct tree));
	root_avl = (struct tree*)malloc(sizeof(struct tree));
	root_sdp = NULL;
	root_avl = NULL;
	for (int i = 0; i < siz; i++) mas[i]=1+rand()%100;
	for(int i=0; i<101; i++) {
		che[i].data=i;
		che[i].check=0;
	}
	check(mas,che);
	for (int i = 0; i < siz; i++) {
		sdp(mas[i], root_sdp);
		AVL(mas[i], root_avl);
	}
	s_sdp = size(root_sdp);
	sum_sdp = check_sum(root_sdp);
	h_sdp = height(root_sdp);
	srh_sdp = srh(root_sdp, 1) / float(s_sdp);
	s_avl = size(root_avl);
	sum_avl = check_sum(root_avl);
	h_avl = height(root_avl);
	srh_avl = srh(root_avl, 1) / float(s_avl);
	obhod(root_avl);
	cout << endl << endl;
	cout << "       Size    Sum    Height     SRH" << endl;
	cout << "  SDP  " << s_sdp << "      " << sum_sdp << "      " << h_sdp << "      " << srh_sdp << endl;
	cout << "  AVL  " << s_avl << "      " << sum_avl << "      " << h_avl << "      " << srh_avl << endl;
	if(siz==10) for (int i = 0; i < siz+1; i++) {
			cout <<  endl << "--> ";
			cin >> x;
			if(x<0) break;
			root_avl = Delete_AVL(x, root_avl);
			obhod(root_avl);
		}
	return 0;
}

void sdp(int D, tree*& p) {
	if (p == NULL) {
		p = (struct tree*)malloc(sizeof(struct tree));
		p->data = D;
		p->left = NULL;
		p->right = NULL;
	} else if (D < p->data) {
		sdp(D, p->left);
	} else if (D >= p->data) {
		sdp(D, p->right);
	} else {
		cout << "point have" << endl;
	}
}

void LL(tree *&p) {
	tree *q;
	q = p->left;
	p->Bal = 0;
	q->Bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR(tree *&p) {
	tree *q;
	q = p->right;
	p->Bal = 0;
	q->Bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
}

void RL(tree *&p) {
	tree *q, *r;
	q = p->right;
	r = q->left;
	if (r->Bal > 0) {
		p->Bal = -1;
	} else {
		p->Bal = 0;
	}
	if (r->Bal < 0) {
		q->Bal = 1;
	} else {
		q->Bal = 0;
	}
	r->Bal = 0;
	q->left = r->right;
	p->right = r->left;
	r->left = p;
	r->right = q;
	p = r;
}

void LR(tree *&p) {
	tree *q, *r;
	q = p->left;
	r = q->right;
	if (r->Bal < 0) {
		p->Bal = 1;
	} else {
		p->Bal = 0;
	}
	if (r->Bal > 0) {
		q->Bal = -1;
	} else {
		q->Bal = 0;
	}
	r->Bal = 0;
	q->right = r->left;
	p->left = r->right;
	r->left = q;
	r->right = p;
	p = r;
}

void AVL(int D, tree *&p) {
	if(p == NULL) {
		p = new tree;
		p->data = D;
		p->left = NULL;
		p->right = NULL;
		p->Bal = 0;
		rost = true;
	} else if(p->data > D) {
		AVL(D, p->left);
		if (rost == true) {
			if (p->Bal > 0) {
				p->Bal = 0;
				rost = false;
			} else if(p->Bal == 0) {
				p->Bal = -1;
				rost = true;
			} else {
				if (p->left->Bal < 0) {
					LL(p);
					rost = false;
				} else {
					LR(p);
					rost = false;
				}
			}
		}
	} else if (p->data < D) {
		AVL(D, p->right);
		if (rost == true) {
			if(p->Bal < 0) {
				p->Bal = 0;
				rost = false;
			} else if (p->Bal == 0) {
				p->Bal = 1;
				rost = true;
			} else {
				if(p->right->Bal > 0) {
					RR(p);
					rost = false;
				} else {
					RL(p);
					rost = false;
				}
			}
		}
	} else cout << "have point";
}

void obhod(tree *p) {
	if (p != NULL) {
//		cout << p->data << " ";
		obhod(p->left);
		cout << p->data << " ";
		obhod(p->right);
	}
}

int size(tree* p) {
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int check_sum(tree *p) {
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + check_sum(p->left) + check_sum(p->right);
	return n;
}

int height(tree* p) {
	int n = 0;
	if (p == NULL) n = 0;
	else n = 1 + max(height(p->left), height(p->right));
	return n;
}

int srh(tree *p, int l) {
	int n;
	if (p == NULL) n = 0;
	else n = l + srh(p->left, l+1) + srh(p->right, l+1);
	return n;
}

void check(int *a, struct mas *b) {
	int er=0;
	for(int i=0; i<siz; i++) {
		if(a[i]==b[a[i]].data && b[a[i]].check==0) b[a[i]].check=1;
		else if(a[i]==b[a[i]].data && b[a[i]].check==1) er=1;
		while(er==1) {
			a[i]=rand()%100;
			if(a[i]==b[a[i]].data && b[a[i]].check==0) {
				b[a[i]].check=1;
				er=0;
			}
		}
	}
}
