#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

#define scan_gets 1
#define left_corn 0
#define right_corn 3999
// 3 36 57 / 49 80 103

int ha=1;

struct data {
	char name_vklad[30];
	unsigned short int sum;
	char date_vklad[10];
	char name_advok[22];
} t1;

struct Queue {
	struct Queue* next;
	struct data* address;
}*queue_point, *print_mark, *last_element;

struct vertex {
	struct data* address;
	int w;
	struct vertex* right=NULL;
	struct vertex* left=NULL;
	struct vertex* center=NULL;
}*root=NULL;

struct mas {
	struct data* address;
	int w=1+rand()%100;
};

void sdp(vertex *&root, mas mas);
struct vertex* del_sdp(struct mas x, struct vertex* root);
void del_que(struct Queue *head);
void quick(struct mas *a, int l, int r);
void scan_input(char input2[4]);
void prin(struct vertex *p, int center);
void prinn(struct data** index_array, struct data* data_base, int mode_print);
void obrprin(struct data** index_array);
void printnt(struct Queue *head);
void tree_search(struct vertex *root);

int less_tree_found(char Key[], struct vertex *p) {
	int size=strlen(Key);
	for(int i=0; i<size; i++) {
		if(Key[i]<p->address->name_advok[i]) return -1;
		else if(Key[i]>p->address->name_advok[i]) return 1;
	}
	return 0;
}

int less_found(struct data *mas, char Key[], int var) {
	int size;
	if(var==1) size=strlen(Key);
	else size=3;
	for(int i=0; i<size; i++) {
		if(mas->name_vklad[i]<Key[i]) return -1;
		else if(mas->name_vklad[i]>Key[i]) return 1;
	}
	return 0;
}

void found(struct data **index_array, int *pos) {
	int left=left_corn, right=right_corn, m=0, result_les=0;
	char input[5];
	bool find=false;

	fflush(stdin);
	system("CLS");
	printf(" \n Key - ");
	if(scan_gets==1) scanf("%s",input);
	else if(scan_gets==2) {
		fgets(input,5,stdin);
		input[strlen(input)-1]='\0';
	}

	while(left<right) {
		m=(left+right)/2;
		result_les=less_found(index_array[m],input,1);
		if(result_les==1) {
			left=m+1;
		} else right=m;
	}

	result_les=less_found(index_array[right],input,1);
	if(result_les==0) {
		find=true;
	} else find=false;

	if(find==true) *pos=right;
	else *pos=-5;
}

int less_vertex(struct mas X, char Y[]) {
	if(strcmp(X.address->name_advok,Y)>0) return 1;
	else if(strcmp(X.address->name_advok,Y)<0) return -1;
	else return 0;
}

int less(struct data* X, struct data* Y) {
	if(strcmp(X->name_vklad,Y->name_vklad)>0) return 1;
	else if(strcmp(X->name_vklad,Y->name_vklad)<0) return -1;
	else if(X->sum>Y->sum) return 1;
	else if(X->sum<Y->sum) return -1;
	else return 0;
}

void HeapCreate(struct data** index_array, int left, int right) {
	struct data* x=index_array[left];
	struct data* obm;
	int i=left, j=0;
	while(true) {
		j=2*i;
		if(j>right) break;
		if((j<right) && less(index_array[j+1],index_array[j])<=0) j=j+1;
		if(less(x,index_array[j])<=0) break;
		index_array[i]=index_array[j];
		i=j;
	}
	index_array[i]=x;
}

void HeapSort(struct data** index_array) {
	int left=ceil(4000/2), right=right_corn;
	struct data* change_temp;
	while(left>=0) {
		HeapCreate(index_array,left,right_corn);
		left=left-1;
	}
	while(right>=0) {
		change_temp=index_array[0];
		index_array[0]=index_array[right];
		index_array[right]=change_temp;
		right=right-1;
		HeapCreate(index_array,0,right);
	}
}

