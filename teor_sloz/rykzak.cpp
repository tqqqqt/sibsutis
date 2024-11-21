#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

void MainBackap(int **mas, int n, int maxM){
	int *f=new int[maxM+2]{};
	for(int i=0;i<=maxM+1;i++){
		int maxFind=0;
		for(int j=0;j<n;j++){
			if(mas[j][0]<=i) maxFind=max(maxFind,f[i-mas[j][0]]+mas[j][1]);
			else break;
		}
		f[i]=maxFind;
		//cout<<"f("<<i<<") = "<<f[i]<<endl;
	}
	
	cout<<endl;
	int res1I=maxM, res2I=maxM+1;
	int res1=f[res1I], res2=f[res2I];
	for(int i=0;i<n;i++){
		cout<<"m("<<i<<") = "<<mas[i][0]<<", C("<<i<<") = "<<mas[i][1]<<endl;
	}
	cout<<endl<<"f("<<res1I<<") = "<<res1<<endl;
	int *resKol=new int[n]{};
	while(res1>0){
		res1=f[res1I];
		for(int i=0;i<n;i++){
			if(f[res1I-mas[i][0]]+mas[i][1]==res1){
				//cout<<"m("<<i<<") = "<<mas[i][0]<<", C("<<i<<") = "<<mas[i][1]<<endl;
				resKol[i]++;
				res1I=res1I-mas[i][0];
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<i<<" predmet vzat - "<<resKol[i]<<"raz"<<endl;
		resKol[i]=0;
	}
	cout<<endl<<endl<<"f("<<res2I<<") = "<<res2<<endl;
	while(res2>0){
		res2=f[res2I];
		for(int i=0;i<n;i++){
			if(f[res2I-mas[i][0]]+mas[i][1]==res2){
				//cout<<"m("<<i<<") = "<<mas[i][0]<<", C("<<i<<") = "<<mas[i][1]<<endl;
				resKol[i]++;
				res2I=res2I-mas[i][0];
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<i<<" predmet vzat - "<<resKol[i]<<"raz"<<endl;
	}
}

int main(){
	int n, maxM=0;
	ifstream input("ruk.txt");
	input>>n;
	int **mas=new int* [n];
	for(int i=0;i<=n;i++) mas[i]=new int[2]{};
	for(int i=0;i<=n;i++){
		input>>mas[i][0]>>mas[i][1];
		maxM+=mas[i][0];	
	} 
	MainBackap(mas,n,maxM);
	MainBackap(mas,n,3000000);
}
