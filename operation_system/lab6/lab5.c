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

struct spis* InitNewSpis(char*, char*, char*);
void AddSpis(char*, char*, char*, struct spis*);
struct spis* DeleteFirstName(char*, struct spis*);
struct spis* DeleteLastName(char*, struct spis*);
struct spis* DeleteFirstLastName(char*, char*, struct spis*);
void PrintSpis(struct spis*);
void NavigSpis(struct spis*);
int SaveSpis(struct spis*);

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

