#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct tree {
	int data;
	struct tree *left=NULL;
	struct tree *right=NULL;
}*root, *pp;

struct mas {
	int data;
	int check;
};

struct tree* isdp(int l, int r, int *A){
	int m=0;
	struct tree *p;
	if(l>r) return NULL;
	else{
		m=ceil((l+r)/2);
		p=(struct tree*)malloc(sizeof(struct tree));
		p->data=A[m];
		p->left=isdp(l,m-1,A);
		p->right=isdp(m+1,r,A);
		return p;
	}
}

void tree_print_up(struct tree *p) {
	if(p!=NULL) {
//		printf("%d ",p->data);
		tree_print_up(p->left);
		printf("%d ",p->data);
		tree_print_up(p->right);
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

int main() {
	srand(time(NULL));
	struct mas b[101];
	int A[100], f_sum=0;
	for(int i=0; i<101; i++) {
		b[i].data=i;
		b[i].check=0;
	}
	for(int i=0; i<100; i++) A[i]=rand()%101;
	check(A,b);
	quick(A,0,99);
	for(int i=0; i<100; i++) {
//		printf("%d ",A[i]);
		f_sum+=A[i];
	}
//	printf("\n \n");
	root=isdp(0,99,A);
	float h1=sred_d_p(root,1), h2=tree_size(root), sred_h=h1/h2;
	printf("\n \n Left -> ");
	tree_print_up(root);
	printf("\n \n Need sum - %d, have sum - %d\n",f_sum,tree_sum(root));
	printf(" Size - %d, height - %d, Sdp - %d, Sred-height - %2.2f \n \n",tree_size(root),tree_height(root),sred_d_p(root,1),sred_h);
	return 0;
}
