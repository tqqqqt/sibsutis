#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "lab3lib.h"
#include "numbermath.h"

void readPrimsNum(std::vector<long long>& prim_mas){
	std::ifstream file_prim("prim2.txt");
	long long temp=0;
	while(file_prim>>temp) prim_mas.push_back(temp);
}

int main(){
	std::string input="", input_file="";
	std::vector<long long> prim_mas;
	readPrimsNum(prim_mas);
	while(1){
		input="";
		while(input!="1" && input!="2" && input!="3" && input!="4" && input!="5"){
			std::cout<<"\n 1 - El-Gamala\n 2 - RSA\n 3 - GOST\n 4 - change input file\n 5 - exit\n --> ";
			std::cin>>input;
		}
		if(input=="5") break;
		else if(input=="1"){
			if(input_file==""){
				std::cout<<"No file.\n";
				continue;
			}
			setElGamal(prim_mas,input_file,"el_gam_podp.txt");
			checkElGamal(input_file,"el_gam_podp.txt");
		}
		else if(input=="2"){
			if(input_file==""){
				std::cout<<"No file.\n";
				continue;
			}
			setRSA(prim_mas,input_file,"rsa_podp.txt");
			std::string tttemp="";
			std::cin>>tttemp;
			checkRSA(input_file,"rsa_podp.txt");
		}
		else if(input=="3"){
			if(input_file==""){
				std::cout<<"No file.\n";
				continue;
			}
			setGOST(prim_mas,input_file,"gost_podp.txt");
			checkGOST(input_file,"gost_podp.txt");
		}
		else if(input=="4"){
			std::cout<<" --> ";
			std::cin>>input;
			if(!std::filesystem::exists(input)){
				std::cout<<" No file.\n";
				continue;
			}
			input_file=input;
		}
	}
}