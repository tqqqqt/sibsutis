#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "lib.h"
#include "numbermath.h"

int checkInput(std::string _str){
	if(_str[0]=='0') return 1;
	for(const char& x:_str){
		if(!(x>='0' && x<='9')) return 1;
	}
	return 0;
}

void generNumber(std::string& num){
	if(num.length()<1) return;
	num[0]='0'+rand()%8+1;
	for(int i=1;i<num.length();i++) num[i]='0'+rand()%9;
}

void readPrim(std::vector<long long>& mas){
	std::ifstream file("prim2.txt");
	long long temp=0;
	while(file>>temp) mas.push_back(temp);
}

int main(){
	std::string input="";
	std::vector<long long> prim_mas;
	readPrim(prim_mas);
	while(1){
		input="";
		while(input!="1" && input!="2" && input!="3" && input!="4" && input!="5"){
			std::cout<<"\nMenu:\n 1-^modul\n 2-Evklid\n 3-key\n 4-shag\n 5-exit\n ->";
			std::cin>>input;
		}
		if(input=="5") break;
		else if(input=="1"){
			std::string module_num=std::to_string(prim_mas[rand()%(prim_mas.size()-1)+1]), num_a=std::to_string(rand()%std::stol(module_num)+1);
			long long num_x=rand()%std::stol(module_num)+1;
			std::cout<<"a = "<<num_a<<"\n x = "<<num_x<<"\n module num = "<<module_num<<'\n';
			std::cout<<"\n--------\n Result = "<<findModule(num_a,num_x,module_num)<<"\n--------\n \n";
		}
		else if(input=="2"){
			std::string num_1="000000000", num_2="999999999";
			generNumber(num_1);
			while(MaxNumber(num_1,num_2)==1) generNumber(num_2);
			std::cout<<"First num = "<<num_1<<"\nSecond num = "<<num_2<<'\n';
			std::cout<<"\n--------\n Result = "<<findNod(num_1,num_2)<<"\n--------\n \n";
		}
		else if(input=="3"){
			long long p=0, q=0;
			for(int i=prim_mas.size()-1;i>=0;i--){
				bool flg=false;
				for(int j=i-1;j>=0;j--){
					if(prim_mas[i]==(2*prim_mas[j])+1){
						flg=true;
						p=prim_mas[i];
						q=prim_mas[j];
						break;
					}
				}
				if(flg) break;
			}
			std::string g="3";
			while(1){
				if(findModule(g,q,std::to_string(p))!="1") break;
				g=MathSum(g,"1");
			}
			std::cout<<"\n--------\n Result:\n p = "<<p<<", q = "<<q<<", g = "<<g<<"\n";
			twoKeys(p,stoll(g));
			std::cout<<"\n--------\n \n";
		}
		else if(input=="4"){
			std::string input1="", input2="", input3="";
			std::cout<<"First num = ";
			std::cin>>input1;
			std::cout<<" module num = ";
			std::cin>>input2;
			std::cout<<" module res= ";
			std::cin>>input3;
			if(checkInput(input1) || checkInput(input2) || checkInput(input3)){
				std::cout<<"\nError input.\n";
				continue;
			}
			std::cout<<"\n--------\n Keys = ";
			findKey(input1,input2,input3);
			std::cout<<"\n--------\n \n";
		}
	}
	return 0;
}