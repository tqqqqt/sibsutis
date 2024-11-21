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

struct spis* InitNewSpis(char newFirstName[30], char newLastName[30], char newLoginDate[12]) {
	struct spis* head=malloc(sizeof(struct spis));
	strcpy(head->firstName,newFirstName);
	strcpy(head->lastName,newLastName);
	strcpy(head->loginDate,newLoginDate);
	head->prev=NULL;
	head->next=NULL;
	return head;
}

void AddSpis(char newFirstName[30], char newLastName[30], char newLoginDate[12], struct spis* head) {
	struct spis* temp=malloc(sizeof(struct spis));
	temp=head;
	while(temp->next!=NULL) {
		temp=temp->next;
	}
	struct spis *newPoint=malloc(sizeof(struct spis));
	strcpy(newPoint->firstName,newFirstName);
	strcpy(newPoint->lastName,newLastName);
	strcpy(newPoint->loginDate,newLoginDate);
	newPoint->next=NULL;
	newPoint->prev=temp;
	temp->next=newPoint;
}

struct spis* DeleteFirstName(char findFirstName[30], struct spis* head) {
	struct spis* temp=malloc(sizeof(struct spis));
	temp=head;
	while(temp!=NULL) {
		if(strcmp(temp->firstName,findFirstName)==0) break;
		temp=temp->next;
	}
	if(temp->prev!=NULL){
	        temp->prev->next=temp->next;
		free(temp);
	}
	else{
		struct spis* forReturn=temp->next;
		free(temp);
		forReturn->prev=NULL;
		return forReturn;
	}
	return head;
}

struct spis* DeleteLastName(char findLastName[30], struct spis* head){
	struct spis* temp=malloc(sizeof(struct spis));
	temp=head;
	while(temp!=NULL) {
		if(strcmp(temp->lastName,findLastName)==0) break;
		temp=temp->next;
	}
	if(temp->prev!=NULL){
	       	temp->prev->next=temp->next;
		free(temp);
	}
	else{
		struct spis* forReturn=temp->next;
		free(temp);
		forReturn->prev=NULL;
		return forReturn;
	}
	return head;
}

struct spis* DeleteFirstLastName(char findFirstName[30], char findLastName[30], struct spis* head){
	struct spis* temp=malloc(sizeof(struct spis));
	temp=head;
	while(temp!=NULL) {
		if(strcmp(temp->firstName,findFirstName)==0 && strcmp(temp->lastName,findLastName)==0) break;
		temp=temp->next;
	}
	if(temp->prev!=NULL){
	       	temp->prev->next=temp->next;
		free(temp);
	}
	else{
		struct spis* forReturn=temp->next;
		free(temp);
		forReturn->prev=NULL;
		return forReturn;
	}
	return head;
}

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

int main() {
	struct spis* mainHead=NULL;
	char fName[30], lName[30], lDate[12];
	int i=0, input=0, input2=0;
	printf(" Create new spis? \n 1 - yes \n 2 - no \n \n -->");
	scanf("%d",&i);
	if(i==1){
		printf("First name - ");
		scanf("%s",fName);
		printf("Last name - ");
		scanf("%s",lName);
		printf("Login date - ");
		scanf("%s",lDate);
		mainHead=InitNewSpis(fName,lName,lDate);
		i=0;
	}
	else i=-2;
	while(i==0){
		printf("\n \n What do? \n 1 - add in spis \n 2 - print spis \n 3 - delete in spis \n 4 - navigation in spis \n 5 - save spis \n 6 - exit \n \n -->");
		scanf("%d",&input);
		if(input==1){
			printf("First Name - ");
			scanf("%s",fName);
			printf("Last Name - ");
			scanf("%s",lName);
			printf("Login date - ");
			scanf("%s",lDate);
			if(mainHead!=NULL) AddSpis(fName,lName,lDate,mainHead);
			else mainHead=InitNewSpis(fName,lName,lDate);
		}
		else if(input==2){
			PrintSpis(mainHead);
			printf("\n \n");
		}
		else if(input==3){
			printf(" 1 - delete on first name \n 2 - delete on last name \n 3 - delete on first and last name \n \n -->");
			scanf("%d",&input2);
			if(input2==1){
				printf("first name - ");
				scanf("%s",fName);
				mainHead=DeleteFirstName(fName,mainHead);
			}
			else if(input2==2){
				printf("last name - ");
				scanf("%s",lName);
				mainHead=DeleteLastName(lName,mainHead);
			}
			else if(input2==3){
				printf("first name - ");
				scanf("%s",fName);
				printf("last name - ");
				scanf("%s",lName);
				mainHead=DeleteFirstLastName(fName,lName,mainHead);
			}
		}
		else if(input==4){
			NavigSpis(mainHead);
			printf("\n \n");
		}
		else if(input==5){
			if(SaveSpis(mainHead)){
				printf("Error save.");
				break;
			}
		}
		else if(input==6) break;
	}
	return 0;
}

