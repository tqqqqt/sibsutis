#include<iostream>
using namespace std;
int main(){
	int mas[3][3]{};
	int mass[9]={1,2,3,4,5,6,7,8,9};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			mas[i+j*3][i]=i+j;
		}
	}
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<mas[i][j]<<" ";
		}
		cout<<endl;
	}
}
