//var 3 - dvoist simplecs metod
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <stdlib.h>

#include "structs.h"
#include "kwLib.cpp"
#include "tableFun.cpp"
using namespace std;


void FindBasis(int **tempMas, int *tempBasis, int nStrok, int nStolb){
	int nullNum=0, checkNums=0, findBasis=0, lastNoNull=0;
	for(int i=0;i<nStolb;i+=1){
		nullNum=0;
		checkNums=0;
		lastNoNull=0;
		for(int j=0;j<nStrok;j+=1){
			if(tempMas[j][i]==0) nullNum+=1;
			else{
				checkNums+=tempMas[j][i];
				lastNoNull=j;
			}
		}
		if(checkNums>1 || checkNums<-1) continue;
		if(nullNum==nStrok-1 && checkNums==1){
			tempBasis[lastNoNull]=i;
			findBasis+=1;
		} 
		else if(nullNum==nStrok-1 && checkNums==-1){
			int needStr=0;
			for(int ii=0;ii<nStrok;ii+=1){
				if(tempMas[ii][i]==-1){
					needStr=ii;
					break;
				}
			}
			for(int ii=0;ii<nStolb;ii+=1){
				tempMas[needStr][ii]*=-1;
			}
			tempBasis[lastNoNull]=i;
			findBasis+=1;
		}
	}
}

void CheckZ(int *tempZ, int *tempBasis, int **tempMas, int nStrok, int nStolb){
	int checkBasis, needStr;
	uint8_t isBasis=0;
	for(int i=0;i<nStolb;i+=1){
		isBasis=0;
		needStr=0;
		if(tempZ[i]==0) continue;
		checkBasis=i;
		for(int i=0;i<nStrok;i+=1){
			if(tempBasis[i]==checkBasis){
				isBasis=1;
				break;
			}
		}
		if(isBasis==0) continue;
		for(int ii=0;ii<nStrok;ii+=1){
			if(tempMas[ii][i]==1){
				needStr=ii;
				break;
			}
		}
		int *tempForNewZ=(int*)malloc(sizeof(int)*nStolb);
		for(int ii=0;ii<nStolb-1;ii+=1){
			tempForNewZ[ii]=tempZ[i]*tempMas[needStr][ii]*-1;
		}
		tempForNewZ[nStolb-1]=tempZ[i]*tempMas[needStr][nStolb-1];
		for(int ii=0;ii<nStolb;ii+=1){
			if(ii==i) tempZ[ii]=0;
			else{
				tempZ[ii]=tempZ[ii]+tempForNewZ[ii];
			}
		}
		free(tempForNewZ);
	}
}

void ReadZ(int *tempZ, string tempStr, string *naprav, int nX){
	int length=tempStr.length(), i=0;
	int tempX=0, numX=0, flagMinus=1, flagX=0;
	while(tempStr[i]!='=') i+=1;
	for(i=i+1;i<length;i+=1){
		if(tempStr[i]=='-' && tempStr[i+1]=='>') break;
		if(flagX==0 && (tempStr[i]=='-')) flagMinus=-1;
		else if(flagX==0 && (tempStr[i]>='0' && tempStr[i]<='9')) tempX=tempX*10+(tempStr[i]-'0');
		else if(flagX!=0 && (tempStr[i]>='0' && tempStr[i]<='9')) numX=numX*10+(tempStr[i]-'0');
		else if(flagX!=0 && (tempStr[i]=='+' || tempStr[i]=='-')){
			if(tempX==0) tempX=1;
			tempZ[numX-1]=tempX*flagMinus;
			numX=0;
			tempX=0;
			flagX=0;
			if(tempStr[i]=='+') flagMinus=1;
			else if(tempStr[i]=='-') flagMinus=-1;
		}
		else if(tempStr[i]=='x') flagX=1;
	}
	if(numX!=0){
		if(tempX==0) tempX=1;
		tempZ[numX-1]=tempX*flagMinus;
	}
	else if(tempX!=0) tempZ[nX]=tempX*flagMinus;
	string tempNaprav="";
	for(i=i+2;i<length;i+=1) tempNaprav+=tempStr[i];
	*naprav=tempNaprav;
}

