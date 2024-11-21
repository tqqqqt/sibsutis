#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

struct drobi{
	long long upNum, downNum;
	bool drob, visible;
};

void PrintMas(struct drobi **mas, int &n, int &m){
	for(int i=0;i<n;i++){
		if(mas[i][0].visible==false) continue;
		for(int j=0;j<m;j++){
			if(mas[i][j].drob==true) cout<<std::setiosflags(ios::left)<<mas[i][j].upNum<<"/"<<mas[i][j].downNum<<setw(4)<<" ";
			else cout<<std::setiosflags(ios::left)<<mas[i][j].upNum<<setw(4)<<" ";
		}
		cout<<'\n';
	}
	cout<<"\n \n";
}

void DrobMathSimple(struct drobi *resNum, struct drobi &num1, struct drobi &num2){
	resNum->upNum=(num1.upNum*num2.downNum)-(num2.upNum*num1.downNum);
	resNum->downNum=num1.downNum*num2.downNum;
}

void DrobMathDel(struct drobi *resNum, struct drobi &num1, struct drobi &num2){
	resNum->upNum=num1.upNum*num2.downNum;
	resNum->downNum=num1.downNum*num2.upNum;
}

void DrobMathUmn(struct drobi *resNum, struct drobi &num1, struct drobi &num2){
	resNum->upNum=num1.upNum*num2.upNum;
	resNum->downNum=num1.downNum*num2.downNum;
}

long long FindDel(long long a, long long b){
	if(b==0) return a;
	return FindDel(b,a%b);
}

void CheckDrob(struct drobi *num){
	if(num->upNum%num->downNum==0){
		num->upNum/=num->downNum;
		num->downNum=1;
		num->drob=false;
		return;
	}
	num->drob=true;
	long long delNum=FindDel(num->upNum,num->downNum);
	if(delNum==0) return;
	num->upNum/=delNum;
	num->downNum/=delNum;
}

struct drobi FullShet(struct drobi &simpleNum, struct drobi &del1, struct drobi &del2, struct drobi &curentNum){
	struct drobi tempNum;
	tempNum.upNum=0;
	tempNum.downNum=0;
	tempNum.visible=true;
	if(del1.drob==true || del2.drob==true){
		DrobMathUmn(&tempNum,del1,del2);
		CheckDrob(&tempNum);
	}
	else{
		tempNum.upNum=del1.upNum*del2.upNum;
		tempNum.downNum=1;
		tempNum.drob=false;
	}
	DrobMathDel(&tempNum,tempNum,curentNum);
	CheckDrob(&tempNum);
	DrobMathSimple(&tempNum,simpleNum,tempNum);
	CheckDrob(&tempNum);
	return tempNum;
}

void CheckNullStrok(struct drobi **mas, int &masStrok, int &masStolb){
	int checkNull=0;
	for(int i=0;i<masStrok;i++){
		checkNull=0;
		for(int j=0;j<masStolb;j++){
			if(mas[i][j].upNum==0) ++checkNull;
		}
		if(checkNull==masStolb){
			for(int j=0;j<masStolb;j++) mas[i][j].visible=false;
		}
	}
}

int CheckFastEnd(struct drobi **mas, int &masStrok, int &masStolb){
	int checkNull=0;
	for(int i=0;i<masStrok;i++){
		checkNull=0;
		for(int j=0;j<masStolb-1;j++){
			if(mas[i][j].visible==true && mas[i][j].upNum==0) ++checkNull;
		}
		if(mas[i][masStolb-1].upNum==1 && checkNull==masStolb-1){
			cout<<" No result in "<<i+1<<" string.";
			return 1;
		}
	}
	return 0;
}

int NextNum(struct drobi **mas, int &masStrok, int &masStolb, int *strok, int *stolb){
	for(int i=*stolb+1;i<masStolb-1;i++){
		for(int j=*strok+1;j<masStrok;j++){
			if(mas[j][i].visible==true && mas[j][i].upNum!=0){
				*strok=j;
				*stolb=i;
				return 1;
			}
		}
	}
	return 0;
}

