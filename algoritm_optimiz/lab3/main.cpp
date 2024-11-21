//var 0
//6 mod 3 == 0
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include <cmath>
#include <cstdint>
using namespace std;

#define MIN(A,B) (A<B?A:B) 

struct tableElement{
	int prior;
	int data;
};

void PrintTable(struct tableElement **mas, unordered_map<int,int> lowStr, unordered_map<int,int> rightStlb, int nStrok, int nStolb){
	cout<<'\n';
	cout<<std::right<<setw(4)<<" ";
	for(int i=0;i<nStolb;i+=1) cout<<std::right<<setw(4)<<"B"<<i;
	cout<<'\n';
	for(int i=0;i<nStrok;i+=1){
		cout<<std::right<<setw(4)<<"A"<<i;
		for(int j=0;j<nStolb;j+=1){
			if(mas[i][j].data>=0) cout<<std::right<<setw(4)<<mas[i][j].data<<" ";
			else if(mas[i][j].data==-1) cout<<std::right<<setw(4)<<"-"<<" ";
			else cout<<std::right<<setw(4)<<"?"<<" ";
		}
		cout<<std::right<<setw(4)<<rightStlb[i]<<'\n';
	}
	cout<<std::right<<setw(5)<<" ";
	for(int i=0;i<nStolb;i+=1) cout<<std::right<<setw(4)<<lowStr[i]<<" ";
	cout<<'\n';
}

void PrintPriorTable(struct tableElement **mas, unordered_map<int,int> lowStr, unordered_map<int,int> rightStlb, int nStrok, int nStolb){
	cout<<'\n';
	cout<<std::right<<setw(4)<<" ";
	for(int i=0;i<nStolb;i+=1) cout<<std::right<<setw(4)<<"B"<<i;
	cout<<'\n';
	for(int i=0;i<nStrok;i+=1){
		cout<<std::right<<setw(4)<<"A"<<i;
		for(int j=0;j<nStolb;j+=1){
			cout<<std::right<<setw(4)<<mas[i][j].prior<<" ";
		}
		cout<<std::right<<setw(4)<<rightStlb[i]<<'\n';
	}
	cout<<std::right<<setw(5)<<" ";
	for(int i=0;i<nStolb;i+=1) cout<<std::right<<setw(4)<<lowStr[i]<<" ";
	cout<<'\n';
}

string IntToStr(int num){
	if(num==0) return "0";
	int length=0, temp=num;
	while(temp>0){
		temp/=10;
		length+=1;
	}
	temp=0;
	string res="";
	int tempNum=num;
	for(int i=length-1;i>=0;i-=1){
		temp=tempNum/pow(10,i);
		tempNum=tempNum%(int)pow(10,i);
		res+=(temp+'0');
	}
	return res;
}

