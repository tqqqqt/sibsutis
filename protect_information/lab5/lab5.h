#ifndef LAB_CLASS
#define LAB_CLASS

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <set>

#include "MD5.h"
#include "numbermath.h"
#include "lab1lib.h"


class Bank{
public:
	std::string num_N, num_d;

	Bank(std::vector<long long>);
	void showKeys();
	std::vector<std::string> getVariant();
	std::string setPodpis(std::string);
	void vote(std::tuple<std::string,std::string,std::string>);
	void showResult();

private:
	std::string num_p, num_q, num_c;
	std::vector<std::string> variant;
	std::set<std::string> vote_mas;
	std::vector<std::vector<std::string>> votes;
};



/*-------------------------*/

Bank::Bank(std::vector<long long> prim_mas){
	num_p=std::to_string(prim_mas[rand()%(prim_mas.size()-1)+0]);
	num_q=std::to_string(prim_mas[rand()%(prim_mas.size()-1)+0]);
	num_N=MathMul(num_p,num_q);
	std::string num_f=MathMul(MathNeg(num_p,"1"),MathNeg(num_q,"1"));
	for(long long i=2;i<stoll(num_f);i++){
		if(std::get<0>(findNod(std::to_string(i),num_f))=="1"){
			num_d=std::to_string(i);
			break;
		}
	}
	std::tuple<std::string,std::string,std::string> temp=findNod(num_d,num_f);
	std::string x=std::get<1>(temp), y=std::get<2>(temp);
	if(x[0]=='-') x=MathNeg(num_f,x.substr(1));
	else x=MathModDiv(x,num_f);
	if(y[0]=='-') y=MathNeg(num_f,y.substr(1));
	else y=MathModDiv(y,num_f);
	num_c=x;
	temp=findNod(num_c,num_f);
	x=std::get<1>(temp), y=std::get<2>(temp);
	if(x[0]=='-') x=MathNeg(num_f,x.substr(1));
	else x=MathModDiv(x,num_f);
	num_d=x;

	variant={"Yes","No","Mb"};
}

void Bank::showKeys(){
	std::cout<<"Bank keys:\n";
	std::cout<<" P="<<num_p<<", Q="<<num_q<<", c="<<num_c<<'\n';
	std::cout<<" N="<<num_N<<", d="<<num_d<<"\n";
}

std::vector<std::string> Bank::getVariant(){
	return variant;
}

std::string Bank::setPodpis(std::string num){
	return findModule(num,std::stoll(num_c),num_N);
}

void Bank::vote(std::tuple<std::string,std::string,std::string> vote_list){
	std::vector<long long> h_temp, temp;
	std::string temp_h="";
	temp_h=md5(std::get<0>(vote_list));
	temp=HashToVector(temp_h);
	h_temp.insert(h_temp.end(),temp.begin(),temp.end());
	std::string num_fn="0";
	for(const long long& x:h_temp) num_fn=MathSum(num_fn,std::to_string(x));
	std::string temp_check=findModule(std::get<1>(vote_list),std::stoll(num_d),num_N);
	if(num_fn!=temp_check){
		std::cout<<"Vote list not valid. (sf^d%N!=f(n))\n";
		return;
	}
	if(vote_mas.count(std::get<0>(vote_list))!=0){
		std::cout<<"Vote list not valid. (list with n registr before this)\n";
		return;
	}
	vote_mas.insert(std::get<0>(vote_list));
	votes.push_back({std::get<0>(vote_list),std::get<2>(vote_list)});
	std::cout<<"Vote list accepted.\n";
}

void Bank::showResult(){
	std::cout<<"Bank result:\n";
	for(int i=0;i<votes.size();i++){
		std::cout<<i+1<<". "<<votes[i][0]<<" -> "<<votes[i][1]<<'\n';
	}
}

#endif