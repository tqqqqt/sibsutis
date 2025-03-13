#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <vector>

long double H(std::vector<long double> arr){
	double res=0;

	for(auto x:arr){
		if(x<=0) continue;
		res+=x*std::log2(x);
	}

	return res*-1;
}


void mainFunction(std::string file_name){
	std::ifstream file(file_name);

	// collect info
	std::unordered_map<char,int> symbols;
	std::unordered_map<std::string,int> pars, tripl;
	std::string p_buf="", t_buf="";
	char symb;
	while(file.get(symb)){
		if(p_buf.length()==2){
			pars[p_buf]+=1;
			p_buf=p_buf.substr(1);
		}
		if(t_buf.length()==3){
			tripl[t_buf]+=1;
			t_buf=t_buf.substr(1);
		}
		symbols[symb]+=1;

		p_buf+=symb;
		t_buf+=symb;
	}
	file.close();

	unsigned int symbol_count=0;
	for(auto x:symbols){
		symbol_count+=x.second;
	}
	unsigned int pars_count=symbol_count-1, tripl_count=symbol_count-2;


	std::vector<long double> ver;

	// h1
	for(auto x:symbols){
		ver.push_back(x.second/(long double)symbol_count);
	}
	std::cout<<"H1="<<H(ver)<<'\n';
	ver.clear();

	// h2
	for(auto x:pars){
		ver.push_back(x.second/(long double)pars_count);
	}
	std::cout<<"H2="<<(H(ver))/(long double)2<<'\n';
	ver.clear();

	// h3
	for(auto x:tripl){
		ver.push_back(x.second/(long double)tripl_count);
	}
	std::cout<<"H3="<<(H(ver))/(long double)3<<'\n';
}

int main(){
	// file 1
	std::cout<<"file_1.txt\n";
	mainFunction("file_1.txt");
	std::cout<<"\n";

	// file 2
	std::cout<<"file_2.txt\n";
	mainFunction("file_2.txt");
	std::cout<<"\n";

	// file 3
	std::cout<<"file_3.txt\n";
	mainFunction("file_3.txt");
	std::cout<<"\n";

	return 0;
}