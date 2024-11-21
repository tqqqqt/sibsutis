#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int siz=100;

struct avl_tree {
	int data;
	int bal;
	struct avl_tree *left;
	struct avl_tree *right;
}*avl_root;

struct tree {
	int data;
	struct tree *left=NULL;
	struct tree *right=NULL;
}*root_sdp=NULL;

struct mas {
	int data;
	int check;
};

void ll(struct avl_tree *&p) {
	struct avl_tree *q;
	q=p->left;
	p->bal=0;
	q->bal=0;
	p->left=q->right;
	q->right=p;
	p=q;
}

void rr(struct avl_tree *&p) {
	struct avl_tree *q;
	q=p->right;
	p->bal=0;
	q->bal=0;
	p->right=q->left;
	q->left=p;
	p=q;
}

void lr(struct avl_tree *&p) {
	struct avl_tree *q, *r;
	q=p->left;
	r=q->right;
	if(r->bal<0) p->bal=1;
	else p->bal=0;
	if(r->bal>0) q->bal=-1;
	else q->bal=0;
	r->bal=0;
	q->right=r->left;
	p->left=r->right;
	r->left=q;
	r->right=p;
	p=r;
}

void rl(struct avl_tree *&p) {
	struct avl_tree *q, *r;
	q=p->right;
	r=q->left;
	if(r->bal>0) p->bal=-1;
	else p->bal=0;
	if(r->bal<0) q->bal=1;
	else q->bal=0;
	r->bal=0;
	q->left=r->right;
	p->right=r->left;
	r->left=p;
	r->right=q;
	p=r;
}

void add(int d, struct avl_tree *&p) {
//	bool rost=true;
	int rost=1;
	if(p==NULL) {
		p=new avl_tree;
		p->data=d;
		p->left=NULL;
		p->right=NULL;
		p->bal=0;
//		rost=true;
		rost=1;
	} else if(p->data>d) {
		add(d,p->left);
		if(rost==1) {
			if(p->bal>0) {
				p->bal=0;
//				rost=false;
				rost=0;
			} else if(p->bal==0) {
				p->bal=-1;
//				rost=true;
				rost=1;
			} else {
				if(p->left->bal<0) {
					ll(p);
//					rost=false;
					rost=0;
				} else {
					lr(p);
//					rost=false;
					rost=0;
				}
			}
		}
	} else if(p->data<d) {
		add(d,p->right);
		if(rost==1) {
			if(p->bal<0) {
				p->bal=0;
//				rost=false;
				rost=0;
			} else if(p->bal==0) {
				p->bal=1;
//				rost=true;
				rost=1;
			} else {
				if(p->right->bal>0) {
					rr(p);
//					rost=false;
					rost=0;
				} else {
					rl(p);
//					rost=false;
					rost=0;
				}
			}
		}
	}
}

void prin(struct avl_tree *p);
int ssdp(struct avl_tree *p, int l);
int tr_si(struct avl_tree *p);
int tr_su(struct avl_tree *p);
int tr_he(struct avl_tree *p);
int sred_d_p(struct tree *p, int l);
int tree_size(struct tree *p);
int tree_sum(struct tree *p);
int tree_height(struct tree *p);
void check(int *a, struct mas *b);
void sdp(int d, struct tree *&root);

int main() {
	srand(time(NULL));
//	avl_root=new avl_tree;
//	avl_root=NULL;
	struct mas che[101];
	int ma[siz];
	for(int i=0; i<101; i++) {
		che[i].data=i;
		che[i].check=0;
	}
	for(int i=0; i<siz; i++) ma[i]=rand()%100+1;
	check(ma,che);
	for(int i=0; i<siz; i++) add(ma[i],avl_root);
	for(int i=0; i<siz; i++) sdp(ma[i],root_sdp);
	prin(avl_root);
	printf("\n \n");
	float h1=ssdp(avl_root,1), h2=tr_si(avl_root), sred_h1=h1/h2;
	float h3=sred_d_p(root_sdp,1), h4=tree_size(root_sdp), sred_h2=h3/h4;
	printf("        Size     Contr. summa     Height     sr. height\n");
//	printf("%d",avl_root->right->data);
	printf(" SDP %7d %12d %12d %12.2f\n",tree_size(root_sdp),tree_sum(root_sdp),tree_height(root_sdp),sred_h2);
	printf(" AVL %7d %12d %12d %12.2f\n",tr_si(avl_root),tr_su(avl_root),tr_he(avl_root),sred_h1);
	return 44;
}

void prin(struct avl_tree *p) {
	if(p!=NULL) {
//		printf("%d ",p->data);
		prin(p->left);
		printf("%d ",p->data);
		prin(p->right);
	}
}

void sdp(int d, struct tree *&root) {
	struct tree **p=&root;
	while(*p!=NULL) {
		if(d<(*p)->data) p=&((*p)->left);
		else if(d>(*p)->data) p=&((*p)->right);
		else break;
	}
	if(*p==NULL) {
		*p=new tree;
		(*p)->data=d;
		(*p)->right=NULL;
		(*p)->left=NULL;
	}
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

int tree_size(struct tree *p) {
	int size=0;
	if(p==NULL) return 0;
	else {
		size=1+tree_size(p->left)+tree_size(p->right);
		return size;
	}
}
int tr_si(struct avl_tree *p) {
	int size=0;
	if(p==NULL) return 0;
	else {
		size=1+tr_si(p->left)+tr_si(p->right);
		return size;
	}
}

int tree_height(struct tree *p) {
	int high=0, max=0;
	if(p==NULL) return 0;
	else {
		if(tree_height(p->left)>tree_height(p->right)) max=tree_height(p->left);
		else max=tree_height(p->right);
		high=1+max;
		return high;
	}
}
int tr_he(struct avl_tree *p) {
	int high=0, max=0;
	if(p==NULL) return 0;
	else {
		if(tr_he(p->left)>tr_he(p->right)) max=tr_he(p->left);
		else max=tr_he(p->right);
		high=1+max;
		return high;
	}
}

int tree_sum(struct tree *p) {
	int sum=0;
	if(p==NULL) return 0;
	else {
		sum=p->data+tree_sum(p->left)+tree_sum(p->right);
		return sum;
	}
}
int tr_su(struct avl_tree *p) {
	int sum=0;
	if(p==NULL) return 0;
	else {
		sum=p->data+tr_su(p->left)+tr_su(p->right);
		return sum;
	}
}

int sred_d_p(struct tree *p, int l) {
	int sdp=0;
	if(p==NULL) sdp=0;
	else sdp=l+sred_d_p(p->left,l+1)+sred_d_p(p->right,l+1);
	return sdp;
}
int ssdp(struct avl_tree *p, int l) {
	int sdp=0;
	if(p==NULL) sdp=0;
	else sdp=l+ssdp(p->left,l+1)+ssdp(p->right,l+1);
	return sdp;
}
