#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <bitset>

using namespace std;

struct que {
	int data;
	que *next=NULL;
};

class spisok {
	protected:
		que *head;
	public:
		spisok(void):head(new que) {
			head->next=NULL;
		}
		virtual void prin()=0;
		virtual void add(int *mas, int n)=0;
		virtual void o_add(int d)=0;
		virtual void check(int nam)=0;
};

class stek:public spisok {
	protected:
		que *p;
		static int count;
	public:
		stek(int d):p(new que) {
			p->data=d;
			if(head->next==NULL) {
				p->next=NULL;
				head->next=p;
			} else if(head->next!=NULL) {
				p->next=head->next;
				head->next=p;
			}
			count+=1;
		}
		stek(int **mas, int n, int *s) {
			for(int i=0; i<n; i++) {
				for(int j=0; j<s[i]; j++) {
					p=new que;
					p->data=mas[i][j];
					if(head->next==NULL) {
						p->next=NULL;
						head->next=p;
					} else if(head->next!=NULL) {
						p->next=head->next;
						head->next=p;
					}
				}
			}
			count+=1;
		}
		virtual void add(int *mas, int n) {
			for(int i=0; i<n; i++) {
				p=new que;
				p->data=mas[i];
				if(head->next==NULL) {
					p->next=NULL;
					head->next=p;
				} else if(head->next!=NULL) {
					p->next=head->next;
					head->next=p;
				}
			}
		}
		virtual void o_add(int d){
		}
		virtual void prin() {
			cout<<endl<<" Count stek = "<<count<<endl;
			for(p=head->next; p; p=p->next) {
				cout<<p->data<<" ";
			}
		}
		virtual void check(int nam){
			int num=0;
			try{
				cout<<endl;
				for(p=head->next;p;p=p->next){
					if(p->data>0);
					else throw(num);
					num+=1;
				}
			}
			catch(int n){
				cout<<nam<<"-stek: "<<n<<" elements <= 0. "<<endl;
			}
		}
};

class ochered:public spisok {
	protected:
		que *tail;
		que *p;
		static int count;
	public:
		ochered(int d):tail(head),p(new que) {
			p->data=d;
			tail->next=p;
			tail=p;
			tail->next=NULL;
			count+=1;
		}
		ochered(int **mas, int n, int *s):tail(head) {
			for(int i=0; i<n; i++) {
				for(int j=0; j<s[i]; j++) {
					p=new que;
					p->data=mas[i][j];
					tail->next=p;
					tail=p;
					tail->next=NULL;
				}
			}
			tail->next=NULL;
			count+=1;
		}
		virtual void add(int *mas, int n) {
			for(int i=0; i<n; i++) {
				p=new que;
				p->data=mas[i];
				tail->next=p;
				tail=p;
//				tail->next=NULL;
			}
			tail->next=NULL;
		}
		void o_add(int d){
			p=new que;
			p->data=d;
			tail->next=p;
			tail=p;
			tail->next=NULL;
		}
		virtual void prin() {
			cout<<endl<<" Count ochered = "<<count<<endl;
			for(p=head->next; p; p=p->next) {
				cout<<p->data<<" ";
			}
		}
		virtual void check(int nam){
			int num=0;
			try{
				cout<<endl;
				for(p=head->next;p;p=p->next){
					if(p->data>0);
					else throw(num);
					num+=1;
				}
			}
			catch(int n){
				cout<<nam<<"-ochered: "<<n<<" elements <= 0. "<<endl;
			}
		}
};

void ran(int **mas, int *str, int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<str[i]; j++) {
			mas[i][j]=1+rand()%50;
		}
	}
}

void rann(int **mas, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			mas[i][j]=1+rand()%50;
		}
	}
}

void right_di(int **mas, spisok *d, int n) {
	int co=0, nn=1;
	for(int i=n-1;i>=0;i--){
		int ind=i;
		for(int j=0;j<nn;j++){
			int jind=j;
			d->o_add(mas[jind][ind]);
			co++;
			jind--;
			ind++;
		}
		nn++;
	}
	nn=n-1;
	for(int i=1;i<n;i++){
		int iind=i, jind=0;
		for(int j=1;j<=nn;j++){
			d->o_add(mas[iind][jind]);
			co++; iind++; jind++;
		}
		nn--;
	}
}

void spir_var(int **a, spisok *b, int n){
	int x=n-1, y=n, d=-1, r=n*n, z=(n*n)-1;
	int res[n*n];
	for(int i=x;i>=0;d*=-1){
		for(int j=i;j>=0;j--){
			res[z]=a[x][y+=d];
			z-=1;
		}
		for(int j=--i;j>=0;j--){
			res[z]=a[x+=d][y];
			z-=1;
		}
	}
	for(int i=0;i<n*n;i++) b->o_add(res[i]);
}

int stek::count;
int ochered::count;

int main() {
	srand(time(NULL));
	spisok *el[4];
	el[0]=new ochered(-8);
	el[0]->prin();
	int **mas, *str, *dop_mas, **dop_dop_mas;
	int n=4, s=0, nn=0;
	mas=(int**)malloc(n*sizeof(int));
	str=(int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++) {
		s=1+rand()%8;
		mas[i]=(int*)malloc(s*sizeof(int));
		str[i]=s;
	}
	ran(mas,str,n);
	cout<<endl<<endl;
	el[1]=new stek(mas,n,str);
	el[1]->prin();
	nn=2+rand()%8;
	dop_mas=new int[nn];
	for(int i=0;i<nn;i++){
		dop_mas[i]=rand()%20;
	}
	el[2]=new stek(mas[0][0]);
	el[2]->add(dop_mas,nn);
	el[2]->prin();
	dop_dop_mas=new int*[n];
	for(int i=0;i<n;i++) dop_dop_mas[i]=new int[n];
	rann(dop_dop_mas,n);
//	cout<<endl<<endl<<endl;
//	for(int i=0;i<n;i++){
//		for(int j=0;j<n;j++) cout<<dop_dop_mas[i][j]<<" ";
//		cout<<endl;
//	}
	right_di(dop_dop_mas,el[0],n);
	el[0]->prin();
	el[3]=new ochered(-2);
	spir_var(dop_dop_mas,el[3],n);
	el[3]->prin();

	el[0]->check(0);
	el[1]->check(1);
	el[2]->check(2);
	el[3]->check(3);
	delete(dop_mas);
	for(int i=0;i<n;i++) delete(mas[i]);
	delete(mas);
	for(int i=0;i<n;i++) delete(dop_dop_mas[i]);
	delete(dop_dop_mas);
	delete(str);
	for(int i=0;i<4;i++) delete(el[i]);
	return 0;
}