void PrintRes(struct drobi **mas, int &strok, int &stolb){
	cout<<" Result: \n";
	int temp=0;
	for(int i=0;i<strok;i++){
		if(mas[i][0].visible==false) continue;
		temp=0;
		for(int j=0;j<stolb-1;j++){
			if(mas[i][j].upNum==0) continue;
			if(temp>0) cout<<" + ";
			if(mas[i][j].drob==true) cout<<mas[i][j].upNum<<"/"<<mas[i][j].downNum<<" * x"<<j+1;
			else cout<<mas[i][j].upNum<<" * x"<<j+1;
			temp++;
		}
		cout<<" = "<<mas[i][stolb-1].upNum<<'\n';
	}
	cout<<"\n \n";
}

void ReZnak(struct drobi *element){
	if(element->drob==false){
		element->upNum*=-1;
		return;
	}
	if((element->upNum<0 && element->downNum<0) || (element->upNum>0 && element->downNum>0)){
		element->downNum*=-1;
		return;
	}
	if(element->upNum<0){
		element->upNum*=-1;
		return;
	}
	if(element->downNum<0){
		element->downNum*=-1;
		return;
	}
}

void PrintOneX(struct drobi **mas, int &strok, int &stolb){
	int temp=0, ttemp=0;
	for(int i=0;i<strok;i++){
		temp=-1;
		ttemp=0;
		for(int j=i;j<stolb-1;j++){
			if(mas[i][j].upNum==1){
				temp=j+1;
				break;
			}
		}
		if(temp==-1) continue;
		cout<<"x"<<temp<<" = ";
		for(int j=0;j<stolb-1;j++){
			if(j==temp-1) continue;
			if(mas[i][j].upNum==0) continue;
			if(ttemp>0) cout<<" + ";
			ReZnak(&mas[i][j]);
			if(mas[i][j].drob==true) cout<<mas[i][j].upNum<<"/"<<mas[i][j].downNum<<" * x"<<j+1;
			else cout<<mas[i][j].upNum<<" * x"<<j+1;
			ttemp++;
		}
		if(ttemp>0) cout<<" + ";
		cout<<mas[i][stolb-1].upNum<<'\n';
	}
}

void LabWork(struct drobi **mas, int &masStrok, int &masStolb){
	int curentStrok=0, curentStolb=0, granStrok=masStrok, exitStatus=1;
	struct drobi curentNum;
	while(exitStatus){
		curentNum=mas[curentStrok][curentStolb];
		for(int j=curentStolb+1;j<masStolb;j++){
			if(j==curentStolb) continue;
			for(int i=0;i<masStrok;i++){
				if(i==curentStrok) continue;
				if(mas[i][j].visible==false) continue;
				mas[i][j]=FullShet(mas[i][j],mas[curentStrok][j],mas[i][curentStolb],curentNum);
			}
		}
		for(int i=curentStolb;i<masStolb;i++){
			if(i==curentStolb){
				mas[curentStrok][i].upNum=1;
				mas[curentStrok][i].downNum=1;
				mas[curentStrok][i].drob=false;
				continue;
			}
			DrobMathDel(&mas[curentStrok][i],mas[curentStrok][i],curentNum);
			CheckDrob(&mas[curentStrok][i]);
		}
		for(int i=0;i<masStrok;i++){
			if(i==curentStrok) continue;
			mas[i][curentStolb].upNum=0;
			mas[i][curentStolb].downNum=0;
			mas[i][curentStolb].drob=false;
		}
		PrintMas(mas,masStrok,masStolb);
		CheckNullStrok(mas,masStrok,masStolb);
		if(CheckFastEnd(mas,masStrok,masStolb)) return;
		exitStatus=NextNum(mas,masStrok,masStolb,&curentStrok,&curentStolb);
	}
	cout<<"\n Res matrica: \n";
	PrintMas(mas,masStrok,masStolb);
	PrintRes(mas,masStrok,masStolb);
	PrintOneX(mas,masStrok,masStolb);
}

int main(int argc, char *argv[]){
	int nStrok=0, nStolb=0;
	ifstream file(argv[1]);
	file>>nStrok>>nStolb;
	struct drobi **mas=(struct drobi**)malloc(sizeof(struct drobi)*nStrok);
	for(int i=0;i<nStrok;i++) mas[i]=(struct drobi*)malloc(sizeof(struct drobi)*nStolb);
	for(int i=0;i<nStrok;i++){
		for(int j=0;j<nStolb;j++){
			file>>mas[i][j].upNum;
			mas[i][j].downNum=1;
			mas[i][j].drob=false;
			mas[i][j].visible=true;
		}
	}
	PrintMas(mas,nStrok,nStolb);
	LabWork(mas,nStrok,nStolb);
	return 0;
}
