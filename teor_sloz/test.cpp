#include<iostream>
using namespace std;

int main(){
	int **mas=new int*[4];
	for(int i=0;i<4;i++) mas[i]=new int[i+1];
	for(int i=0;i<4;i++){
		for(int j=0;j<i+1;j++){
			cout<<mas[i][j]<<" ";
		}
		cout<<'\n';
	}
}
