#include<iostream>
#include<string>
using namespace std;

int intStr(char c){
	return c - '0';
}

int main(){
	string a, b;
	cout<<"Chislo a - ";
	cin>>a;
	cout<<"Chislo b - ";
	cin>>b;
	
	int na=a.length(), nb=b.length();
	int res=0, temp=0, mnojtemp=1, mnojres=1;
	for(int i=na-1;i>=0;i--){
		if(intStr(a[i])!=0){
			temp=0;
			mnojtemp=1;
			for(int j=nb-1;j>=0;j--){
				if(intStr(b[i])!=0){
					temp+=intStr(a[i])*intStr(b[j])*mnojtemp;
				}
				mnojtemp*=10;
			}
			res+=temp*mnojres;
		}
		mnojres*=10;
	}
	cout<<"\n \n Result = "<<res;
}
