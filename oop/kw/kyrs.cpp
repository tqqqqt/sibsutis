#include <iostream>
#include <stdlib.h>

using namespace std;

const int ff=10;

int main(){
	int j=0;
	for(int i=0;i<20;i+=1){
		j=1+rand()%99;
		cout<<j<<" ";
		if(j<=25) cout<<"[]";
	}
	return 0;
}
