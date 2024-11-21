#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int n=11;
int i=0, j=0;

struct mas {
	int data;
	int w=1+rand()%100;
};

struct vertex {
	int data;
	int w;
	vertex *right=NULL;
	vertex *left=NULL;
}*root;

int tree_size(vertex *p);
int tree_sum(vertex *p);
int sum_w(vertex *p);
int sred_dp(vertex *p, int level);
float aver_height(vertex *p);

void AW_cr(int AW[n][n], struct mas *mas) {
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			AW[i][j]=AW[i][j-1]+mas[j].w;
		}
	}
}

void AP_AR(int AR[n][n], int AP[n][n], int AW[n][n]) {
	i=0;
	j=0;
	int m=0, x=0, min=0, k=0;
	int h=0;
	for(i=0; i<=n; i++) {
		j=i+1;
		AP[i][j]=AW[i][j];
		AR[i][j]=j;
	}
	for(h=2; h<n; h++) {
		for(i=0; i<n-h; i++) {
			j=i+h;
			m=AR[i][j-1];
			min=AP[i][m-1]+AP[m][j];
			for(k=m+1; k<=AR[i+1][j]; k++) {
				x=AP[i][k-1]+AP[k][j];
				if(x<min) {
					m=k;
					min=x;
				}
			}
			AP[i][j]=min+AW[i][j];
			AR[i][j]=m;
		}
	}
}

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

vertex* creat_tree(struct vertex *root, int l, int r, struct mas *m, int AR[n][n]) {
	int k=0;
	if(l<r) {
		k=AR[l][r];
		sdp(root,m[k]);
		creat_tree(root,l,k-1,m,AR);
		creat_tree(root,k,r,m,AR);
	}
	return root;
}

void prin(struct vertex *p) {
	if(p!=NULL) {
//		cout << p->data << " ";
		prin(p->left);
		cout << p->data << " ";
		prin(p->right);
	}
}

int main() {
	srand(time(NULL));
	mas mas[n];
	for(i=1; i<n; i++) {
		mas[i].data=i;
		cout << mas[i].data << "[" << mas[i].w << "] ";
	}
	cout <<endl<<endl;
	int AW[n][n]= {0}, AP[n][n]= {0}, AR[n][n]= {0};
	AW_cr(AW,mas);
	AP_AR(AR,AP,AW);
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%5d ",AW[i][j]);
		}
		cout <<endl;
	}
	cout<<endl<<endl;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%5d ",AP[i][j]);
		}
		cout <<endl;
	}
	cout<<endl<<endl;
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			printf("%5d ",AR[i][j]);
		}
		cout <<endl;
	}
	cout<<endl<<endl;
	root=creat_tree(root,0,n-1,mas,AR);
	cout<<endl;
	prin(root);
	cout<<endl<<endl;
	int size=tree_size(root), sum=tree_sum(root);
	float sr_height=aver_height(root);
	cout<<endl<<" n=100     Size     Summa     Sr.height" <<endl;
	cout<<" DOP       "<< size << "        "<< sum << "        " << sr_height << endl;
	cout<<endl<<"Need h="<<(float)AP[0][n-1]/AW[0][n-1]<<endl;
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
