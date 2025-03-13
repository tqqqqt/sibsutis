#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>

const double char_p[3]={0.5, 0.2, 0.3};
const char* file_name="file_2.txt";

struct t_info{
	std::string symb;
	double p;

	t_info(){ }
	t_info(std::string _s, double _p){
		symb=_s;
		p=_p;
	}
};

int up(int size, double q, std::vector<t_info>& p){
	int j=0;
	for(int i=size-1;i>=1;--i){
		if(p[i-1].p>=q){
			j=i;
			break;
		}
		p[i]=p[i-1];
	}
	p[j].p=q;
	return j;
}

void down(int n, int index, std::vector<std::string>& code, std::vector<int>& len){
	std::string s;
	s=code[index];
	int temp_len=len[index];
	for(int i=index;i<=n-1;++i){
		code[i]=code[i+1];
		len[i]=len[i+1];
	}
	code[n-1]=s+'0';
	code[n]=s+'1';
	len[n-1]=temp_len+1;
	len[n]=temp_len+1;
}

void huffman(int n, std::vector<t_info> p, std::vector<std::string>& code, std::vector<int> len){
	if(n==1){
		code[0]="0";
		len[0]=1;
		code[1]="1";
		len[1]=1;
		return;
	}
	double q=p[n-1].p+p[n].p;
	int index=up(n,q,p);
	huffman(n-1,p,code,len);
	down(n,index,code,len);
}

void createBlock(std::string _str, std::unordered_map<std::string,double>& _arr, const int& _len){
	for(int i=_len-1;i>=0;--i){
		if(_str[i]>='C') continue;
		_str[i]++;
		_arr[_str]=1;
		createBlock(_str,_arr,_len);
		_str[i]--;
	}
}

void mainFunction(int _block_size){
	std::unordered_map<std::string,double> block_ver;

	// create and calculate block ver
	block_ver[std::string(_block_size,'A')]=1;
	createBlock(std::string(_block_size,'A'),block_ver,_block_size);
	for(auto& x:block_ver){
		for(int i=0;i<_block_size;++i){
			x.second*=char_p[x.first[i]-'A'];
		}
	}

	// collect info and crate code for block
	int siz=block_ver.size();
	std::vector<std::string> code(siz,"");
	std::vector<t_info> ver;
	for(auto x:block_ver) ver.push_back(t_info(x.first,x.second));
	block_ver.clear();
	std::sort(ver.begin(),ver.end(),[](const t_info& x, const t_info& y){ return x.p>y.p; });
	
	huffman(siz-1,ver,code,std::vector<int>(siz,0));

	// collect result and calculate metrix
	double L=0, H=0;
	std::unordered_map<std::string,std::string> block_code;
	for(int i=0;i<siz;++i){
		block_code[ver[i].symb]=code[i];
		L+=code[i].length()*ver[i].p;
		H+=ver[i].p*std::log2(ver[i].p);
	}
	H*=-1;

	std::cout<<" L="<<L<<", H="<<H<<", r="<<(L-H)<<'\n';

	// code file
	std::ifstream file_in(file_name);
	std::ofstream file_out("block_"+std::to_string(_block_size)+"_file_2.txt");
	std::string temp="";
	char symb=' ';
	while(file_in.get(symb)){
		temp+=symb;
		if(temp.length()==_block_size){
			file_out<<block_code[temp];
			temp.clear();
		}
	}
	file_in.close();
	file_out.close();
	std::cout<<" Code file complete.\n";
}

int main(){
	for(int i=1;i<5;++i){
		std::cout<<"Block size="<<i<<'\n';
		mainFunction(i);
	}
	
	return 0;
}