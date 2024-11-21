#include<iostream>
#include<iomanip>
#include<fstream>
#include<algorithm>
using namespace std;

void mainFunc(int **mas, int n, int start){
	int **d=new int* [n];
	for(int i=0;i<n;i++){
		d[i]=new int[n];
	}
	for(int i=0;i<n;i++){
		if(i==start) d[0][i]=0;
		else d[0][i]=9999;
	}
	cout<<"D(0) = ";
	for(int i=0;i<n;i++){
		if(d[0][i]==9999) cout<<"*,";
		else cout<<d[0][i]<<",";
	}
	cout<<"\n";
	for(int i=1;i<n;i++){
		int flag=0;
		for(int j=0;j<n;j++){
			int minD=d[i-1][j];
			for(int ii=0;ii<n;ii++){
				int temp=0;
				if(mas[ii][j]>=9999) temp=9999;
				else if(d[i-1][ii]>=9999) temp=9999;
				else temp=d[i-1][ii]+mas[ii][j];
				minD=min(minD,temp);
			}
			d[i][j]=minD;
		}
		cout<<"D("<<i<<") = ";
		for(int j=0;j<n;j++){
			if(d[i][j]>=9999) cout<<"*,";
			else cout<<d[i][j]<<",";
		}
		cout<<endl;
		for(int j=0;j<n;j++){
			if(d[i][j]==d[i-1][j]) flag++;
		}
		if(flag==n) break;
	}
}

int main(){
	int n, start;
	ifstream input("temp.txt");
	input>>n>>start;
	start--;
	cout<<"N - "<<n<<endl;//<<"Start point - "<<start<<endl<<endl;
	int **mas=new int* [n];
	for(int i=0;i<n;i++){
		mas[i]=new int[n]{};
	}
	for(int i=0;i<=n;i++) cout<<setw(4)<<i;
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<setw(4)<<i+1;
		for(int j=0;j<n;j++){
			input>>mas[i][j];
			if(mas[i][j]==-1){
				cout<<setw(4)<<"-1";
				mas[i][j]=9999;
			}
			else cout<<setw(4)<<mas[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
	input.close();
//	mainFunc(mas,n,start);
	
	for(int i=0;i<n;i++){
		cout<<i<<" point:\n";
		mainFunc(mas,n,i);
		cout<<endl;
	}
}
