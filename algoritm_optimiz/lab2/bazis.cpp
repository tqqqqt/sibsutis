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
			if(mas[i][j].drob==true){
				cout<<std::right<<setw(10)<<mas[i][j].upNum<<"/"<<std::left<<setw(10)<<mas[i][j].downNum<<" ";
			}
			else cout<<std::setiosflags(ios::right)<<setw(20)<<mas[i][j].upNum;
		}
		cout<<'\n';
	}
	cout<<"\n \n";
}

void DrobMathSimple(struct drobi *resNum, struct drobi &num1, struct drobi &num2){
	if(num2.downNum==0 || num2.upNum==0){
		resNum->upNum=num1.upNum;
		resNum->downNum=num1.downNum;
		return;
	}
	if(num1.upNum==0 || num1.downNum==0){
		if((num2.upNum<0 && num2.downNum>0) || (num2.downNum<0 && num2.upNum>0)){
			resNum->upNum=num2.upNum<0 ? num2.upNum*(-1) : num2.upNum;
			resNum->downNum=num2.downNum<0 ? num2.downNum*(-1) : num2.downNum;
			return;
		}
		if(num2.upNum<0 && num2.downNum<0){
			resNum->upNum=num2.upNum;
			resNum->downNum=num2.downNum*(-1);
			return;
		}	
		resNum->upNum=0-num2.upNum;
		resNum->downNum=num2.downNum;
		return;
	}
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
	if(num->downNum==0) return;
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
	int newStrok=*strok+1, newStolb=*stolb+1, noNull=0;
	struct drobi newElement, temp;
	newElement.upNum=1;
	newElement.downNum=1;
	for(int i=*stolb+1;i<masStolb-1;i++){
		noNull=0;
		for(int j=*strok+1;j<masStrok;j++){
			if(mas[j][i].visible==true && mas[j][i].upNum!=0){
				noNull+=1;
				if(mas[j][i].drob==true){
					if(abs(mas[j][i].upNum/mas[j][i].downNum)>abs(newElement.upNum/newElement.downNum)){
						newStrok=j;
						newStolb=i;
						newElement=mas[j][i];
					}
				}
				else if(abs(mas[j][i].upNum)>abs(newElement.upNum)){
					newStrok=j;
					newStolb=i;
					newElement=mas[j][i];
				}
			}
		}
		if(noNull>0) break;
	}
	if(noNull==0) return 0;
	for(int i=0;i<masStolb;i++){
		temp=mas[newStrok][i];
		mas[newStrok][i]=mas[*strok+1][i];
		mas[*strok+1][i]=temp;
	}
	for(int i=*stolb+1;i<masStolb-1;i++){
		for(int j=*strok+1;j<masStrok;j++){
			if(mas[j][i].visible==true && mas[j][i].upNum!=0){
				*strok=j;
				*stolb=i;
				return 1;
			}
		}
	}
	return 1;
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

int LabWork(struct drobi **mas, int &masStrok, int &masStolb){
	int curentStrok=0, curentStolb=0, granStrok=masStrok, exitStatus=1;
	struct drobi curentNum;
	while(exitStatus==1){
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
		if(CheckFastEnd(mas,masStrok,masStolb)) return 4;
		exitStatus=NextNum(mas,masStrok,masStolb,&curentStrok,&curentStolb);
		PrintMas(mas,masStrok,masStolb);
	}
	cout<<"\n Res matrica: \n";
	PrintMas(mas,masStrok,masStolb);
	return 0;
	//PrintRes(mas,masStrok,masStolb);
	//PrintOneX(mas,masStrok,masStolb);
}

int RangMatric(struct drobi **mas, int &masStrok, int &masStolb){
	int res=0;
	for(int i=0;i<masStrok;i++){
		if(mas[i][masStolb-1].visible==true) res+=1;
	}
	return res;
}

int Factorial(int x){
	if(x==1) return 1;
	return x*Factorial(x-1);
}

int NumCombo(int rang, int numX){
	return (Factorial(numX))/(Factorial(rang)*Factorial(numX-rang));
}

void CreateCombo(int *mas, int &rang, int &numX){
	for(int p=rang-1;p>=0;p--){
	    if(mas[p]<numX-rang+p+1){
	        mas[p]++;
	        for(int i=p+1;i<rang;i++) mas[i]=mas[i-1]+1;
	        return;
	    }
	}
}

void CopyMas(struct drobi **buffer, struct drobi **mas, int &masStrok, int &masStolb){
	for(int i=0;i<masStrok;i++){
		for(int j=0;j<masStolb;j++) buffer[i][j]=mas[i][j];
	}
}

void PrintCombo(int *mas, int &rang){
	for(int i=0;i<rang;i++) cout<<"X"<<mas[i]<<",";
	cout<<" - ";
}

int CheckBazisLife(struct drobi **masDrob, int &masStrok, int &masStolb, int *masX, int &rang){
	int temp=0, find=0;
	for(int i=0;i<rang;i++){
		temp=0;
		find=0;
		for(int ii=0;ii<masStrok;ii++){
			if(masDrob[ii][masX[i]-1].visible==false) continue;
			if(masDrob[ii][masX[i]-1].upNum==0) continue;
			if(masDrob[ii][masX[i]-1].upNum+masDrob[ii][masX[i]-1].downNum==2){
				find=1;
				for(int j=0;j<rang;j++) temp+=masDrob[ii][masX[j]-1].upNum+masDrob[ii][masX[j]-1].downNum;
				if(temp==0 || temp==4) return 1;
				if(temp>4) return 2;
				if(temp==2) break;
			} 
			else find-=1;
		}
		if(find<0) return 2;
		if(find==0) return 1;
	}
	return 0;
}

int BufferShet(struct drobi **mas, int &masStrok, int &masStolb, int *masX, int &rang){
	int tempStolb=-1, tempStrok=-1, temp=0;
	for(int i=0;i<rang;i++){
		tempStolb=-1;
		for(int ii=0;ii<masStrok;ii++){
			if(mas[ii][masX[i]-1].visible==false) continue;
			if(mas[ii][masX[i]-1].upNum!=0 && mas[ii][masX[i]-1].upNum+mas[ii][masX[i]-1].downNum!=2){
				tempStolb=masX[i]-1;
				break;
			}
		}
		if(tempStolb!=-1) break;
	}
	if(tempStolb==-1) return 1;
	temp=0;
	for(int i=0;i<masStrok;i++){
		if(mas[i][0].visible==false) continue;
		tempStrok=-1;
		temp=0;
		for(int j=0;j<rang;j++){
			if(masX[j]-1==tempStolb) continue;
			temp=mas[i][masX[j]-1].upNum+mas[i][masX[j]-1].downNum;
			if(temp==2) break;
		}
		if(temp==0 || temp!=2){
			tempStrok=i;
			break;
		}
	}
	if(tempStrok==-1) return 1;
	struct drobi curentNum;
	curentNum=mas[tempStrok][tempStolb];
	for(int j=0;j<masStolb;j++){
		if(j==tempStolb) continue;
		for(int i=0;i<masStrok;i++){
			if(i==tempStrok) continue;
			if(mas[i][j].visible==false) continue;
			if(mas[tempStrok][j].upNum==0 || mas[i][tempStolb].upNum==0) continue;
			mas[i][j]=FullShet(mas[i][j],mas[tempStrok][j],mas[i][tempStolb],curentNum);
		}
	}
	for(int i=0;i<masStolb;i++){
		if(mas[tempStrok][i].upNum==0 || mas[tempStrok][i].downNum==0) continue;
		if(i==tempStolb){
			mas[tempStrok][i].upNum=1;
			mas[tempStrok][i].downNum=1;
			mas[tempStrok][i].drob=false;
			continue;
		}
		DrobMathDel(&mas[tempStrok][i],mas[tempStrok][i],curentNum);
		CheckDrob(&mas[tempStrok][i]);
	}
	for(int i=0;i<masStrok;i++){
		if(i==tempStrok) continue;
		mas[i][tempStolb].upNum=0;
		mas[i][tempStolb].downNum=0;
		mas[i][tempStolb].drob=false;
	}
	PrintMas(mas,masStrok,masStolb);
	CheckNullStrok(mas,masStrok,masStolb);
	return 0;
}

void PrintBazis(struct drobi **mas, int &masStrok, int &masStolb, int *masX, int &rang){
	int tempMasX=0, tempBack=0;
	cout<<"Bazis - (";
	for(int i=0;i<masStolb-1;i++){
		if(tempBack!=0) cout<<";";
		if(i!=masX[tempMasX]-1) cout<<"0";
		else{
			for(int j=0;j<masStrok;j++){
				if(mas[j][i].visible==false) continue;
				if(mas[j][i].upNum==0) continue;
				if(mas[j][i].upNum==1){
					if(mas[j][masStolb-1].drob==false) cout<<mas[j][masStolb-1].upNum;
					else cout<<mas[j][masStolb-1].upNum<<"/"<<mas[j][masStolb-1].downNum;
				}
			}
			tempMasX+=1;
		}
		tempBack+=1;
	}
	cout<<")\n \n";
}

void Bazis(struct drobi **mas, int &masStrok, int &masStolb){
	int rang=RangMatric(mas,masStrok,masStolb), numX=masStolb-1, numCombo;
	if(rang-numX==0) {
		cout<<"No basiz (rang-numX==0).";
		return;
	}
	else numCombo=NumCombo(rang,numX);
	cout<<" Rang - "<<rang<<" NumCombo - "<<numCombo<<'\n';
	struct drobi **bazisBuf=(struct drobi**)malloc(sizeof(struct drobi)*masStrok);
	for(int i=0;i<masStrok;i++) bazisBuf[i]=(struct drobi*)malloc(sizeof(struct drobi)*masStolb);
	CopyMas(bazisBuf,mas,masStrok,masStolb);
	int *masX=(int*)malloc(sizeof(int)*rang), tempResCheck=0, tempResShet=0;
	for(int i=0;i<rang;i++) masX[i]=i+1;
	for(int i=0;i<numCombo;i++){
		tempResCheck=0;
		if(i!=0) CreateCombo(masX,rang,numX);
		cout<<i+1<<") ";
		PrintCombo(masX,rang);
		tempResCheck=CheckBazisLife(bazisBuf,masStrok,masStolb,masX,rang);
		if(tempResCheck==1){
			cout<<"No bazis.\n";
			continue;
		}
		if(tempResCheck==2){
			tempResShet=0;
			CopyMas(bazisBuf,mas,masStrok,masStolb);
			int exitRes=0;
			while(1){
				cout<<"\n";
				tempResShet=BufferShet(bazisBuf,masStrok,masStolb,masX,rang);
				if(tempResShet){
					cout<<"No basiz.\n";
					CopyMas(bazisBuf,mas,masStrok,masStolb);
					exitRes=-1;
					break;
				}
				tempResCheck=CheckBazisLife(bazisBuf,masStrok,masStolb,masX,rang);
				if(tempResCheck==1){
					cout<<"No bazis.\n";
					CopyMas(bazisBuf,mas,masStrok,masStolb);
					exitRes=-1;
					break;
				}
				if(tempResCheck==0) break;
			}
			if(exitRes==-1) continue;
		}
		PrintBazis(bazisBuf,masStrok,masStolb,masX,rang);
		CopyMas(bazisBuf,mas,masStrok,masStolb);
	}
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
	if(LabWork(mas,nStrok,nStolb)==0) Bazis(mas,nStrok,nStolb);
	return 0;
}