void crea_qu(int position, int *kolvo, struct data **index_array, struct Queue *last_element) {
	int result=0;
	for(int i=position; i<right_corn+1; i++) {
		result=less_found(index_array[i],index_array[position]->name_vklad,0);
		if(result==0) {
			queue_point=(struct Queue*)malloc(sizeof(struct Queue));
			queue_point->address=index_array[i];
			last_element->next=queue_point;
			last_element=last_element->next;
			*kolvo+=1;
		}
	}
	last_element->next=NULL;
}

void alt_crea_qu(int position, int *kolvo, struct data **index_array, struct Queue *last_element) {
	int result=0, right_position=0;
	for(int i=position; i<right_corn+1; i++) {
		result=less_found(index_array[i],index_array[position]->name_vklad,0);
		if(result==0) {
			right_position=i;
		}
	}
	for(int i=right_position; i>position-1; i--) {
		queue_point=(struct Queue*)malloc(sizeof(struct Queue));
		queue_point->address=index_array[i];
		last_element->next=queue_point;
		last_element=last_element->next;
		*kolvo+=1;
	}
	last_element->next=NULL;
}

void A2(int left, int right, struct mas *mas) {
	int wes=0, sum=0, shetchik=0;
	if(left<=right) {
		for(shetchik=left; shetchik<right; shetchik++) wes=wes+mas[shetchik].w;
		for(shetchik=left; shetchik<right; shetchik++) {
			if((sum<float((wes/2))) && ((sum+mas[shetchik].w)>float((wes/2)))) break;
			sum=sum+mas[shetchik].w;
		}
		sdp(root,mas[shetchik]);
		A2(left,shetchik-1,mas);
		A2(shetchik+1,right,mas);
	}
}

