#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

#include "lab2lib.h"

void readPrimNums(std::vector<long long>& prim_vector){
	std::ifstream file("prim2.txt");
	long long temp_num=0;
	while(file>>temp_num) prim_vector.push_back(temp_num);
}

int main(){
	srand(time(nullptr));
	std::vector<long long> prim_nums;
	readPrimNums(prim_nums);
	std::string input="";
	while(1){
		input="";
		while(input!="1" && input!="2" && input!="3" && input!="4" && input!="5"){
			std::cout<<" 1 - Shamira\n 2 - El-Gamala\n 3 - Vernama\n 4 - RSA\n 5 - exit\n -->";
			std::cin>>input;
		}
		if(input=="5") break;
		if(input=="1"){
			int num_prim=rand()%(prim_nums.size()-1)+0;
			//shamiraEnc(prim_nums[num_prim],"input.txt");
			//shamiraDec(prim_nums[num_prim],"shamira_enc.txt", "shamira_dec.txt");
			shamiraEnc(prim_nums[num_prim],"galac.jpg");
			shamiraDec(prim_nums[num_prim],"shamira_enc.txt", "shamira_dec.jpg");
		}
		else if(input=="2"){
			long long p=0, q=0;
			for(int i=prim_nums.size()-1;i>=0;i--){
				bool flg=false;
				for(int j=i-1;j>=0;j--){
					if(prim_nums[i]==(2*prim_nums[j])+1){
						flg=true;
						p=prim_nums[i];
						q=prim_nums[j];
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
			//elGamalEnc(std::to_string(p),g,"input.txt");
			//elGamalDec(std::to_string(p),g,"el_gamal_enc.txt","el_gamal_dec.txt");
			elGamalEnc(std::to_string(p),g,"galac.jpg");
			elGamalDec(std::to_string(p),g,"el_gamal_enc.txt","el_gamal_dec.jpg");
		}
		else if(input=="3"){
			// vernamEnc("input.txt");
			// vernamDec("vernam_enc.txt","vernam_dec.txt");
			vernamEnc("ava.jpg");
			vernamDec("vernam_enc.txt","vernam_dec.jpg");
		}
		else if(input=="4"){
			//rsaEnc("input.txt",prim_nums);
		//	rsaDec("rsa_enc.txt","rsa_dec.txt");
			rsaEnc("galac.jpg",prim_nums);
			rsaDec("rsa_enc.txt","rsa_dec.jpg");
		}
	}
	return 0;
}