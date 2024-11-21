#include<iostream>
using namespace std;
int main(){
	int n=10;
	int *mas=new int[n], temp=0, flag=0;
	for(int i=0;i<n;i++) mas[i]=rand()%100;
	for(int i=0;i<n-1;i++){
		flag=0;
		for(int j=n-1;j>i;j--){
			if(mas[j]<mas[j-1]){
				temp=mas[j];
				mas[j]=mas[j-1];
				mas[j-1]=temp;
				flag=1;
			}
		}
		if(!flag) break;
	}
	for(int i=0;i<n;i++) cout<<mas[i]<<" ";
}