void main_body(struct data* data_base) {
	fflush(stdin);
	int exit=0, error_input=0, position=0, mas_kolvo=0, ii=0, prin_flag=0, prin_flag2=0;
	bool live_tree=false, live_que=false, live_mas=false;
	char input[4];
	struct mas *mass;
	struct data** index_array=(struct data**)malloc((right_corn+1)*sizeof(struct data));
	for(int i=0; i<right_corn+1; i++) index_array[i]=&data_base[i];
	struct Queue* head;
	HeapSort(index_array);
	while(exit==0) {
		fflush(stdin);
		printf("\n 1 - Prosmotr basi \n 2 - Yporadochivan \n 3 - Poisk \n 4 - Create vertex \n 5 - search in vertex \n 6 - Exit \n"); // 1 - 49 / 2 - 50 / 3 - 51
		printf(" ---> ");
		if(scan_gets==1) scanf("%s",&input);
		else if(scan_gets==2) {
			fgets(input,4,stdin);
			input[strlen(input)-1]='\0';
		}
		if(strlen(input)!=1) error_input+=2;
		while(error_input>0) {
			fflush(stdin);
			printf("\n Error. Unknown key. \n");
			printf("\n 1 - Prosmotr basi \n 2 - Yporadochivan \n 3 - Poisk \n 4 - Create vertex \n 5 - search in vertex \n 6 - Exit \n");
			printf(" ---> ");
			if(scan_gets==1) scanf("%s",&input);
			else if(scan_gets==2) {
				fgets(input,4,stdin);
				input[strlen(input)-1]='\0';
			}
			if(strlen(input)==1 && (input[0]=='1' || input[0]=='2' || input[0]=='3' || input[0]=='4')) error_input=0;
		}
		switch(input[0]) {
			case '1':
				prinn(index_array,data_base,1);
				break;
			case '2':
				system("CLS");
				fflush(stdin);
				scan_input(input);
				if(input[0]=='1') prinn(index_array,data_base,2);
				else if(input[0]=='2') obrprin(index_array);
				break;
			case '3':
				if(live_que==true) {
					if(position>1) del_que(head);
					else free(head);
					live_que=false;
					mas_kolvo=0;
					ha=1;
				}
				head=(struct Queue*)malloc(sizeof(struct Queue));
				head->next=NULL;
				last_element=(struct Queue*)head;
				system("CLS");
				fflush(stdin);
				scan_input(input);
				found(index_array,&position);
				if(position>-1) {
					live_que=true;
					if(input[0]=='1') {
						crea_qu(position,&mas_kolvo,index_array,last_element);
					} else if(input[0]=='2') {
						alt_crea_qu(position,&mas_kolvo,index_array,last_element);
					}
					printnt(head);
					printf("\n \n");
				} else printf("\n \n No found \n \n");
				getch();
				break;
			case '4':
				ii=0;
				prin_flag=0;
				if(live_tree==true) {
					for(int i=0; i<mas_kolvo; i++) root=del_sdp(mass[i],root);
					live_tree=false;
					if(live_mas==true) {
						free(mass);
						live_mas=false;
					}
					ha=1;
				}
				root=new vertex;
				root=NULL;
				if(live_que==true) {
					system("CLS");
					mass=(struct mas*)malloc(mas_kolvo*sizeof(struct mas));
					for(print_mark=head->next; print_mark; print_mark=print_mark->next) {
						mass[ii].address=print_mark->address;
						ii+=1;
					}
					live_mas=true;
					quick(mass,0,ii-1);
					A2(0,mas_kolvo-1,mass);
					printf("\n Printf Vertex? \n 1 - Yes \n 2 - No \n \n -->");
					scanf("%d",&prin_flag);
					if(prin_flag!=1 && prin_flag!=2) while(prin_flag!=1 && prin_flag!=2) {
							printf(" Printf Vertex? \n 1 - Yes \n 2 - No \n \n -->");
							scanf("%d",&prin_flag);
						}
					if(prin_flag==1) {
						printf("\n Printf Center? \n 1 - Yes \n 2 - No \n -->");
						scanf("%d",&prin_flag2);
						if(prin_flag!=1 && prin_flag!=2) while(prin_flag!=1 && prin_flag!=2) {
								printf("\n Printf Center? \n 1 - Yes \n 2 - No \n -->");
								scanf("%d",&prin_flag2);
							}
						if(prin_flag2==1) prin(root,1);
						else prin(root,0);
					} else if(prin_flag==2) printf(" Vertex ready. \n \n");
					live_tree=true;
				} else printf(" NO que. \n");
				break;
			case '5':
				if(live_tree==true && root!=NULL) tree_search(root);
				else printf(" NO vertex. \n \n");
				break;
			case '6':
				exit+=2;
				if(live_tree==true && live_mas==true) for(int i=0; i<mas_kolvo; i++) root=del_sdp(mass[i],root);
				if(live_mas==true) free(mass);
				break;
		}
	}
	free(index_array);
}

int main() {
	struct data* data_base;
	FILE* file=fopen("testBase3.dat","rb");
	if(file==NULL) {
		printf("\n Data base is empty or error.\n ");
		return 44;
	}
	data_base=(struct data*)malloc((right_corn+1)*sizeof(struct data));
	fread((struct data*)data_base,sizeof(t1),(right_corn+1),file);
	main_body(data_base);
	fclose(file);
	free(data_base);
	return 0;
}

void tree_search(struct vertex *root) {
	struct vertex *p=new vertex, *q=new vertex;
	bool find=false;
	char input[30];
	p=root;
	fflush(stdin);
	system("CLS");
	printf(" \n Key - ");
	fgets(input,31,stdin);
	input[strlen(input)-1]='\0';
	while (p != NULL) {
		if (less_tree_found(input,p)==-1) p = p->left;
		else if (less_tree_found(input,p)==1) p = p->right;
		else if(less_tree_found(input,p)==0) {
			find=true;
			break;
		}
	}
	if(p!=NULL) {
		while(p!=NULL) {
			printf(" %s %d %s %s\n",p->address->name_vklad,p->address->sum,p->address->date_vklad,p->address->name_advok);
			p=p->center;
		}
	} else if(find==false) printf(" No found \n");
}

