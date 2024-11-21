#include <iostream>
#include <fstream>

#include "structs.h"
#include "kwLib.cpp"
#include "tableFun.cpp"
using namespace std;

int main(int argc, char **argv){
	ifstream file(argv[1]);
	int nStrok=0, nStolb=0;
	file>>nStrok>>nStolb;
	struct drobi **mas=(struct drobi**)malloc(nStrok*sizeof(struct drobi));
	for(int i=0;i<nStrok;i+=1) mas[i]=(int*)malloc(nStolb*sizeof(struct drobi));
	for(int i=0;i<nStrok;i+=1){
		for(int j=0;j<nStolb;j+=1){
			file>>mas[i][j].up;
			mas[i][j].down=1;
			mas[i][j].drob=false;
		}
	}
	int curentStr=-1, curentStlb=-1;
	while(1){
		curentStr=-1;
		curentStlb=-1;
		
	}
	return 0;
}
