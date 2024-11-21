#include<iostream>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
#include<math.h>
using namespace std;

int flag=0;

struct check{
	int pair11, pair12;
	int pair21, pair22;
	check(int p11, int p12, int p21, int p22){
		pair11=p11;
		pair12=p12;
		pair21=p21;
		pair22=p22;
	}
	check(){}
};

string ConvertToString(long long int x){
	stringstream stringStream;
	stringStream<<x;
	return stringStream.str();
}

string StrOut(int curX, int curY, int x, int y, check **mas){
	if(abs(x-y)==1){
		//if(flag==0) {
			//flag=1;
			return (string)("(["+ConvertToString(x)+"] * ["+ConvertToString(y)+"])");
		//}
		//else if(flag==1) return (string)("(M["+ConvertToString(x)+"] * M["+ConvertToString(y)+"])");
	}
	else if(abs(x-y)==0){
		//flag=1;
		//return (string)("(M["+ConvertToString(x)+"] * "+StrOut(curX,curY,mas[curX][curY].pair11,mas[curX][curY].pair12,mas)+")");
		return (string)("["+ConvertToString(x)+"]");
	}
	else if(abs(x-y)>1){
		int newX=x, newY=y;
		flag=0;
		cout<<newX<<" "<<newY<<" "<<mas[newX][newY].pair11<<" "<<mas[newX][newY].pair12<<" "<<mas[newX][newY].pair21<<" "<<mas[newX][newY].pair22<<endl;
		return ("("+StrOut(newX,newY,mas[newX][newY].pair11,mas[newX][newY].pair12,mas) + " * " + StrOut(newX,newY,mas[newX][newY].pair21,mas[newX][newY].pair22,mas) + ")");
		
	}
}

string StrStr(int x, int y, check **mas){
	
}

void MainSkobki(int **mas, int n){
	int **f=new int* [n+1];
	int *r=new int[n+1];
	check **m=new check* [n+1];
	for(int i=0;i<n;i++) r[i]=mas[i][0];
	r[n]=mas[n-1][1];
	cout<<endl;
	for(int i=0;i<=n;i++) cout<<"r("<<i<<") = "<<r[i]<<endl;
	cout<<endl;
	for(int i=0;i<=n;i++) f[i]=new int[n+1]{};
	for(int i=0;i<=n;i++) m[i]=new check[n+1];
	for(int t=1;t<n;t++){
		for(int k=1;k<n;k++){
			int minF=999999, temp=0;
			if(k+t>=n+1) continue;
			for(int j=k;j<k+t;j++){
//				if(k+t>=n+1) break;
				temp=f[k][j]+f[j+1][k+t]+r[k-1]*r[j]*r[k+t];
				if(temp<minF){
					minF=temp;
					m[k][k+t].pair11=k;
					m[k][k+t].pair12=j;
					m[k][k+t].pair21=j+1;
					m[k][k+t].pair22=k+t;
				}
			}
			f[k][k+t]=minF;
		}
	}
	cout<<setw(6)<<"";
	for(int i=1;i<=n;i++) cout<<setw(6)<<i;
	cout<<endl;
	for(int i=1;i<=n;i++){
		cout<<setw(6)<<i;
		for(int j=1;j<=n;j++){
			cout<<setw(6)<<f[i][j];
		}
		cout<<endl;
	}
	if(m[1][n].pair11-m[1][n].pair12==0) cout<<endl<<"Otvet - "<<StrOut(1,n,m[1][n].pair11,m[1][n].pair12,m)<<" "<<StrOut(1,n,m[1][n].pair21,m[1][n].pair22,m);
	else if(m[1][n].pair21-m[1][n].pair22==0) cout<<endl<<"Otvet - ("<<StrOut(1,n,m[1][n].pair11,m[1][n].pair12,m)<<" * "<<StrOut(1,n,m[1][n].pair21,m[1][n].pair22,m)+")";
	else cout<<endl<<"Otvet - "<<StrOut(1,n,m[1][n].pair11,m[1][n].pair12,m)<<" * "<<StrOut(1,n,m[1][n].pair21,m[1][n].pair22,m);
}

int main(){
	ifstream input("skobk.txt");
	int n;
	input>>n;
	int **mas=new int* [n];
	for(int i=0;i<n;i++) mas[i]=new int[2]{};
	for(int i=0;i<n;i++) input>>mas[i][0]>>mas[i][1];
	for(int i=0;i<n;i++) cout<<"M["<<i+1<<"] = ["<<mas[i][0]<<"x"<<mas[i][1]<<"], ";
	cout<<endl;
	MainSkobki(mas,n);
}
