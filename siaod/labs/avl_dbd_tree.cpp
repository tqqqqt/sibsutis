#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int VR=1, HR=1;
bool rost;

struct vertex {
	int data;
	vertex* right;
	vertex* left;
	int bal;
}*root_dbd, *root_avl;

struct mas {
	int data;
	int check;
};

void add_dbd(int d, vertex *&p) {
	vertex *q;
	if(p==NULL) {
		p=new vertex;
		p->data=d;
		p->left=p->right=NULL;
		p->bal=0;
		VR=1;
	} else if(p->data>d) {
		add_dbd(d,p->left);
		if(VR==1) {
			if(p->bal==0) {
				q=p->left;
				p->left=q->right;
				q->right=p;
				p=q;
				q->bal=1;
				VR=0;
				HR=1;
			} else {
				p->bal=0;
				VR=1;
				HR=0;
			}
		} else HR=0;
	} else if(p->data<d) {
		add_dbd(d,p->right);
		if(VR==1) {
			p->bal=1;
			HR=1;
			VR=0;
		} else if(HR==1) {
			if(p->bal==1) {
				q=p->right;
				p->bal=0;
				q->bal=0;
				p->right=q->left;
				q->left=p;
				p=q;
				VR=1;
				HR=0;
			} else HR=0;
		}

	}
}

void pr(vertex *p) {
	if(p!=NULL) {
		pr(p->left);
		cout << p->data << " ";
		pr(p->right);
	}
}

int size(vertex *p);
int check_sum(vertex *p);
int height(vertex *p);
int srh(vertex *p, int l);
void AVL(int d,vertex *&p);
void check(int *a, mas *b);

int main() {
	srand(time(NULL));
	root_dbd=(vertex*)malloc(sizeof(vertex));
	root_dbd=NULL;
	root_avl=(vertex*)malloc(sizeof(vertex));
	root_avl=NULL;
	int mass[100];
	struct mas chec[101];
	for(int i=0; i<101; i++) {
		chec[i].data=i;
		chec[i].check=0;
	}
	for(int i=0; i<100; i++) {
//		mass[i]=1+rand()%100;
		mass[i]=i+1;
	}
//	check(mass,chec);
	for(int i=0; i<100; i++) {
		add_dbd(mass[i],root_dbd);
		AVL(mass[i],root_avl);
	}
	pr(root_dbd);
	float sred1=srh(root_dbd,1)/float(size(root_dbd)), sred2=srh(root_avl,1)/float(size(root_avl));
	cout <<endl<<endl<<endl<<"     Razmer     SUM     height     SR.height  "<<endl;
	cout <<" AVL   " << size(root_avl) <<"   -   "<< check_sum(root_avl) <<"   -   "<< height(root_avl) <<"   -   " << sred2 << endl;
	cout <<" DBD   " << size(root_dbd) <<"   -   "<< check_sum(root_dbd) <<"   -   "<< height(root_dbd) <<"   -   " << sred1 << endl;
	return 0;
}

int size(vertex* p) {
	int n;
	if (p == NULL) n = 0;
	else n = 1 + size(p->left) + size(p->right);
	return n;
}

int check_sum(vertex *p) {
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + check_sum(p->left) + check_sum(p->right);
	return n;
}

int height(vertex* p) {
	int n = 0;
	if (p == NULL) n = 0;
	else n = 1 + max(height(p->left), height(p->right));
	return n;
}

int srh(vertex *p, int l) {
	int n;
	if (p == NULL) n = 0;
	else n = l + srh(p->left, l+1) + srh(p->right, l+1);
	return n;
}

void LL(vertex *&p) {
	vertex *q;
	q = p->left;
	p->bal = 0;
	q->bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR(vertex *&p) {
	vertex *q;
	q = p->right;
	p->bal = 0;
	q->bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
}

void RL(vertex *&p) {
	vertex *q, *r;
	q = p->right;
	r = q->left;
	if (r->bal > 0) {
		p->bal = -1;
	} else {
		p->bal = 0;
	}
	if (r->bal < 0) {
		q->bal = 1;
	} else {
		q->bal = 0;
	}
	r->bal = 0;
	q->left = r->right;
	p->right = r->left;
	r->left = p;
	r->right = q;
	p = r;
}

void LR(vertex *&p) {
	vertex *q, *r;
	q = p->left;
	r = q->right;
	if (r->bal < 0) {
		p->bal = 1;
	} else {
		p->bal = 0;
	}
	if (r->bal > 0) {
		q->bal = -1;
	} else {
		q->bal = 0;
	}
	r->bal = 0;
	q->right = r->left;
	p->left = r->right;
	r->left = q;
	r->right = p;
	p = r;
}

void AVL(int D, vertex *&p) {
	if(p == NULL) {
		p = new vertex;
		p->data = D;
		p->left = NULL;
		p->right = NULL;
		p->bal = 0;
		rost = true;
	} else if(p->data > D) {
		AVL(D, p->left);
		if (rost == true) {
			if (p->bal > 0) {
				p->bal = 0;
				rost = false;
			} else if(p->bal == 0) {
				p->bal = -1;
				rost = true;
			} else {
				if (p->left->bal < 0) {
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
			if(p->bal < 0) {
				p->bal = 0;
				rost = false;
			} else if (p->bal == 0) {
				p->bal = 1;
				rost = true;
			} else {
				if(p->right->bal > 0) {
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

void check(int *a, struct mas *b) {
	int er=0;
	for(int i=0; i<100; i++) {
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
