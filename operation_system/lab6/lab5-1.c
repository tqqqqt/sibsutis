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