int main(int argc, char** argv){
	if(argc!=2){
		cout<<"USAGE: ./program <file_name>\n";
		return -4;
	}
	ifstream file(argv[1]);
	int nStrok, nStolb;
	file>>nStrok>>nStolb;
	int **tempMas=(int**)malloc(sizeof(int*)*nStrok);
	for(int i=0;i<nStrok;i+=1) tempMas[i]=(int*)malloc(sizeof(int)*nStolb);
	for(int i=0;i<nStrok;i+=1){
		for(int j=0;j<nStolb;j+=1) file>>tempMas[i][j];
	}
	unordered_map<int,int> lowStr;
	unordered_map<int,int> rightStlb; 
	int lowStrSum=0, rightStlbSum=0;
	for(int i=0;i<nStolb-1;i+=1){
		lowStr.insert(make_pair(i,tempMas[nStrok-1][i]));
		lowStrSum+=tempMas[nStrok-1][i];
	}
	for(int i=0;i<nStrok-1;i+=1){
		rightStlb.insert(make_pair(i,tempMas[i][nStolb-1]));
		rightStlbSum+=tempMas[i][nStolb-1];
	}
	struct tableElement **mas;
	if(lowStrSum==rightStlbSum){
		cout<<" It's close model.\n";
		mas=(struct tableElement**)malloc(sizeof(struct tableElement*)*(nStrok-1));
		for(int i=0;i<nStrok-1;i+=1) mas[i]=(struct tableElement*)malloc(sizeof(struct tableElement)*(nStolb-1));
		for(int i=0;i<nStrok-1;i+=1){
			for(int j=0;j<nStolb-1;j+=1){
				mas[i][j].prior=tempMas[i][j];
				mas[i][j].data=-2;
			}
		}
		nStrok=nStrok-1;
		nStolb=nStolb-1;
	}
	else{
		cout<<" It's open model.\n";
		int tempStr=0, tempStlb=0;
		if(lowStrSum>rightStlbSum){
			tempStr=nStrok;
			tempStlb=nStolb-1;
			rightStlb.insert(make_pair(nStrok-1,(lowStrSum-rightStlbSum)));
		}
		else{
			tempStr=nStrok-1;
			tempStlb=nStolb;
			lowStr.insert(make_pair(nStolb-1,(rightStlbSum-lowStrSum)));
		}
		mas=(struct tableElement**)malloc(sizeof(struct tableElement*)*tempStr);
		for(int i=0;i<tempStr;i+=1) mas[i]=(struct tableElement*)malloc(sizeof(struct tableElement)*tempStlb);
		for(int i=0;i<tempStr;i+=1){
			for(int j=0;j<tempStlb;j+=1){
				if(i>=nStrok-1 || j>=nStolb-1) mas[i][j].prior=0;
				else mas[i][j].prior=tempMas[i][j];
				mas[i][j].data=-2;
			}
		}
		nStrok=tempStr;
		nStolb=tempStlb;
	}
	free(tempMas);
	
	//main code
	PrintPriorTable(mas,lowStr,rightStlb,nStrok,nStolb);
	int curStr=0, curStlb=0, countElem=0, resSum=0;
	int dStr, dStlb;
	string multStr="";
	while(true){
		dStr=curStr;
		dStlb=curStlb;
		int needVal=MIN(lowStr[curStlb],rightStlb[curStr]);
		mas[curStr][curStlb].data=needVal;
		lowStr[curStlb]-=needVal;
		rightStlb[curStr]-=needVal;
		if(resSum==0) multStr+=IntToStr(needVal)+"*"+IntToStr(mas[curStr][curStlb].prior);
		else multStr+="+"+IntToStr(needVal)+"*"+IntToStr(mas[curStr][curStlb].prior);
		resSum+=needVal*mas[curStr][curStlb].prior;
		countElem+=1;
		cout<<"\nA"<<curStr<<"B"<<curStlb<<" value = "<<needVal;
		if(lowStr[curStlb]==0 && rightStlb[curStr]>0){
			cout<<" Delete B"<<curStlb;
			for(int i=curStr+1;i<nStrok;i+=1) if(mas[i][curStlb].data==-2) mas[i][curStlb].data=-1;
			curStlb+=1;
		}
		else if(lowStr[curStlb]>0 && rightStlb[curStr]==0){
			cout<<" Delete A"<<curStr;
			for(int i=curStlb+1;i<nStolb;i+=1) if(mas[curStr][i].data==-2) mas[curStr][i].data=-1;
			curStr+=1;
		}
		else if(lowStr[curStlb]==0 && rightStlb[curStr]==0){
			if(curStlb==nStolb-1 && curStr==nStrok-1){
				PrintTable(mas,lowStr,rightStlb,nStrok,nStolb);
				break;
			}
			cout<<" Delete A"<<curStr<<", delte B"<<curStlb;
			uint8_t findNul=0;
			while(1){
				for(int i=0;i<nStolb;i+=1){
					if(mas[curStr][i].data==-2){
						mas[curStr][i].data=0;
						findNul=1;
						break;
					}
				}
				if(findNul==1) break;
				for(int i=0;i<nStrok;i+=1){
					if(mas[i][curStlb].data==-2){
						mas[i][curStlb].data=0;
						findNul=1;
						break;
					}
				}
				if(findNul==1) break;
			}
			for(int i=curStlb+1;i<nStolb;i+=1) if(mas[curStr][i].data==-2) mas[curStr][i].data=-1;
			for(int i=curStr+1;i<nStrok;i+=1) if(mas[i][curStlb].data==-2) mas[i][curStlb].data=-1;
			curStr+=1;
			curStlb+=1;
		}
		PrintTable(mas,lowStr,rightStlb,nStrok,nStolb);
		if(curStr>=nStrok || curStlb>=nStolb) break;
		if(dStr==curStr && dStlb==curStlb) break;
	}
	cout<<"\n Need elements: "<<IntToStr(nStrok)<<"+"<<IntToStr(nStolb)<<"-1="<<(nStrok+nStolb)-1<<", curent elements="<<countElem<<'\n';
	cout<<" z="<<multStr<<"="<<resSum<<'\n';
	//
	
	lowStr.clear();
	rightStlb.clear();
	free(mas);
	return 0;
}
