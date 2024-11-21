#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct spis {
	char firstName[30];
	char lastName[30];
	char loginDate[12];
	struct spis* next;
	struct spis* prev;
};

void PrintSpis(struct spis* head) {
	struct spis* temp=head;
	int i=1;
	printf("First name \t Last name \t Login date\n");
	while(1) {
		if(temp==NULL) break;
		printf("%d. %s \t %s \t %s\n",i,temp->firstName,temp->lastName,temp->loginDate);
		temp=temp->next;
		i++;
	}
}

void NavigSpis(struct spis* head) {
	struct spis* temp=head;
	char tempChar;
	printf("Navigation: \n s - next\n w - back \n e - exit \n \n");
	while(1) {
		printf("%s %s %s\n",temp->firstName,temp->lastName,temp->loginDate);
		fflush(stdin);
		tempChar=getchar();
		if(tempChar=='e') break;
		else if(tempChar=='s' && temp->next!=NULL) temp=temp->next;
		else if(tempChar=='w' && temp->prev!=NULL) temp=temp->prev;
	}
}

int SaveSpis(struct spis* head) {
	FILE *file=fopen("temp.txt","wr");
	struct spis* tempHead=head;
	while(tempHead!=NULL) {
		fprintf(file,"%s %s %s\n",tempHead->firstName,tempHead->lastName,tempHead->loginDate);
		tempHead=tempHead->next;
	}
	return 0;
}
