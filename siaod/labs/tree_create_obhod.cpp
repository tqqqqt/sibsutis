#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct tree {
	int data;
	struct tree *left;
	struct tree *right;
}*p, *pp, *root=NULL;

int tree_crea() {
	int sum=0;
	root=(struct tree*)malloc(sizeof(struct tree));
	root->data=9+rand()%2;
	sum+=root->data;
	pp=root;
	p=(struct tree*)malloc(sizeof(struct tree));
	p->data=1+rand()%7;
	p->left=NULL;
	p->right=NULL;
	sum+=p->data;
	root->left=p;
	p=(struct tree*)malloc(sizeof(struct tree));
	p->data=18+rand()%3;
	p->right=NULL;
	sum+=p->data;
	root->right=p;
	pp=p;
	p=(struct tree*)malloc(sizeof(struct tree));
	p->data=14+rand()%2;
	sum+=p->data;
	pp->left=p;
	pp=p;
	p=(struct tree*)malloc(sizeof(struct tree));
	p->data=12+rand()%2;
	p->left=NULL;
	p->right=NULL;
	sum+=p->data;
	pp->left=p;
	p=(struct tree*)malloc(sizeof(struct tree));
	p->data=16+rand()%2;
	p->left=NULL;
	p->right=NULL;
	sum+=p->data;
	pp->right=p;
	return sum;
}

void tree_print_up(struct tree *p) {
	if(p!=NULL) {
		printf("%d ",p->data);
		tree_print_up(p->left);
		tree_print_up(p->right);
	}
}

void tree_print_left(struct tree *p) {
	if(p!=NULL) {
		tree_print_left(p->left);
		printf("%d ",p->data);
		tree_print_left(p->right);
	}
}

void tree_print_down(struct tree *p) {
	if(p!=NULL) {
		tree_print_down(p->left);
		tree_print_down(p->right);
		printf("%d ",p->data);
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

int main() {
	srand(time(NULL));
	int f_sum=tree_crea();
	printf(" Need sum - %d, have sum - %d\n",f_sum,tree_sum(root));
	printf(" Size - %d, height - %d, Sdp - %d, Sred-height - %d \n \n",tree_size(root),tree_height(root),sred_d_p(root,1),(sred_d_p(root,1)/tree_size(root)));
	printf("| \nV \n");
	tree_print_up(root);
	printf("\n \n \n-->\n");
	tree_print_left(root);
	printf("\n \n \n^\n|\n");
	tree_print_down(root);
	return 0;
}
