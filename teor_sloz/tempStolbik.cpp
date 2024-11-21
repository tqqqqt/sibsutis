#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string ConvertToString(long long int x){
	stringstream stringStream;
	stringStream<<x;
	return stringStream.str();
}

string MultNums(string sNum1, string sNum2){
	int l1=sNum1.length(), l2=sNum2.length();
	if(l1==0 || l2==0) return "0";
	vector<long long int> res(l1+l2,0);
	int in1=0, in2=0;
	int r1=0, r2=0, flag=0;
	if(sNum1[0]=='-'){
		r1=1;
		flag++;
	}
	if(sNum2[0]=='-'){
		r2=1;
		flag++;
	}
	for(int i=l1-1;i>=r1;i--){
		int carry=0, n1=sNum1[i]-'0';
		in2=0;
		for(int j=l2-1;j>=r2;j--){
			int n2=sNum2[j]-'0';
			int sum=n1*n2+res[in1+in2]+carry;
			carry=sum/10;
			res[in1+in2]=sum%10;
			in2++;
		}
		if(carry>0) res[in1+in2]+=carry;
		in1++;
	}
	int i=res.size()-1;
	while(i>=0 && res[i]==0) i--;
	if(i==-1) return "0";
	string s="";
	if(flag==1) s+='-';
	while(i>=0) s+=ConvertToString(res[i--]);
	return s;
}

int main()
{
    string num1,num2;
    cout<<"Num 1 - ";
    cin>>num1;
    cout<<"Num 2 - ";
    cin>>num2;
    cout<<MultNums(num1,num2);
    return 0;
}
