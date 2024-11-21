#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct tree {
	int x, y;
	int sum;
	tree() {}
	tree(int newX, int newY, int newSum) {
		x=newX;
		y=newY;
		sum=newSum;
	}
};

struct checked {
	int num;
	int team;
	bool flag;
	checked(int newNum, int newTeam, bool newFlag) {
		num=newNum;
		team=newTeam;
		flag=newFlag;
	}
};

struct checkTeam {
	int team1, team2;
	bool flag;
	checkTeam(int newT1, int newT2, bool newFlag) {
		team1=newT1;
		team2=newT2;
		flag=newFlag;
	}
};

vector<tree> mergeSort(vector<tree> mas, int n);

bool checkEnd(int maxTeam, vector<checked>& mass, vector<checkTeam>& mas){
	for(int i=0;i<mass.size();i++){
		if(mass[i].flag==false){
			return false;
		}
	}
	for(int i=1;i<maxTeam;i++){
		bool find=false;
		for(int j=0;j<mas.size();j++){
			if((mas[j].team1==i || mas[j].team2==i) && mas[j].flag==true){
				find=true;
				break;
			}
		}
		if(find==false) return false;
	}
	return true;
}

int main() {
	ifstream input("input1.txt");
	int n, resSum=0;
	input>>n;
	int **mas=new int* [n];
	vector<tree> vec;
	for(int i=0; i<n; i++) mas[i]=new int[n] {};
	for(int i=0; i<n+1; i++) cout<<setw(3)<<i;
	cout<<endl;
	for(int i=0; i<n; i++) {
		cout<<setw(3)<<i+1;
		for(int j=0; j<n; j++) {
			input>>mas[i][j];
			if(mas[i][j]!=-1) {
				bool flag=false;
				for(int ii=0; ii<vec.size(); ii++) {
					if((vec[ii].x==i && vec[ii].y==j) || (vec[ii].x==j && vec[ii].y==i)) flag=true;
				}
				if(flag==false) vec.push_back(tree(i,j,mas[i][j]));
				cout<<setw(3)<<mas[i][j];
			} else cout<<setw(3)<<"-";
		}
		cout<<endl;
	}
	input.close();
	vec=mergeSort(vec,vec.size());
//	cout<<endl;
//	for(int i=0;i<vec.size();i++){
//		cout<<vec[i].x<<" "<<vec[i].y<<" "<<vec[i].sum<<endl;
//	}
	vector<checked> check;
	vector<checkTeam> checkTeams;
	int teamCount=1;
	for(int i=0; i<n; i++) {
		check.push_back(checked(i+1,0,false));
	}
	cout<<endl<<endl<<"( , )"<<endl;
	for(int i=0; i<vec.size(); i++) {
		cout<<"("<<vec[i].x+1<<","<<vec[i].y+1<<")";
		if(check[vec[i].x].flag==false || check[vec[i].y].flag==false) {
			if(check[vec[i].x].team==0 && check[vec[i].y].team==0) {
				check[vec[i].x].team=teamCount;
				check[vec[i].y].team=teamCount;
				if(teamCount>1) {
					for(int ii=1; ii<teamCount; ii++) {
						checkTeams.push_back(checkTeam(ii,teamCount,false));
					}
				}
				teamCount++;
			} else if(check[vec[i].x].team!=0 && check[vec[i].y].team==0) {
				check[vec[i].y].team=check[vec[i].x].team;
			} else if(check[vec[i].x].team==0 && check[vec[i].y].team!=0) {
				check[vec[i].x].team=check[vec[i].y].team;
			}
			resSum+=vec[i].sum;
			check[vec[i].x].flag=true;
			check[vec[i].y].flag=true;
			cout<<"\t \t ";
		} else if((check[vec[i].x].flag==true && check[vec[i].y].flag==true) && check[vec[i].x].team!=check[vec[i].y].team) {
			vector<int> t1, t2;
			bool scep=false, oldScep=false;
			for(int j=0; j<checkTeams.size(); j++) {
				if(((checkTeams[j].team1==check[vec[i].x].team && checkTeams[j].team2==check[vec[i].y].team) || (checkTeams[j].team2==check[vec[i].x].team && checkTeams[j].team1==check[vec[i].y].team)) && checkTeams[j].flag==true) {
					oldScep=true;
					break;
				}
				if(checkTeams[j].team1==check[vec[i].x].team) t1.push_back(checkTeams[j].team2);
				if(checkTeams[j].team2==check[vec[i].x].team) t1.push_back(checkTeams[j].team1);
				if(checkTeams[j].team1==check[vec[i].y].team) t2.push_back(checkTeams[j].team2);
				if(checkTeams[j].team2==check[vec[i].y].team) t2.push_back(checkTeams[j].team1);
			}
			if(oldScep==true) {
				cout<<" - no";
			} else if(oldScep==false) {
				for(int j=0; j<t1.size(); j++) {
					for(int jj=0; jj<t2.size(); jj++) {
						if(t1[j]==t2[jj]) {
							scep=true;
							break;
						}
					}
					if(scep==true) break;
				}
				if(scep==false && oldScep==false) {
					checkTeams.push_back(checkTeam(check[vec[i].x].team,check[vec[i].y].team,true));
					resSum+=vec[i].sum;
				}
				cout<<"\t";
			}
			cout<<"\t";
		} else {
			cout<<" - no\t";
		}
		for(int i=0; i<check.size(); i++) {
			if(check[i].flag==true) cout<<check[i].num<<" ";
		}
		cout<<endl;
		if(checkTeams.size()>0) if(checkEnd(teamCount,check,checkTeams)==true) break;
	}
	cout<<endl<<endl<<" Sum = "<<resSum<<endl;
	return 0;
}

vector<tree> mergeSort(vector<tree> mas, int n) {
	vector<tree> sortVec=mas;
	struct tree temp;
	int flag=0;
	for(int i=0; i<n-1; i++) {
		flag=0;
		for(int j=n-1; j>i; j--) {
			if(sortVec[j].sum<sortVec[j-1].sum) {
				temp=sortVec[j];
				sortVec[j]=sortVec[j-1];
				sortVec[j-1]=temp;
				flag=1;
			}
		}
		if(!flag) break;
	}
	return sortVec;
}
