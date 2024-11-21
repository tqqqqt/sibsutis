#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <utility>

#include "MD5.h"
#include "numbermath.h"
#include "lab1lib.h"
#include "lab5.h"

void readPrim(std::vector<long long>& mas){
	std::ifstream file_in("prim2.txt");
	long long temp;
	while(file_in>>temp) mas.push_back(temp);
}

std::string generateFn(std::string name){
	std::vector<long long> h_temp, temp;
	std::string temp_h="";
	temp_h=md5(name);
	temp=HashToVector(temp_h);
	h_temp.insert(h_temp.end(),temp.begin(),temp.end());
	std::string result="0";
	for(const long long& x:h_temp) result=MathSum(result,std::to_string(x));
	return result;
}

int main(){
	srand(time(nullptr));
	std::vector<long long> prim_mas;
	readPrim(prim_mas);
	Bank* my_bank=new Bank(prim_mas);
	my_bank->showKeys();
	std::vector<std::string> variant=my_bank->getVariant();
	int n=0;
	std::cout<<"\nVote start.\n----------\n";
	for(int i=0;i<5;i++){
		if(i!=3) n=rand()%(std::stoll(my_bank->num_N))+2;
		std::string num_fn=generateFn(std::to_string(n));
		std::string r="0";
		for(int i=2;i<n;i++){
			if(std::get<0>(findNod(std::to_string(i),std::to_string(n)))=="1"){
				r=std::to_string(i);
				break;
			}
		}
		std::string temp_n=MathModDiv(MathMul(num_fn,findModule(r,std::stoll(my_bank->num_d),my_bank->num_N)),my_bank->num_N);
		std::string s_temp=my_bank->setPodpis(temp_n);
		std::tuple<std::string,std::string,std::string> temp=findNod(r,my_bank->num_N);
		std::string x=std::get<1>(temp), y=std::get<2>(temp), minus_r="";
		if(x[0]=='-') x=MathNeg(my_bank->num_N,x.substr(1));
		else x=MathModDiv(x,my_bank->num_N);
		if(y[0]=='-') y=MathNeg(my_bank->num_N,y.substr(1));
		else y=MathModDiv(y,my_bank->num_N);
		minus_r=x;
		std::string s=MathModDiv(MathMul(s_temp,minus_r),my_bank->num_N);
		std::tuple<std::string,std::string,std::string> vote_list=make_tuple(std::to_string(n),s,variant[rand()%3+0]);
		my_bank->vote(vote_list);
	}
	std::cout<<"----------\nVote end. Wait bank...\n \n";
	my_bank->showResult();
	delete my_bank;
	return 0;
}