void ReadX(int **tempMas, string tempStr, int curentStr, int maxX, unordered_map<int,string> &znakMp){
	int length=tempStr.length(), i=0;
	int tempX=0, numX=0, flagMinus=1, flagX=0, curentX=0;
	for(i=0;i<length;i+=1){
		if(tempStr[i]=='<' || tempStr[i]=='>' || tempStr[i]=='=') break;
		if(flagX==0 && tempStr[i]=='-') flagMinus=-1;
		else if(flagX==0 && (tempStr[i]>='0' && tempStr[i]<='9')) tempX=tempX*10+(tempStr[i]-'0');
		else if(flagX!=0 && (tempStr[i]>='0' && tempStr[i]<='9')) numX=numX*10+(tempStr[i]-'0');
		else if(flagX!=0 && (tempStr[i]=='+' || tempStr[i]=='-')){
			if(tempX==0) tempX=1;
			if(numX-1!=curentX){
				while(numX-1!=curentX){
					tempMas[curentX][curentStr]=0;
					curentX+=1;
				}
			}
			tempMas[numX-1][curentStr]=tempX*flagMinus;
			numX=0;
			tempX=0;
			flagX=0;
			if(tempStr[i]=='+') flagMinus=1;
			else if(tempStr[i]=='-') flagMinus=-1;
			curentX+=1;
		}
		else if(tempStr[i]=='x') flagX=1;
	}
	if(numX!=0){
		if(tempX==0) tempX=1;
		if(numX-1!=curentX){
			while(numX-1!=curentX){
				tempMas[curentX][curentStr]=0;
				curentX+=1;
			}
		}
		tempMas[numX-1][curentStr]=tempX*flagMinus;
		curentX+=1;
	}
	else if(tempX!=0){
		if(tempX==0) tempX=1;
		tempMas[numX][curentStr]=tempX*flagMinus;
		curentX+=1;
	}
	while(curentX!=maxX){
		tempMas[curentX][curentStr]=0;
		curentX+=1;
	}
	string tempZnak="";
	for(i=i;i<length;i+=1){
		if(tempStr[i]!='=' && tempStr[i]!='<' && tempStr[i]!='>') break;
		tempZnak+=tempStr[i];
	}
	znakMp.insert(make_pair(curentStr,tempZnak));
	tempX=0;
	flagMinus=1;
	for(i=i;i<length;i+=1) tempX=tempX*10+(tempStr[i]-'0');
	tempMas[maxX][curentStr]=tempX*flagMinus;
}

struct drobi Shet(struct drobi mulNum1, struct drobi mulNum2, struct drobi delNum, struct drobi curentNum){
	struct drobi tempMul, tempDel, tempRes;
	DrobMathMul(&tempMul,mulNum1,mulNum2);
	CheckDrob(&tempMul);
	DrobMathDel(&tempDel,tempMul,delNum);
	CheckDrob(&tempDel);
	DrobMathRaz(&tempRes,curentNum,tempDel);
	CheckDrob(&tempRes);
	return tempRes;
}

