#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define lef 0
#define riht 99
#define last_el 100

struct tree {
	int data;
	struct tree *left=NULL;
	struct tree *right=NULL;
}*root_isdp=NULL, *root_sdp=NULL;

struct mas {
	int data;
	int check;
};

void sdp(int d, struct tree *&root){
	struct tree **p=&root;
	while(*p!=NULL){
		if(d<(*p)->data) p=&((*p)->left);
		else if(d>(*p)->data) p=&((*p)->right);
		else break;
	}
	if(*p==NULL){
		*p=new tree;
		(*p)->data=d;
		(*p)->right=NULL;
		(*p)->left=NULL;
	}
}

void sdp_v2(int d, struct tree *&adr){
	if(adr==NULL){
		adr=new tree;
		adr->data=d;
	}
	else if(d<adr->data) sdp_v2(d,adr->left);
	else if(d>adr->data) sdp_v2(d,adr->right);
	else return
}

void tree_print(struct tree *p);
int tree_size(struct tree *p);
int tree_height(struct tree *p);
int tree_sum(struct tree *p);
int sred_d_p(struct tree *p, int l);
struct tree* isdp(int l, int r, int *A);
void check(int *a, struct mas *b);
void quick(int *a, int l, int r);

int main(){
	srand(time(NULL));
	struct mas mas_check[last_el+1];
	int mas[last_el];
	for(int i=lef; i<last_el+1; i++) {
		mas_check[i].data=i;
		mas_check[i].check=0;
	}
	for(int i=lef; i<last_el; i++) mas[i]=rand()%last_el+1;
	check(mas,mas_check);
	for(int i=lef;i<last_el;i++) sdp_v2(mas[i],root_sdp);
	quick(mas,lef,riht);
	root_isdp=isdp(lef,riht,mas);
//	for(int i=lef;i<last_el;i++) sdp(mas[i],root_sdp);
	tree_print(root_sdp);
	printf("\n \n");
//	tree_print(root_isdp);
	printf("\n \n");
	float h1=sred_d_p(root_isdp,1), h2=tree_size(root_isdp), sred_h1=h1/h2;
	float h3=sred_d_p(root_sdp,1), h4=tree_size(root_sdp), sred_h2=h3/h4;
	printf("        Size     Contr. summa     Height     sr. height\n");
	printf(" ISDP %6d %12d %12d %12.2f\n",tree_size(root_isdp),tree_sum(root_isdp),tree_height(root_isdp),sred_h1);
	printf(" SDP %7d %12d %12d %12.2f\n",tree_size(root_sdp),tree_sum(root_sdp),tree_height(root_sdp),sred_h2);
	return 0;
}

struct tree* isdp(int l, int r, int *A) {
	struct tree *p;
	int m=0;
	if(l>r) return NULL;
	else {
		m=ceil((l+r)/2);
		p=new tree;
		p->data=A[m];
		p->left=isdp(l,m-1,A);
		p->right=isdp(m+1,r,A);
		return p;
	}
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

void quick(int *a, int l, int r) {
	int temp=0;
	int x=a[l], i=l, j=r;
	while(i<=j) {
		while(a[i]<x) i+=1;
		while(a[j]>x) j-=1;
		if(i<=j) {
			temp=a[j];
			a[j]=a[i];
			a[i]=temp;
			i+=1;
			j-=1;
		}
	}
	if(l<j) quick(a,l,j);
	if(i<r) quick(a,i,r);
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
