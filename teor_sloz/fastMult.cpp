#include<iostream>
#include<cstring>
#include<sstream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;

struct multShet{
	string x;
	string y;
	string x2;
	string y2;
	string rxy;
	string rx1y1;
	string res;
	int flag;
	multShet(string n1, string n2, string r){
		x=n1;
		y=n2;
		res=r;
		flag=0;
	}
	multShet(string n1, string n2, string n3, string n4, string n13, string n24, string r){
		x=n1;
		x2=n2;
		y=n3;
		y2=n4;
		res=r;
		rxy=n13;
		rx1y1=n24;
		flag=1;
	}
};

vector<multShet> mull;
bool flag=true;

string ConvertToString(long long int x){
	stringstream stringStream;
	stringStream<<x;
	return stringStream.str();
}

string TenPow(int x){
	string res="1";
	for(int i=0;i<x;i++) res+="0";
	return res;
}

string MultNums(string sNum1, string sNum2){
	int l1=sNum1.length(), l2=sNum2.length();
	if(l1==0 || l2==0) return "0";
	vector<long long int> res(l1+l2,0);
	int in1=0, in2=0;
	for(int i=l1-1;i>=0;i--){
		int carry=0, n1=sNum1[i]-'0';
		in2=0;
		for(int j=l2-1;j>=0;j--){
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
	while(i>=0) s+=ConvertToString(res[i--]);
	return s;
}

string SumNums(string stringNum1, string stringNum2){
	int lengthNum1=stringNum1.length()-1, lengthNum2=stringNum2.length()-1;
	int sum=0, carry=0;
	string n1="",n2="",res="";
	while(lengthNum1>=0 || lengthNum2>=0){
		if(lengthNum1<0) n1="0";
		else n1=stringNum1[lengthNum1];
		if(lengthNum2<0) n2="0";
		else n2=stringNum2[lengthNum2];
		sum=(int)(n1[0]-'0')+(int)(n2[0]-'0')+carry;
		if(sum>9){
			res=ConvertToString(sum%10)+res;
			carry=sum/10;
		}
		else{
			res=ConvertToString(sum%10)+res;
			carry=0;
		}
		lengthNum1--;
		lengthNum2--;
	}
	if(carry!=0) res=ConvertToString(carry)+res;
	while(res[0]=='0' && res.length()>0) res=res.substr(1,res.length());
	return res;
}

string SubNums(string num1, string num2){
	int flg=num2.length()>num1.length() ? 2 : 0;
    if(num1.length()==num2.length()) flg=1;
    else if(num1.length()>num2.length()) flg=0;
    if(flg==2){
    	string temp=num1;
    	num1=num2;
    	num2=temp;
    }
    if(flg==1){
    	for(int i=0;i<num1.size();i++){
    		if(num1[i]-'0'==num2[i]-'0') continue;
    		if(num1[i]-'0'>num2[i]-'0') break;
    		string temp=num1;
    		num1=num2;
    		num2=temp;
    		flg=2;
    		break;
		}
	}
    int ln1=num1.length()-1,ln2=num2.length()-1;
    int sub=0, carry=0;
    string n1,n2,res;
    while(ln1>=0 || ln2>=0){
        if(ln1<0) n1="0";
        else n1=num1[ln1];
        if(ln2<0) n2="0";
        else n2=num2[ln2];
        if(ln1==0 && ln2==0){
            if(carry==0) sub=(int)(n1[0]-'0')-(int)(n2[0]-'0');
            else if(carry==1) sub=(int)((n1[0]-'0')-1)-(int)(n2[0]-'0');
            carry=0;
        }
        else{
        	if(carry==1){
        		sub=(int)((n1[0]-'0')-1)-(int)(n2[0]-'0');
        		if(sub<0){
        			sub=(int)((n1[0]-'0')+9)-(int)(n2[0]-'0');
				}
				else carry=0;
			}
			else{
				sub=(int)(n1[0]-'0')-(int)(n2[0]-'0');
            	if(sub<0){
            		sub=(int)((n1[0]-'0')+10)-(int)(n2[0]-'0');
            		carry=1;
				}	
			}
        }
        res=ConvertToString(sub)+res;
        ln1--;
        ln2--;
    }
   	while(res[0]=='0' && res.length()>1) res=res.substr(1,res.length());
    if(flg==2) res="-"+res;
    if(res.length()==0) return "0";
    return res;
}

string MainMultNums(string num1, string num2){
	if(num1.length()!=num2.length()) return MultNums(num1,num2);
	if(num1.length()==1 && num2.length()==1) return MultNums(num1,num2);
	int k=num1.length()>=num2.length() ? num1.length()/2 : num2.length()/2;
	string a=num1.substr(0,num1.length()/2), b=num1.substr(num1.length()/2,num1.length()/2);
	string c=num2.substr(0,num2.length()/2), d=num2.substr(num2.length()/2,num2.length()/2);
	string sumAB=SumNums(a,b), sumCD=SumNums(c,d);
	string u="";
	if(sumAB.length()>k || sumCD.length()>k){
		string a1="0",a2="0",b1="0",b2="0";
		int flg=sumAB.length()>k ? 1 : 0;
		if(flg==1){
			a1=sumAB.substr(0,1);
			a2=sumAB.substr(1,sumAB.length()-1);
		}
		else a2=sumAB;
		flg=sumCD.length()>k ? 1 : 0;
		if(flg==1){
			b1=sumCD.substr(0,1);
			b2=sumCD.substr(1,sumCD.length()-1);
		}
		else b2=sumCD;
		while(a2[0]=='0' && a2.length()>1) a2=a2.substr(1,a2.length()-1);
		while(b2[0]=='0' && b2.length()>1) b2=b2.substr(1,b2.length()-1);
//		flag=false;
		string doSkobok=MultNums(MultNums(a1,b1),TenPow(k*2)),	skobki=MultNums(SumNums(MultNums(a1,b2),MultNums(a2,b1)),TenPow(k));
		string posleSkobok=MainMultNums(a2,b2);
		u=SumNums(SumNums(doSkobok,skobki),posleSkobok);
//		flag=true;
	}
	else u=MainMultNums(sumAB,sumCD);
	string v=MainMultNums(a,c), w=MainMultNums(b,d);
	if(flag==true) mull.push_back(multShet(a,b,c,d,sumAB,sumCD,u));
	mull.push_back(multShet(a,c,v));
	mull.push_back(multShet(b,d,w));
	string resTo2K=TenPow(2*k), resToK=TenPow(k);
	string resSub=MultNums(SubNums(SubNums(u,v),w),resToK);
	string res=SumNums(SumNums(MultNums(v,resTo2K),resSub),w);
	cout<<"num1="<<num1<<" a="<<a<<" b="<<b<<endl<<"num2="<<num2<<" c="<<c<<" d="<<d<<'\n';
	cout<<"u="<<u<<" v="<<v<<" w="<<w<<" res="<<res<<'\n'<<'\n';
	return res;
}

int main(){
	string num1, num2;
	
	cout<<" Input num1 -> ";
	cin>>num1;
	cout<<" Input num2 -> ";
	cin>>num2;
	int n=num1.length();
	string res=MainMultNums(num1,num2);
	cout<<" Answer = "<<res<<"\n \n";
//	cout<<" Check  = "<<MultNums(num1,num2)<<"\n \n";

	
	if(num1.length()!=num2.length()) return 0;
	mull.push_back(multShet(num1,num2,res));
	int **oper=new int* [5];
	for(int i=0;i<5;i++){
		oper[i]=new int[n]{};
	}
	for(int i=0;i<n;i++) oper[0][i]=i+1;
	
	int flg=0;
	for(int i=0;i<mull.size();i++){
		int temp=mull[i].res.length()-mull[i].x.length();
		int ttemp=mull[i].x.length();
		if(mull[i].flag==0){
			cout<<mull[i].x<<" * "<<mull[i].y<<" = "<<mull[i].res;
			oper[1][mull[i].x.length()-1]++;
			oper[4][mull[i].x.length()-1]++;
			cout<<" "<<mull[i].x.length()<<endl; 
		} 
		else if(mull[i].flag==1){
			cout<<"("<<mull[i].x<<" + "<<mull[i].x2<<")*("<<mull[i].y<<" + "<<mull[i].y2<<") = "<<mull[i].rxy<<" * "<<mull[i].rx1y1<<" = "<<mull[i].res<<" ";
			int r1=mull[i].rxy.length()-mull[i].x.length();
			int r2=mull[i].rx1y1.length()-mull[i].y.length();
			int rr=r1+r2;
			cout<<mull[i].x.length();
			for(int j=0;j<rr;j++) cout<<"+";
			oper[rr+1][mull[i].y.length()-1]++;
			oper[4][mull[i].y.length()-1]++;
			cout<<endl;
		} 
	}

	
	cout<<endl<<endl;
	for(int i=0;i<5;i++){
		for(int j=0;j<n;j++){
			cout<<oper[i][j]<<"\t";
		}
		if(i==2) cout<<" +"<<endl;
		else if(i==3) cout<<" ++"<<endl;
		else if(i==4) cout<<" all"<<endl;
		else cout<<endl;
	}
}