int main(int argc, char** argv){
	if(argc!=2){
		cout<<"USAGE: ./a <file_name>\n";
		return -4;
	}
	ifstream file(argv[1]);
	int nUrav=0, nX=0;
	string tempInput="";
	file>>nUrav>>nX;
	int *tempTempZ=(int*)malloc((nX+1)*sizeof(int));
	for(int i=0;i<nX+1;i+=1) tempTempZ[i]=0;
	file>>tempInput;
	int napravFlag=0;
	string naprav;
	ReadZ(tempTempZ,tempInput,&naprav,nX);
	if(naprav=="min"){
		napravFlag=-1;
		cout<<"---------Change to -z, becouse in original z -> min.-----------\n";
		naprav="max";
	}
	else napravFlag=1;
	
	int **tempMasX=(int**)malloc((nX+nUrav+1)*sizeof(int*));
	for(int i=0;i<nX+nUrav+1;i+=1) tempMasX[i]=(int*)malloc(nUrav*sizeof(int));
	unordered_map<int,string> znakMp;
	for(int i=0;i<nUrav;i+=1){
		file>>tempInput;
		ReadX(tempMasX,tempInput,i,nX,znakMp);
	}
	int newX=0;
	for(int i=0;i<nUrav;i+=1){
		if(znakMp[i]=="=") continue;
		for(int j=0;j<nUrav;j+=1){
			tempMasX[nX+(newX)+1][j]=tempMasX[nX+(newX)][j];
			tempMasX[nX+(newX)][j]=0;
		}
		if(znakMp[i]=="<=") tempMasX[nX+(newX)][i]=1;
		else if(znakMp[i]==">=") tempMasX[nX+(newX)][i]=-1;
		newX+=1;
	}
	int **tempMas=(int**)malloc(nUrav*sizeof(int*));
	for(int i=0;i<nUrav;i+=1) tempMas[i]=(int*)malloc((nX+(newX)+1)*sizeof(int));
	for(int i=0;i<nUrav;i+=1){
		for(int j=0;j<(nX+(newX)+1);j+=1){
			tempMas[i][j]=tempMasX[j][i];
		}
	}
	
	int *tempZ=(int*)malloc((nX+(newX)+1)*sizeof(int));
	int tempP=0;
	for(tempP=0;tempP<nX;tempP+=1) tempZ[tempP]=tempTempZ[tempP]*napravFlag;
	for(tempP=tempP;tempP<(nX+(newX)+1);tempP+=1) tempZ[tempP]=0;
	
	
	int nStrok=nUrav;
	int nStolb=nX+newX+1;
	int *tempBasis=(int*)malloc(sizeof(int)*nStrok);
	
	free(tempTempZ);
	free(tempMasX);
	znakMp.clear();
	
	PrintStartInfo(tempZ,tempMas,naprav,nStrok,nStolb);
	FindBasis(tempMas,tempBasis,nStrok,nStolb);
	CheckZ(tempZ,tempBasis,tempMas,nStrok,nStolb);
	PrintStartInfo(tempZ,tempMas,naprav,nStrok,nStolb);
	
	cout<<"\n--------basis: ";
	for(int i=0;i<nStrok;i+=1) cout<<"x"<<tempBasis[i]+1<<" ";
	
	struct drobi **mas=(struct drobi**)malloc(nStrok*sizeof(struct drobi*));
	for(int i=0;i<nStrok;i+=1) mas[i]=(struct drobi*)malloc((nStolb-1)*sizeof(struct drobi));
	for(int i=0;i<nStrok;i+=1){
		for(int j=0;j<nStolb-1;j+=1){
			mas[i][j].up=tempMas[i][j];
			mas[i][j].down=1;
			mas[i][j].drob=false;
		}
	}
	
	struct leftStolb *leftMas=(struct leftStolb*)malloc(nStrok*sizeof(struct leftStolb));
	for(int i=0;i<nStrok;i+=1){
		leftMas[i].numX=tempBasis[i];
		leftMas[i].num.up=tempMas[i][nStolb-1];
		leftMas[i].num.down=1;
		leftMas[i].num.drob=false;
	}
	
	struct drobi *downMasZ=(struct drobi*)malloc(nStolb*sizeof(struct drobi));
	for(int i=1;i<nStolb;i+=1){
		downMasZ[i].up=tempZ[i-1]*-1;
		downMasZ[i].down=1;
		downMasZ[i].drob=false;
	}
	
	free(tempMas);
	free(tempBasis);
	
	PrintTable(mas,leftMas,downMasZ,tempZ,1,nStrok,nStolb);
	PrintPlan(leftMas,tempZ,1,1,nStrok,nStolb);
	
	//
	int curentStr=-1, curentStlb=-1, curentPlan=2;
	double curentMin=0;
	struct drobi *masCO;
	while(1){
		curentMin=0;
		curentStr=-1;
		curentStlb=-1;
		masCO=(struct drobi*)malloc(nStolb*sizeof(struct drobi));
		for(int i=0;i<nStrok;i+=1){
			if(leftMas[i].num.up>=0) continue;
			if((double)(leftMas[i].num.up/(double)leftMas[i].num.down)<(double)curentMin){
				curentMin=(double)(leftMas[i].num.up/(double)leftMas[i].num.down);
				curentStr=i;
			}
		}
		if(curentStr==-1){
			cout<<"----------No maxStr. No reshen.------------\n";
			break;
		}
		cout<<"--------Min str = "<<curentStr+1<<"--------\n";
		for(int i=1;i<nStolb;i+=1){
			if(downMasZ[i].up==0 || mas[curentStr][i-1].up>0){
				masCO[i].up=0;
				masCO[i].down=0;
				masCO[i].drob=false;
				continue;
			}
			struct drobi tempRes;
			DrobMathDel(&tempRes,downMasZ[i],mas[curentStr][i-1]);
			CheckDrob(&tempRes);
			masCO[i]=tempRes;
		}
		cout<<"CO|"<<std::right<<setw(8)<<" "<<"|";
		for(int i=1;i<nStolb;i+=1){
			if(masCO[i].drob==true) cout<<std::right<<setw(4)<<masCO[i].up<<"/"<<std::left<<setw(4)<<masCO[i].down<<" ";
			else cout<<std::right<<setw(8)<<masCO[i].up<<" ";
		}
		curentMin=99999999;
		for(int i=1;i<nStolb;i+=1){
			if(masCO[i].up==0) continue;
			if((double)fabs(masCO[i].up/(double)masCO[i].down)<(double)curentMin){
				curentMin=(double)fabs(masCO[i].up/(double)masCO[i].down);
				curentStlb=i-1;
			}
		}
		if(curentStlb==-1){
			cout<<"----------- No stlb. No reshen.------------\n";
			break;
		}
		cout<<"\n---------Min stlb = "<<curentStlb+1<<"----------\n";
		for(int i=1;i<nStolb;i+=1){
			if(i==curentStlb+1) continue;
			downMasZ[i]=Shet(mas[curentStr][i-1],downMasZ[curentStlb+1],mas[curentStr][curentStlb],downMasZ[i]);
		}
		for(int i=0;i<nStrok;i+=1){
			if(i==curentStr) continue;
			for(int j=0;j<nStolb-1;j+=1){
				if(j==curentStlb) continue;
				mas[i][j]=Shet(mas[curentStr][j],mas[i][curentStlb],mas[curentStr][curentStlb],mas[i][j]);
			}
		}
		for(int i=0;i<nStrok;i+=1){
			if(i==curentStr) continue;
			leftMas[i].num=Shet(leftMas[curentStr].num,mas[i][curentStlb],mas[curentStr][curentStlb],leftMas[i].num);
		}
		for(int i=0;i<nStolb-1;i+=1){
			if(i==curentStlb) continue;
			struct drobi temp;
			DrobMathDel(&temp,mas[curentStr][i],mas[curentStr][curentStlb]);
			CheckDrob(&temp);
			mas[curentStr][i]=temp;
		}
		struct drobi tempLeft;
		leftMas[curentStr].numX=curentStlb;
		DrobMathDel(&tempLeft,leftMas[curentStr].num,mas[curentStr][curentStlb]);
		CheckDrob(&tempLeft);
		leftMas[curentStr].num=tempLeft;
		for(int i=0;i<nStrok;i+=1){
			mas[i][curentStlb].up=0;
			mas[i][curentStlb].down=0;
			mas[i][curentStlb].drob=false;
		}
		downMasZ[curentStlb+1].up=0;
		downMasZ[curentStlb+1].down=0;
		downMasZ[curentStlb+1].drob=false;
		mas[curentStr][curentStlb].up=1;
		mas[curentStr][curentStlb].down=1;
		mas[curentStr][curentStlb].drob=false;
		
		PrintTable(mas,leftMas,downMasZ,tempZ,1,nStrok,nStolb);
		PrintPlan(leftMas,tempZ,curentPlan,1,nStrok,nStolb);
		curentPlan+=1;
		int findMinus=0;
		for(int i=0;i<nStrok;i+=1){
			if(leftMas[i].num.up<0){
				findMinus+=1;
				break;
			}
		}
		free(masCO);
		if(findMinus==0) break;
	}
	if(napravFlag==-1){
		cout<<"----------Return to original z.--------------\n";
		PrintPlan(leftMas,tempZ,curentPlan-1,-1,nStrok,nStolb);
	}
	int findMinus=0;
	for(int i=1;i<nStolb;i+=1){
		if(downMasZ[i].up<0) findMinus+=1;
	}
	if(findMinus==0) cout<<"-------------Resh optim.---------------\n";
	else{
		cout<<"---------------Resh ne optim.-----------------\n";
		masCO=(struct drobi*)malloc(nStrok*sizeof(int));
		while(1){
			curentMin=0;
			curentStr=-1;
			curentStlb=-1;
			for(int i=1;i<nStolb;i+=1){
				if(downMasZ[i].up<0 && (double)fabs(downMasZ[i].up/(double)downMasZ[i].down)>curentMin){
					curentMin=(double)fabs(downMasZ[i].up/(double)downMasZ[i].down);
					curentStlb=i-1;
				}
			}
			if(curentStlb==-1){
				cout<<"----------No null in stolb.-------------\n";
				break;
			}
			cout<<"----------Max stolb="<<curentStlb+1<<"-----------\n";
			curentMin=99999999;
			for(int i=0;i<nStrok;i+=1){
				if(mas[i][curentStlb].up<=0){
					masCO[i].up=0;
					masCO[i].down=0;
					masCO[i].drob=false;
					continue;
				}
				struct drobi tempRes;
				DrobMathDel(&tempRes,leftMas[i].num,mas[i][curentStlb]);
				CheckDrob(&tempRes);
				masCO[i]=tempRes;
				if((double)(tempRes.up/(double)tempRes.down)<curentMin){
					curentMin=(double)(tempRes.up/(double)tempRes.down);
					curentStr=i;
				}
			}
			cout<<"CO|\n";
			for(int i=0;i<nStrok;i+=1){
				if(masCO[i].drob==true) cout<<masCO[i].up<<"/"<<masCO[i].down<<"\n";
				else cout<<masCO[i].up<<"\n";
			}
			if(curentStr==-1){
				cout<<"-----------No curentStr. No resh.-------------\n";
				break;
			}
			cout<<"----------min str="<<curentStr+1<<"-----------------\n";
			for(int i=1;i<nStolb;i+=1){
				if(i==curentStlb+1) continue;
				downMasZ[i]=Shet(mas[curentStr][i-1],downMasZ[curentStlb+1],mas[curentStr][curentStlb],downMasZ[i]);
			}
			for(int i=0;i<nStrok;i+=1){
				if(i==curentStr) continue;
				for(int j=0;j<nStolb-1;j+=1){
					if(j==curentStlb) continue;
					mas[i][j]=Shet(mas[curentStr][j],mas[i][curentStlb],mas[curentStr][curentStlb],mas[i][j]);
				}
			}
			for(int i=0;i<nStrok;i+=1){
				if(i==curentStr) continue;
				leftMas[i].num=Shet(leftMas[curentStr].num,mas[i][curentStlb],mas[curentStr][curentStlb],leftMas[i].num);
			}
			for(int i=0;i<nStolb-1;i+=1){
				if(i==curentStlb) continue;
				struct drobi temp;
				DrobMathDel(&temp,mas[curentStr][i],mas[curentStr][curentStlb]);
				CheckDrob(&temp);
				mas[curentStr][i]=temp;
			}
			struct drobi tempLeft;
			leftMas[curentStr].numX=curentStlb;
			DrobMathDel(&tempLeft,leftMas[curentStr].num,mas[curentStr][curentStlb]);
			CheckDrob(&tempLeft);
			leftMas[curentStr].num=tempLeft;
			for(int i=0;i<nStrok;i+=1){
				mas[i][curentStlb].up=0;
				mas[i][curentStlb].down=0;
				mas[i][curentStlb].drob=false;
			}
			downMasZ[curentStlb+1].up=0;
			downMasZ[curentStlb+1].down=0;
			downMasZ[curentStlb+1].drob=false;
			mas[curentStr][curentStlb].up=1;
			mas[curentStr][curentStlb].down=1;
			mas[curentStr][curentStlb].drob=false;
			PrintTable(mas,leftMas,downMasZ,tempZ,1,nStrok,nStolb);
			PrintPlan(leftMas,tempZ,curentPlan,1,nStrok,nStolb);
			curentPlan+=1;
			int findMinus=0;
			for(int i=1;i<nStolb;i+=1){
				if(downMasZ[i].up<0){
					findMinus+=1;
					break;
				}
			}
			if(findMinus==0) {
				cout<<"-----------------Resh optim.-----------------\n";
				break;
			}
		}
		free(masCO);
	}

	int tempFindNull=0;
	for(int i=1;i<nStolb;i+=1){
		if(downMasZ[i].up!=0) continue;
		tempFindNull=0;
		for(int j=0;j<nStrok;j+=1){
			if(leftMas[j].numX==i-1){
				tempFindNull+=1;
				break;
			}
		}
		if(tempFindNull!=0) continue;
		break;
	}
	if(tempFindNull!=0) cout<<"------------Edinstven reshen.---------------\n";
	else{
		cout<<"---------------Ne edinstv reshen.-------------------\n";
		int oldX=-1, flagBescon=0;
		curentStlb=-1;
		masCO=(struct drobi*)malloc(nStrok*sizeof(struct drobi));
		struct drobi *xBefore, *xAfter;
		xBefore=(struct drobi*)malloc(nStolb*sizeof(struct drobi));
		xAfter=(struct drobi*)malloc(nStolb*sizeof(struct drobi));
		int findX=0;
		while(1){
			for(int i=0;i<nStolb;i+=1){
				findX=0;
				for(int j=0;j<nStrok;j+=1){
					if(leftMas[j].numX==i){
						findX=1;
						xBefore[i]=leftMas[j].num;
						break;
					}
				}
				if(findX==1) continue;
				xBefore[i].up=0;
				xBefore[i].down=0;
				xBefore[i].drob=false;
			}
			curentMin=0;
			curentStr=-1;
			curentStlb=-1;
			int findNull=0;
			for(int i=1;i<nStolb;i+=1){
				if(downMasZ[i].up!=0) continue;
				findNull=0;
				for(int j=0;j<nStrok;j+=1){
					if(leftMas[j].numX==i-1){
						findNull+=1;
						break;
					}
				}
				if(findNull!=0) continue;
				curentStlb=i-1;
				break;
			}
			if(curentStlb==-1) break;
			cout<<"--------------Find null in stlb="<<curentStlb+1<<"--------\n";
			curentMin=99999999;
			for(int i=0;i<nStrok;i+=1){
				if(mas[i][curentStlb].up<=0){
					masCO[i].up=0;
					masCO[i].down=0;
					masCO[i].drob=false;
					continue;
				}
				struct drobi tempRes;
				DrobMathDel(&tempRes,leftMas[i].num,mas[i][curentStlb]);
				CheckDrob(&tempRes);
				masCO[i]=tempRes;
				if((double)(tempRes.up/(double)tempRes.down)<curentMin){
					curentMin=(double)(tempRes.up/(double)tempRes.down);
					curentStr=i;
				}
			}
			cout<<"CO|\n";
			for(int i=0;i<nStrok;i+=1){
				if(masCO[i].drob==true) cout<<masCO[i].up<<"/"<<masCO[i].down<<"\n";
				else cout<<masCO[i].up<<"\n";
			}
			if(curentStr==-1){
				cout<<"-----------No curentStr. No resh.----------\n";
				break;
			}
			cout<<"-----------Min str="<<curentStr<<"--------\n";
			if(oldX==curentStlb){
				cout<<"------------Beskonecnoe reshenie. Old change x"<<oldX+1<<" curent change x"<<curentStlb+1<<"----------------\n";
				flagBescon=1;
				break;
			}
			oldX=leftMas[curentStr].numX;
			for(int i=1;i<nStolb;i+=1){
				if(i==curentStlb+1) continue;
				downMasZ[i]=Shet(mas[curentStr][i-1],downMasZ[curentStlb+1],mas[curentStr][curentStlb],downMasZ[i]);
			}
			for(int i=0;i<nStrok;i+=1){
				if(i==curentStr) continue;
				for(int j=0;j<nStolb-1;j+=1){
					if(j==curentStlb) continue;
					mas[i][j]=Shet(mas[curentStr][j],mas[i][curentStlb],mas[curentStr][curentStlb],mas[i][j]);
				}
			}
			for(int i=0;i<nStrok;i+=1){
				if(i==curentStr) continue;
				leftMas[i].num=Shet(leftMas[curentStr].num,mas[i][curentStlb],mas[curentStr][curentStlb],leftMas[i].num);
			}
			for(int i=0;i<nStolb-1;i+=1){
				if(i==curentStlb) continue;
				struct drobi temp;
				DrobMathDel(&temp,mas[curentStr][i],mas[curentStr][curentStlb]);
				CheckDrob(&temp);
				mas[curentStr][i]=temp;
			}
			struct drobi tempLeft;
			leftMas[curentStr].numX=curentStlb;
			DrobMathDel(&tempLeft,leftMas[curentStr].num,mas[curentStr][curentStlb]);
			CheckDrob(&tempLeft);
			leftMas[curentStr].num=tempLeft;
			for(int i=0;i<nStrok;i+=1){
				mas[i][curentStlb].up=0;
				mas[i][curentStlb].down=0;
				mas[i][curentStlb].drob=false;
			}
			downMasZ[curentStlb+1].up=0;
			downMasZ[curentStlb+1].down=0;
			downMasZ[curentStlb+1].drob=false;
			mas[curentStr][curentStlb].up=1;
			mas[curentStr][curentStlb].down=1;
			mas[curentStr][curentStlb].drob=false;
			PrintTable(mas,leftMas,downMasZ,tempZ,1,nStrok,nStolb);
			PrintPlan(leftMas,tempZ,curentPlan,1,nStrok,nStolb);
			curentPlan+=1;	
		}
		free(masCO);
		if(flagBescon==1){
			for(int i=0;i<nStolb;i+=1){
				findX=0;
				for(int j=0;j<nStrok;j+=1){
					if(leftMas[j].numX==i){
						findX=1;
						xAfter[i]=leftMas[j].num;
						break;
					}
				}
				if(findX==1) continue;
				xAfter[i].up=0;
				xAfter[i].down=0;
				xAfter[i].drob=false;
			}
			cout<<"\n--------------Create linear combo X^"<<curentPlan-2<<" and X^"<<curentPlan-1<<"----------\n";
			struct linearCombo *masCombo=(struct linearCombo*)malloc(nStolb*sizeof(struct linearCombo));
			for(int i=0;i<nStolb;i+=1){
				struct drobi tempRes1, tempRes2;
				struct drobi numOne, numMinusOne;
				numOne.up=1;
				numOne.down=1;
				numOne.drob=false;
				numMinusOne.up=-1;
				numMinusOne.down=1;
				numMinusOne.drob=false;
				DrobMathMul(&tempRes1,numOne,xBefore[i]);
				masCombo[i].numNoA=tempRes1;
				DrobMathMul(&tempRes2,numMinusOne,xBefore[i]);
				DrobMathSum(&tempRes2,tempRes2,xAfter[i]);
				masCombo[i].numA=tempRes2;
			}
			cout<<"x*=(";
			for(int i=0;i<nStolb;i+=1){
				if(i!=0) cout<<", ";
				cout<<masCombo[i].numNoA.up<<"/"<<masCombo[i].numNoA.down;
				if(masCombo[i].numA.up>=0) cout<<"+"<<masCombo[i].numA.up<<"/"<<masCombo[i].numA.down<<"A";
				else cout<<masCombo[i].numA.up<<"/"<<masCombo[i].numA.down<<"A";
			}
			cout<<")";
			ComboFunctionZ(tempZ,masCombo,napravFlag,nStrok,nStolb);
		}
		free(xAfter);
		free(xBefore);
	}

	free(leftMas);
	free(mas);
	free(tempZ);
	return 0;
}
