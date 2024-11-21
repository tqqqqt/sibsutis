#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int n=10;

struct mas {
	int data;
	int w=1+rand()%100;
};

struct vertex {
	int data;
	int w;
	vertex *right=NULL;
	vertex *left=NULL;
}*root_a1, *root_a2;

struct mass {
	int data;
	int check;
};

void quick(struct mas *a, int l, int r);
int tree_size(vertex *p);
int tree_sum(vertex *p);
int sum_w(vertex *p);
int sred_dp(vertex *p, int level);
float aver_height(vertex *p);
void check(struct mas *a, struct mass *b);

void sdp(struct vertex *&p, struct mas mas) {
	if(p==NULL) {
		p=new vertex;
		p->data=mas.data;
		p->w=mas.w;
		p->right=NULL;
		p->left=NULL;
	} else if(mas.data<p->data) sdp(p->left,mas);
	else if(mas.data>p->data) sdp(p->right,mas);
}

vertex* A1(struct mas *mas, struct vertex *root_a1){
	for(int i=0;i<n;i++){
		sdp(root_a1,mas[i]);
	}
	return root_a1;
}

vertex* A2(int l, int r, struct mas *mas, struct vertex* root_a2){
	int wes=0, sum=0, i=0;
	if(l<=r){
		for(i=l;i<r;i++) wes=wes+mas[i].w;
		for(i=l;i<r;i++){
			if(sum<float(wes/2) && sum+mas[i].w>=float(wes/2)) break;
			sum=sum+mas[i].w;
		}
		sdp(root_a2,mas[i]);
		A2(l,i-1,mas,root_a2);
		A2(i+1,r,mas,root_a2);
	}
	return root_a2;
}

void prin(struct vertex *p) {
	if(p!=NULL) {
//		cout << p->data << " ";
		prin(p->left);
		cout << p->data << " ";
		prin(p->right);
	}
}

int main(){
	srand(time(NULL));
	root_a1=new vertex;
	root_a1=NULL;
	root_a2=new vertex;
	root_a2=NULL;
	mas mas[n];
//	mass che[n+1];
//	for(int i=0;i<n+1;i++){
//		che[i].data=i;
//		che[i].check=0;
//	}
	for(int i=0; i<n; i++) {
//		mas[i].data=1+rand()%100;
		mas[i].data=i+1;
		cout << mas[i].data << "[" << mas[i].w << "] ";
	}
	cout <<endl<<endl;
//	check(mas,che);
	root_a2=A2(0,n-1,mas,root_a2);
	quick(mas,0,n);
//	root_a2=A2(0,n,mas,root_a2);
//	for(int i=0;i<n;i++) cout<<ma s[i].data<<" ";
	cout<<endl<<endl;
	root_a1=A1(mas,root_a1);
	cout<<endl<<"Prin A1: ";
	prin(root_a1);
	cout<<endl<<endl<<"Prin A2: ";
	prin(root_a2);
	cout<<endl<<endl;
	int size1=tree_size(root_a2), sum1=tree_sum(root_a2), size2=tree_size(root_a1), sum2=tree_sum(root_a1);
	float sr_height1=aver_height(root_a2), sr_height2=aver_height(root_a1);
	cout<<" n=100     Size     Summa     Sr.height" <<endl;
	cout<<" A1        "<< size2 << "        "<< sum2 << "        " << sr_height2 << endl;
	cout<<" A2        "<< size1 << "        "<< sum1 << "        " << sr_height1 << endl;
	return 0;
}

int tree_size(vertex *p) {
	int n=0;
	if (p == NULL) n = 0;
	else n = 1 + tree_size(p->left) + tree_size(p->right);
	return n;
}

int tree_sum(vertex *p) {
	int n = 0;
	if (p == NULL) n = 0;
	else n = p->data + tree_sum(p->left) + tree_sum(p->right);
	return n;
}

int sum_w(vertex *p) {
	if(p==NULL) return 0;
	else return (p->w)+sum_w(p->left)+sum_w(p->right);
}

int sred_dp(vertex *p, int level) {
	if(p==NULL) return 0;
	else return level*(p->w)+sred_dp(p->left,level+1)+sred_dp(p->right,level+1);
}

float aver_height(vertex *p) {
	return (float)sred_dp(p,1)/sum_w(p);
}

void quick(struct mas *a, int ll, int rr) {
	int k=n, temp=0;
	int l=ll, r=rr;
	while(l<r){
		for(int j=r;j>=l+1;j--){
			if(a[j].w>a[j-1].w){
				temp=a[j].w;
				a[j].w=a[j-1].w;
				a[j-1].w=temp;
				temp=a[j].data;
				a[j].data=a[j-1].data;
				a[j-1].data=temp;
				k=j;
			}
		}
		l=k;
		for(int j=l;j<=r-1;j++){
			if(a[j].w<a[j+1].w){
				temp=a[j].w;
				a[j].w=a[j+1].w;
				a[j+1].w=temp;
				temp=a[j].data;
				a[j].data=a[j+1].data;
				a[j+1].data=temp;
				k=j;
			}
		}
		r=k;
	}
}

void check(struct mas *a, struct mass *b) {
	int er=0;
	for(int i=0; i<n; i++) {
		if(a[i].data==b[a[i].data].data && b[a[i].data].check==0) b[a[i].data].check=1;
		else if(a[i].data==b[a[i].data].data && b[a[i].data].check==1) er=1;
		
		while(er==1) {
			a[i].data=1+rand()%100;
			if(a[i].data==b[a[i].data].data && b[a[i].data].check==0) {
				b[a[i].data].check=1;
				er=0;
			}
		}
	}
}
