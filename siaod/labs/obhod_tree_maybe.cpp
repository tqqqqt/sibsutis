#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

struct dvoich_tree{
	int data;
	struct dvoich_tree *left;
	struct dvoich_tree *right;
} *l, *root=NULL, *p;

int new_tree(){
	int s=0;
	root=(struct dvoich_tree*)malloc(sizeof(struct dvoich_tree));
	root->data=13+rand()%3; 
	s=s+root->data;
	l=root;
	p=(struct dvoich_tree*)malloc(sizeof(struct dvoich_tree));
	p->data=16+rand()%2;
	p->left=NULL;
	s=s+p->data;
	root->right=p;
	l=p;
	p=(struct dvoich_tree*)malloc(sizeof(struct dvoich_tree));
	p->data=18+rand()%3;
	p->left=NULL;
	p->right=NULL;
	s=s+p->data;
	l->right=p;
	p=(struct dvoich_tree*)malloc(sizeof(struct dvoich_tree));
	p->data=8+rand()%2;
	s=s+p->data;
	root->left=p;
	l=p;
	p=(struct dvoich_tree*)malloc(sizeof(struct dvoich_tree));
	p->data=1+rand()%6;
	p->right=NULL;
	p->left=NULL;
	s=s+p->data;
	l->left=p;
	p=(struct dvoich_tree*)malloc(sizeof(struct dvoich_tree));
	p->data=11+rand()%2;
	p->left=NULL;
	p->right=NULL;
	s=s+p->data;
	l->right=p;
	return s;
}
int sizee(struct dvoich_tree *p){
	int s=0;
	if(p==NULL) return 0;
	else{
		s=1+sizee(p->left)+sizee(p->right);
		return s;
	}
}
int heightt(struct dvoich_tree *p){
	int h=0, max=0;
	if(p==NULL) return 0;
	else{
		if(heightt(p->left)>heightt(p->right)) max=heightt(p->left);
		else max=heightt(p->right);
		h=1+max;
		return h;
	}
}
int summ(struct dvoich_tree *p){
	int s=0;
	if(p==NULL) return 0;
	else{
		s=p->data+summ(p->left)+summ(p->right);
		return s;
	}
}
int s_d_p(struct dvoich_tree *p, int l){
	int sdp=0;
	if(p==NULL) sdp=0;
	else sdp=l+s_d_p(p->left,l+1)+s_d_p(p->right,l+1);
	return sdp;
}
void tree_up(struct dvoich_tree *p){
	if(p!=NULL){
		printf("%d ",p->data);
		tree_up(p->left);
		tree_up(p->right);
	}
}
void tree_left(struct dvoich_tree *p){
	if(p!=NULL){
		tree_left(p->left);
		printf("%d ",p->data);
		tree_left(p->right);
	}
}
void tree_down(struct dvoich_tree *p){
	if(p!=NULL){
		tree_down(p->left);
		tree_down(p->right);
		printf("%d ",p->data);
	}
}

int main(){
	srand(time(NULL));
	int need_sum=new_tree(), have_sum=summ(root), size=sizee(root), height=heightt(root), sdp=s_d_p(root,1);
	printf("Need summ %d = %d\n",need_sum,have_sum);
	printf("Tree size = %d, height = %d\nSdp = %d, Sred-high = %d \n \n",size,height,sdp,(sdp/size));
	printf("Down \n");
	tree_up(root);
	printf("\n \nRight\n");
	tree_left(root);
	printf("\n \nUp\n");
	tree_down(root);
	return 0;
}
