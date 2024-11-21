#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){
	int n=10;
	int *mas=new int[n], pos=0, temp=0;
	for(int i=0;i<n;i++) mas[i]=rand()%100;
	for(int i=0;i<n-1;i++){
		pos=i;
		for(int j=i+1;j<n;j++){
			if(mas[pos]>mas[j]){
				pos=j;
				temp=mas[j];
			}
		}
		mas[pos]=mas[i];
		mas[i]=temp;
	}
	for(int i=0;i<n;i++) cout<<mas[i]<<" ";
}