void sdp(struct vertex *&root, mas mas) {
	struct vertex **p=&root;
	while(*p!=NULL) {
		if(strcmp(mas.address->name_advok,(*p)->address->name_advok)==-1) p=&((*p)->left);
		else if(strcmp(mas.address->name_advok,(*p)->address->name_advok)==1) p=&((*p)->right);
		else if(strcmp(mas.address->name_advok,(*p)->address->name_advok)==0) {
			while(*p!=NULL) p=&((*p)->center);
		};
	}
	if(*p==NULL) {
		*p=new vertex;
		(*p)->address=mas.address;
		(*p)->w=mas.w;
		(*p)->right=NULL;
		(*p)->left=NULL;
	}
}

void quick(struct mas *a, int l, int r) {
	struct data *temp;
	int ttemp=0, res=0;
	char x[22];
	strcpy(x,a[l].address->name_advok);
	int i=l, j=r;
	while(i<=j) {
		res=less_vertex(a[i],x);
		while(less_vertex(a[i],x)==-1) {
			i+=1;
		}
		while(less_vertex(a[j],x)==1) {
			j-=1;
		}
		if(i<=j) {
			temp=a[j].address;
			a[j].address=a[i].address;
			a[i].address=temp;
			ttemp=a[j].w;
			a[j].w=a[i].w;
			a[i].w=ttemp;
			i+=1;
			j-=1;
		}
	}
	if(l<j) quick(a,l,j);
	if(i<r) quick(a,i,r);
}

void del_que(struct Queue *head) {
	struct Queue *delet_memory;
	int exit = 0;
	delet_memory=head;
	if(head->next!=NULL) queue_point=head->next;
	else if(head->next==NULL) exit+=2;
	while(exit==0) {
		if(queue_point->next==NULL) {
			exit+=2;
		} else if(queue_point->next!=NULL) {
			free(delet_memory);
			delet_memory=queue_point;
			queue_point=queue_point->next;
		}
	}
	if(exit!=0) {
		delet_memory=queue_point;
		free(delet_memory);
	}
}

void scan_input(char input2[4]) {
	fflush(stdin);
	int error_input=0;
	printf("\n Poradok: \n 1 - po ybivaniy \n 2 - po vozrastaniy \n");
	printf(" ---> ");
	if(scan_gets==1) scanf("%s",input2);
	else if(scan_gets==2) {
		fgets(input2, 4, stdin);
		input2[strlen(input2)-1]='\0';
	}
	if((strlen(input2)!=1)||(input2[0]!='1' && input2[0]!='2')) {
		error_input+=2;
	}
	while(error_input!=0) {
		fflush(stdin);
		printf("\n Error. Unknown key. \n");
		printf("\n Poradok: \n 1 - po ybivaniy \n 2 - po vozrastaniy \n");
		printf(" ---> ");
		if(scan_gets==1) scanf("%s",input2);
		else if(scan_gets==2) {
			fgets(input2, 4, stdin);
			input2[strlen(input2)-1]='\0';
		}
		if(strlen(input2)==1 && (input2[0]=='1' || input2[0]=='2')) error_input=0;
	}
}

void prin(struct vertex *p, int center) {
	if(p!=NULL) {
//		printf(" %d. %s %d %s %s\n",ha,p->address->name_vklad,p->address->sum,p->address->date_vklad,p->address->name_advok); ha+=1;
		prin(p->left,center);
		printf(" %d. %s %d %s %s\n",ha,p->address->name_vklad,p->address->sum,p->address->date_vklad,p->address->name_advok);
		ha+=1;
		if(center==1) prin(p->center,center);
		prin(p->right,center);
	}
}

