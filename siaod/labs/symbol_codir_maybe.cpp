#include <stdio.h>
#include <stdlib.h>
#include <math.h>
char A[]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
int flag=0;

struct spis {
	struct spis* next;
	int data;
};

struct tle {
	struct spis* head;
	struct spis* tail;
};

void ran(char s[], int size) {
	for(int i=0; i<size; i++) {
		lll:
		//s[i]=A[rand()%25+1];
		s[i]=rand()%25+'A';
		for(int j=i;j>=0;j--) if(i>=1 && j!=i && s[i]==s[j]) goto lll;
	}
}

int lin_ser(char s, int pp, int m, int *hod){
	int h=0;
	struct spis* p;
	struct tle Q[m];
	h=(pp*256+(int)s)%m;
	for(p=Q[h].head->next;p;p=p->next){
		*hod+=1;
		if(p->data==(int)s) return h;
	}
	return NULL;
}

void hesh_sh(char s[], int t, int m, int* kol, int st) {
	int h=0;
	int k[t];
	struct spis* p;
	struct tle Q[m];
	for (int i = 0; i < m; i++)
		Q[i].tail = (struct spis*)&Q[i].head;
	for(int i=0; i<t; i++) {
		for (int j = 0; j < i; j++)
				if (i >= 1 && s[i] == s[j])	goto l;
		h=(h*256+(int)s[i])%m;
		p=(struct spis*)malloc(sizeof(struct spis));
		p->data=s[i];
		//strcpy(p->dat,s[i]);
		if(Q[h].tail!=(struct spis*)&Q[h].head) *kol+=1;
		Q[h].tail->next=p;
		Q[h].tail=p;
		l:;
	}
	for (int i = 0; i < m; i++)
		Q[i].tail->next = NULL;
	if(st==1) for(int i=0; i<m; i++) {
			printf(" %d- ",i);
			for(p=Q[i].head; p; p=p->next) {
				printf(" %c",p->data);
			}
			printf("\n");
		}
}

int h(char k, int i, int m) {
	int res=0;
	if(i==0) res=k%m;
	else {
		res=(k+i);
		if(res>=m) res=res%m;
	}
	return res;
}

int hash_search(int T[], char k, int m, int mmode) {
	int i=0;
	do {
		int j=h(k,i,m);
		if(T[j]==k) return j;
		if(mmode==1) i=i+1;
		else if(mmode==2){if(i==0) i=i+1; else i=i+2; }
	} while(T[i]==0 || i<=m);
	return NULL;
}

void hash_insert(int T[], char K, int m, int k[], int ff, int mode) {
	int i=0;
	do {
		int j=h(K,i,m);
		if(T[j]==NULL || T[j]==0) {
			T[j]=K;
			//printf("%d ",flag);
//			return j;
			break;
		}
		if(mode==1){i=i+1; k[ff]+=1;}
		if(mode==2){if(i==0) {i=i+1; k[ff]+=1;} else {i=i+2; k[ff]+=1;}}
	} while(i<=m);
	if(i>m) flag=1;
}

void del(int t[]){
	for(int i=0;i<80;i++) t[i]=0;
}
void del2(char t[]){
	for(int i=0;i<80;i++) t[i]=0;
}

