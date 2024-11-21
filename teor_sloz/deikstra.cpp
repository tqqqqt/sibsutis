#include<iostream>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<sstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

string ConvertToString(long long int x){
	stringstream stringStream;
	stringStream<<x;
	return stringStream.str();
}

void Deikstra(int **mas, int n, int start){
	int needAdd=n-1, nn=n-1;
	vector<int> s;
	int **table=new int* [n];
	map<int,int> mp;
	for(int i=0;i<n;i++){
		table[i]=new int[needAdd]{};
	}
	s.push_back(start);
	cout<<std::setiosflags(ios::left)<<setw(15)<<"S"<<setw(6)<<"w"<<setw(6)<<"D(w)";
	for(int i=0;i<n;i++){
		string temp="D("+ConvertToString(i)+")";
		if(i!=start) cout<<setw(6)<<temp;
	} 
	cout<<endl;
	cout<<setw(15)<<start<<setw(6)<<"-"<<setw(6)<<"-";
	int temp=0;
	for(int i=0;i<n;i++){
		if(i!=start){
			if(mas[start][i]==9999) cout<<setw(6)<<"no";
			else cout<<setw(6)<<mas[start][i];
			mp[temp]=i;
			table[0][temp]=mas[start][i];
			temp++;
		}
	}
	cout<<endl;
	int *checkMas=new int[n];
	for(int i=0;i<n;i++) checkMas[i]=0;
	checkMas[start]=1;
	int curentStr=0;
	while(needAdd>0){
		int minPath=9999, nextPoint, nextPointPath;
		for(int i=0;i<nn;i++){
			if(checkMas[mp[i]]==0){
				if(table[curentStr][i]<minPath){
					nextPoint=mp[i];
					minPath=table[curentStr][i];
				}
			}
		}
		curentStr++;
		s.push_back(nextPoint);
		checkMas[nextPoint]=1;
		nextPointPath=minPath;
		for(int i=0;i<nn;i++){
			minPath=9999;
			if(checkMas[mp[i]]==0 && mas[nextPoint][mp[i]]!=9999){
				minPath=min(table[curentStr-1][i],nextPointPath+mas[nextPoint][mp[i]]);
			}
			else if(mas[nextPoint][mp[i]]==9999 || checkMas[mp[i]]==1) minPath=table[curentStr-1][i];
			table[curentStr][i]=minPath;
		}
		needAdd--;
		string outPut="(";
		for(int i=0;i<s.size();i++) outPut+=ConvertToString(s[i])+",";
		outPut+=")";
		cout<<std::setiosflags(ios::left)<<setw(15)<<outPut<<setw(6)<<nextPoint<<setw(6)<<nextPointPath;
		for(int i=0;i<nn;i++){
			if(table[curentStr][i]==table[curentStr-1][i] && checkMas[mp[i]]==1) cout<<setw(6)<<"-";
			else if(table[curentStr][i]==9999) cout<<setw(6)<<"no";
			else cout<<setw(6)<<table[curentStr][i];
		}
		cout<<endl;
	}
}

int main(){
	int n, start;
	ifstream input("temp.txt");
	input>>n>>start;
	start--;
	cout<<"N - "<<n<<endl;
	int **mas=new int* [n];
	for(int i=0;i<n;i++){
		mas[i]=new int[n]{};
	}
	cout<<setw(4)<<"";
	for(int i=0;i<n;i++) cout<<setw(4)<<i;
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<setw(4)<<i;
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
	for(int i=0;i<n;i++){
		Deikstra(mas,n,i);
		cout<<endl<<endl;
	}
}
