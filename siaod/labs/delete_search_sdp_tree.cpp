#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct tree {
	int data;
	struct tree *left=NULL;
	struct tree *right=NULL;
}*root_sdp=NULL, *root_sdp2=NULL;

struct mas {
	int data;
	int check;
};

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

struct tree* del_sdp(int x, struct tree *root) {
	struct tree **p;
	p=&root;
	struct tree *s, *r, *q;
	while(*p!=NULL) {
		if(x<(*p)->data) p=&((*p)->left);
		else if(x>(*p)->data) p=&((*p)->right);
		else break;
	}
	if(*p!=NULL) {
		q=*p;
		if(q->left==NULL) *p=q->right;
		else if(q->right==NULL) *p=q->left;
		else {
			r=q->left;
			s=q;
			if(r->right==NULL) {
				r->right=q->right;
				*p=r;
			} else {
				while(r->right!=NULL) {
					s=r;
					r=r->right;
				}
				s->right=r->left;
				r->left=q->left;
				r->right=q->right;
				*p=r;
			}
		}
		free(q);
	}
	return root;
}

void poisk(int x, struct tree *&root) {
	struct tree *p=root;
	while(p!=NULL) {
		if(x<p->data) p=p->left;
		else if(x>p->data) p=p->right;
		else break;
	}
	if(p!=NULL) printf("\n \n Vershina naidena %d",p->data);
	else printf("\n \n Vershini net");
}

void tree_print(struct tree *p);
void check(int *a, struct mas *b);
int tree_size(struct tree *p);
int tree_height(struct tree *p);
int tree_sum(struct tree *p);
int sred_d_p(struct tree *p, int l);

int main() {
	srand(time(NULL));
	struct mas mas_check[101];
	int mas[10], k=0, vvod=0;
	for(int i=0; i<101; i++) {
		mas_check[i].data=i;
		mas_check[i].check=0;
	}
	for(int i=0; i<100; i++) mas[i]=rand()%101;
	check(mas,mas_check);
	for(int i=0; i<10; i++) sdp(mas[i],root_sdp);
	tree_print(root_sdp);
	while(k<12) {
		printf("\n\n (%d)Key delete - ",k);
		scanf("%d",&vvod);
		if(vvod>100 || vvod<0) break;
		root_sdp=del_sdp(vvod,root_sdp);
		tree_print(root_sdp);
		k+=1;
	}
	k=0;
	while(k<5) {
		printf("\n\n (%d)Key - ",k);
		scanf("%d",&vvod);
		if(vvod>100 || vvod<0) break;
		poisk(vvod,root_sdp);
		k+=1;
	}
	free(root_sdp);
	return 0;
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

int tree_size(struct tree *p) {
	int size=0;
	if(p==NULL) return 0;
	else {
		size=1+tree_size(p->left)+tree_size(p->right);
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

int tree_sum(struct tree *p) {
	int sum=0;
	if(p==NULL) return 0;
	else {
		sum=p->data+tree_sum(p->left)+tree_sum(p->right);
		return sum;
	}
}

int sred_d_p(struct tree *p, int l) {
	int sdp=0;
	if(p==NULL) sdp=0;
	else sdp=l+sred_d_p(p->left,l+1)+sred_d_p(p->right,l+1);
	return sdp;
}

void tree_print(struct tree *p) {
	if(p!=NULL) {
//		printf("%d ",p->data);
		tree_print(p->left);
		printf("%d ",p->data);
		tree_print(p->right);
	}
}