int main() {
	int d1=13, d2=5;
	char s1[d1];
	int k=0, m=0;
	ran(s1,d1);
	printf(" Lab#1 \n Hesh tabl = %d, Elementov = %d \n",d2,d1);
	hesh_sh(s1,d1,d2,&k,1);
	k=0;
	printf("\n \n");

	//1 chast

	printf(" Razmer hesh - Kolvo symbol - Kolvo koliz \n");
	char s[80];
	ran(s,13);
	hesh_sh(s,13,11,&k,0); 
	printf(" %6d       %6d         %6d \n",11,13,k);
	k=0; del2(s);
	ran(s,17);
	hesh_sh(s,17,13,&k,0);
	printf(" %6d       %6d         %6d \n",13,17,k);
	k=0; del2(s);
	ran(s,19);
	hesh_sh(s,19,17,&k,0);
	printf(" %6d       %6d         %6d \n",17,19,k);
	k=0; del2(s);
	ran(s,23);
	hesh_sh(s,23,19,&k,0);
	printf(" %6d       %6d         %6d \n",19,23,k);
	k=0; del2(s);

	//2 chast
	printf("\n \n \n \n Lab#2 \n");
	m=11;
	int mm=13, kk[30], kk1[30], kkk1=0, kkk=0;
	//int s5[mm];
	int hes[11];
	printf("\n \n");
	for(int i=0; i<m; i++) {
		hes[i]=0;
	}
	//char s5[13];
	ran(s,13);
	
	for(int i=0; i<mm; i++) {
		//	s5[i]=rand()%15+1;
		printf(" %c",s[i]);
	}

	for(int i=0; i<mm; i++) {
		for (int j = 0; j < i; j++)
				if (i >= 1 && s[i] == s[j])	goto l2;
		hash_insert(hes,s[i],m,kk,i,1);
		l2:;
	}
	printf("\n g(i)=i \n Nomer ");
	for(int i=0; i<m; i++) {
		printf(" %3d",i);
	}
	printf("\n Symbl ");
	for(int i=0; i<m; i++) {
		printf(" %3c",hes[i]);
	}
	
	for(int i=0;i<11;i++) hes[i]=0;
	printf("\n \n");
	for(int i=0; i<mm; i++) {
		for (int j = 0; j < i; j++)
				if (i >= 1 && s[i] == s[j])	goto l1;
		hash_insert(hes,s[i],m,kk,i,2);
		l1:;
	}
	printf("\n g(i)=i^2 \n Nomer ");
	for(int i=0; i<m; i++) {
		printf(" %3d",i);
	}
	printf("\n Symbl ");
	for(int i=0; i<m; i++) {
		printf(" %3c",hes[i]);
	}
	
	for(int i=0; i<30; i++) {
		kk[i]=0; kk1[i]=0;
		hes[i]=0;
	}
	
	flag=0;
	int hes1[13], hes2[13];
	for(int i=0;i<80;i++) hes1[i]=0;
	printf("\n \n Razmer hash - Kol. symbol - Kol. koliz (lin - kvadr)\n");
	ran(s,20); flag=0;
	for(int i=0;i<20;i++){
		if(flag==1) break;
		for (int j = 0; j < i; j++)
				if (i >= 1 && s[i] == s[j])	goto l3;
		hash_insert(hes2,s[i],13,kk,i,2);
		kkk+=kk[i];
		l3:;
		//if(flag==0) printf("+");
	}
	flag=0;
	for(int i=0;i<20;i++){
		if(flag==1) break;
		for (int j = 0; j < i; j++)
				if (i >= 1 && s[i] == s[j])	goto l4;
		hash_insert(hes1,s[i],13,kk1,i,1);
		kkk1+=kk1[i];
		l4:;
		//if(flag==0) printf("+");
	}
	//printf("\n \n"); for(int i=0;i<13;i++) printf(" %c[%d]",hes1[i],i);
	printf(" %6d        %6d            %d - %d \n",13,20,kkk1,kkk);
	int hes3[23], hes4[23];
	del(hes); del(hes1); del(kk); del(kk1); kkk=0; kkk1=0;
	ran(s,20); flag=0;
	for(int i=0;i<20;i++){
		if(flag==1) break;
		for (int j = 0; j < i; j++) if (i >= 1 && s[i] == s[j])	goto l8;
		hash_insert(hes3,s[i],23,kk,i,2);
		kkk+=kk[i];
		l8:;
	}
	flag=0;
	for(int i=0;i<20;i++){
		if(flag==1) break;
		for (int j = 0; j < i; j++) if (i >= 1 && s[i] == s[j])	goto l7;
		hash_insert(hes4,s[i],23,kk1,i,1);
		kkk1+=kk1[i];
		l7:;
	}
	printf(" %6d        %6d            %d - %d \n",23,40,kkk1,kkk);
	int hes5[37],hes6[37];
	del(hes); del(hes1); del(kk); del(kk1); kkk=0; kkk1=0;
	ran(s,23); flag=0;
	for(int i=0;i<23;i++){
		if(flag==1) break;
		//for (int j = 0; j < i; j++) if (i >= 1 && s[i] == s[j])	goto l6;
		hash_insert(hes5,s[i],37,kk,i,2);
		kkk+=kk[i];
		//l6:;
	}
	flag=0;
	for(int i=0;i<23;i++){
		if(flag==1) break;
		//for (int j = 0; j < i; j++) if (i >= 1 && i != j && s[i] == s[j]) goto l5;
		hash_insert(hes6,s[i],37,kk1,i,1);
		kkk1+=kk1[i];
		//l5:;
	}
	printf(" %6d        %6d            %d - %d ",37,60,kkk1,kkk);
	
	
	// search
	printf("\n \n");
	del(hes); 
	ran(s,13); 
	for(int i=0;i<13;i++){ for (int j = 0; j < i; j++)
		//if (i >= 1 && s[i] == s[j])	goto ll; 
		hash_insert(hes,s[i],11,kk,0,1); }
	for(int i=0;i<13;i++) printf(" %c",hes[i]);
	printf("\n \n [%d]-[%c]",hash_search(hes,'H',m,1),hes[hash_search(hes,'H',m,1)]);


	//printf("\n \n %d \n \n",k);
	return 0;
}
