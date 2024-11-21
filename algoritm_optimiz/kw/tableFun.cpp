#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <stdint.h>

#include "kwLib.cpp"
#include "structs.h"
using namespace std;

void PrintStartInfo(int *tempZ, int** tempMas, string tempNaprav, int nStrok, int nStolb){
	cout<<" Z=";
	uint8_t tempPrint=0;
	for(int i=0;i<nStolb-1;i+=1){
		if(tempZ[i]==0) continue;
		if(tempPrint==0){
			cout<<tempZ[i]<<"x"<<i+1;
			tempPrint+=1;
			continue;
		}
		if(tempZ[i]>0){
			cout<<"+";	
		} 
		cout<<tempZ[i]<<"x"<<i+1;
		tempPrint+=1;
	}
	if(tempZ[nStolb-1]>0) cout<<"+"<<tempZ[nStolb-1];
	else if(tempZ[nStolb-1]<0) cout<<tempZ[nStolb-1];
	cout<<" -> "<<tempNaprav<<"\n \n";
	for(int i=0;i<nStrok;i+=1){
		for(int j=0;j<nStolb;j+=1){
			cout<<std::right<<setw(4)<<tempMas[i][j]<<" ";
		}
		cout<<'\n';
	}
	cout<<"\n \n";
}

struct drobi FunctionZ(int *tempZ, struct leftStolb *leftMas, int napravFlag, int nStrok, int nStolb){
	struct drobi res;
	res.up=0;
	res.down=0;
	res.drob=false;
	for(int i=0;i<nStrok;i+=1){
		struct drobi numZ, tempRes;
		numZ.up=tempZ[leftMas[i].numX]*napravFlag;
		numZ.down=1;
		numZ.drob=false;
		DrobMathMul(&tempRes,numZ,leftMas[i].num);
		DrobMathSum(&res,res,tempRes);
		CheckDrob(&res);
	}
	if(tempZ[nStolb-1]!=0){
		struct drobi numZ;
		numZ.up=tempZ[nStolb-1];
		numZ.down=1;
		numZ.drob=false;
		DrobMathSum(&res,res,numZ);
		CheckDrob(&res);
	}
	return res;
}

void PrintTable(struct drobi **mas, struct leftStolb *leftMas, struct drobi *downMas, int *tempZ, int napravFlag, int nStrok, int nStolb){
	cout<<"\n \n";
	cout<<"BP|"<<std::right<<setw(8)<<"1"<<"|";
	for(int i=1;i<nStolb;i+=1) cout<<std::right<<setw(8)<<"x"<<i;
	cout<<"\n";
	for(int i=0;i<nStrok;i+=1){
		cout<<"x"<<leftMas[i].numX+1<<"|";
		if(leftMas[i].num.drob==true){
			cout<<std::right<<setw(4)<<leftMas[i].num.up<<"/"<<std::left<<setw(4)<<leftMas[i].num.down<<"|";
		}
		else cout<<std::right<<setw(8)<<leftMas[i].num.up<<"|";
		for(int j=0;j<nStolb-1;j+=1){
			if(mas[i][j].drob==true){
				cout<<std::right<<setw(4)<<mas[i][j].up<<"/"<<std::left<<setw(4)<<mas[i][j].down<<" ";
			}
			else cout<<std::right<<setw(8)<<mas[i][j].up<<" ";
		}
		cout<<"\n";
	}
	cout<<" Z|";
	struct drobi zRes=FunctionZ(tempZ,leftMas,napravFlag,nStrok,nStolb);
	if(zRes.drob==true) cout<<std::right<<setw(4)<<zRes.up<<"/"<<std::left<<setw(4)<<zRes.down<<"|";
	else cout<<std::right<<setw(8)<<zRes.up<<"|";
	for(int i=1;i<nStolb;i+=1){
		if(downMas[i].drob==true){
			cout<<std::right<<setw(4)<<downMas[i].up<<"/"<<std::left<<setw(4)<<downMas[i].down<<" ";
		}
		else cout<<std::right<<setw(8)<<downMas[i].up<<" ";
	}
	
	cout<<"\n \n";
}

void PrintPlan(struct leftStolb *leftMas, int *tempZ, int curentPlan, int napravFlag, int nStrok, int nStolb){
	cout<<" X^"<<curentPlan<<"=(";
	for(int needX=0;needX<nStolb-1;needX+=1){
		uint8_t find=0;
		if(needX!=0) cout<<",";
		for(int i=0;i<nStrok;i+=1){
			if(leftMas[i].numX!=needX) continue;
			find=i+1;
			break;
		}
		if(find==0){
			cout<<"0";
			continue;
		}
		if(leftMas[find-1].num.drob==true){
			cout<<leftMas[find-1].num.up<<"/"<<leftMas[find-1].num.down;
		}
		else cout<<leftMas[find-1].num.up;
	}
	cout<<")\n Z=";
	struct drobi zRes=FunctionZ(tempZ,leftMas,napravFlag,nStrok,nStolb);
	if(zRes.drob==true) cout<<zRes.up<<"/"<<zRes.down<<'\n';
	else cout<<zRes.up<<"\n \n";
}

void ComboFunctionZ(int *tempZ, struct linearCombo *masCombo, int napravFlag, int nStrok, int nStolb){
	struct drobi res;
	res.up=0;
	res.down=0;
	res.drob=false;
	for(int i=0;i<nStolb-1;i+=1){
		if(tempZ[i]==0) continue;
		struct drobi tempMul, numZ;
		numZ.up=tempZ[i]*napravFlag;
		numZ.down=1;
		numZ.drob=false;
		DrobMathMul(&tempMul,numZ,masCombo[i].numNoA);
		CheckDrob(&tempMul);
		DrobMathSum(&res,res,tempMul);
		CheckDrob(&res);
	}
	if(tempZ[nStolb-1]!=0){
		struct drobi numZ;
		numZ.up=tempZ[nStolb-1]*napravFlag;
		numZ.down=1;
		numZ.drob=false;
		DrobMathSum(&res,res,numZ);
		CheckDrob(&res);
	}
	if(res.drob==true) cout<<"\n \n Z(x*)="<<res.up<<"/"<<res.down<<'\n';
	else cout<<"\n \n Z(x*)="<<res.up<<'\n';
}