void obrprin(struct data** index_array) {
	int exit=0, input=0, position=0;
	printf(" Nomer ycheiki - ");
	scanf("%d",&position);
	if(position<0) position=0;
	if(position>0) position=position-1;
	if(position>3981) position=3979;
	while(exit==0) {
		system("CLS");
		for(int printf_position=right_corn-position; printf_position>right_corn-(position+21) && printf_position>=0 && printf_position<right_corn+1; printf_position--) {
			printf(" \n %d. %s %d %s %s",(right_corn-printf_position)+1,index_array[printf_position]->name_vklad,index_array[printf_position]->sum,index_array[printf_position]->date_vklad,index_array[printf_position]->name_advok);
		}
		printf("\n \n What do? Esc - exit\n -> for next\n <- for back\n ^- for write number. ");
		input=getch(); // 75 <- 77 -> 27 esc
		switch(input) {
			case 75:
				position-=21;
				if(position<0) position=0;
				break;
			case 77:
				position+=21;
				if(position>=3980) position=4000-21;
				break;
			case 27:
				exit+=2;
				break;
			case 72:
				printf(" \n Number - ");
				scanf("%d",&position);
				if(position>0) position=position-1;
				if(position>3980) position=4000-20;
				break;
			default:
				printf("\n \n Error Esc - exit, -> for next, <- for back, ^- for write number. ");
				break;
		}
	}
	printf("\n \n");
}

void prinn(struct data** index_array, struct data* data_base, int mode_print) {
	int exit=0, input=0, position=0;
	fflush(stdin);
	printf(" Nomer ycheiki - ");
	scanf("%d",&position);
	if(position>0) position=position-1;
	if(position>3980) position=(right_corn+1)-20;
	while(exit==0) {
		system("CLS");
		if(mode_print==2) for(int print_position=position; print_position<position+21 && print_position>=0 && print_position<4000; print_position++) {
				printf(" \n %d. %s %d %s %s",print_position+1,index_array[print_position]->name_vklad,index_array[print_position]->sum,index_array[print_position]->date_vklad,index_array[print_position]->name_advok);
			}
		else if(mode_print==1) for(int print_position=position; print_position<position+21 && print_position>=0 && print_position<4000; print_position++) {
				printf(" \n %d. %s %d %s %s",print_position+1,data_base[print_position].name_vklad,data_base[print_position].sum,data_base[print_position].date_vklad,data_base[print_position].name_advok);
			}
		printf("\n \n What do? Esc - exit\n -> for next\n <- for back\n ^- for write number. ");
		input=getch(); // 75 <- 77 -> 27 esc
		switch(input) {
			case 75:
				position-=21;
				if(position<0) position=0;;
				break;
			case 77:
				position+=21;
				if(position>=3980) position=4000-20;
				break;
			case 27:
				exit+=2;
				break;
			case 72:
				printf(" \n Number - ");
				scanf("%d",&position);
				if(position<0) position=0;
				if(position>0) position=position-1;
				if(position>3980) position=(right_corn+1)-20;
				break;
			default:
				printf("\n \n Error Esc - exit, -> for next, <- for back, ^- for write number. ");
				break;
		}
	}
	printf("\n \n");
}

void printnt(struct Queue *head) {
	int number=1;
	for(print_mark=head->next; print_mark; print_mark=print_mark->next) {
		printf("\n %d) %s %d %s %s",number,print_mark->address->name_vklad,print_mark->address->sum,print_mark->address->date_vklad,print_mark->address->name_advok);
		number+=1;
	}
}

void del_cent(struct vertex* p) {
	struct vertex *q, *qq;
	qq=p;
	for(q=p->center; q; q=q->center) {
		free(qq);
		qq=q;
	}
	if(qq!=NULL) free(qq);
	if(q!=NULL) free(q);
}

struct vertex* del_sdp(struct mas x, struct vertex *root) {
	struct vertex **p;
	p=&root;
	struct vertex *s, *r, *q, *pp;
	while(*p!=NULL) {
		if(strcmp(x.address->name_advok,(*p)->address->name_advok)==-1) p=&((*p)->left);
		else if(strcmp(x.address->name_advok,(*p)->address->name_advok)==1) p=&((*p)->right);
		else if(strcmp(x.address->name_advok,(*p)->address->name_advok)==0) {
			if((*p)->center!=NULL) {
				pp=(*p)->center;
				del_cent(pp->center);
			}
			break;
		}
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
