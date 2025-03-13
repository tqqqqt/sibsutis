#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

struct t_info{
	char symb;
	double p;

	t_info(){ }
	t_info(char _s, double _p){
		symb=_s;
		p=_p;
	}
};

long double H(std::vector<long double> arr){
	double res=0;

	for(auto x:arr){
		if(x<=0) continue;
		res+=x*std::log2(x);
	}

	return res*-1;
}

int up(int n, double q, std::vector<t_info>& p){
	int j=0;
	for(int i=n-1;i>=1;--i){
		if(p[i-1].p>=q){
			j=i;
			break;
		}
		p[i]=p[i-1];
	}
	p[j].p=q;
	return j;
}

void down(int n, int j, std::vector<std::string>& c, std::vector<int>& l){
	std::string s;
	s=c[j];
	int temp_len=l[j];
	for(int i=j;i<=n-1;++i){
		c[i]=c[i+1];
		l[i]=l[i+1];
	}
	c[n-1]=s+'0';
	c[n]=s+'1';
	l[n-1]=temp_len+1;
	l[n]=temp_len+1;
}

void huffman(int n, std::vector<t_info> p, std::vector<std::string>& c, std::vector<int> l){
	if(n==1){
		c[0]="0";
		l[0]=1;
		c[1]="1";
		l[1]=1;
		return;
	}
	double q=p[n-1].p+p[n].p;
	int j=up(n,q,p);
	huffman(n-1,p,c,l);
	down(n,j,c,l);
}

void shenon(std::vector<t_info> p, std::vector<std::string>& c){
	std::vector<double> q, l;

	// collect p
	for(int i=0;i<p.size();++i){
		if(i<=0) q.push_back(0);
		else q.push_back(q.back()+p[i-1].p);
		l.push_back(std::ceil(-std::log2(p[i].p)));
	}

	// create codes
	for(int i=0;i<p.size();++i){
		c.push_back("");
		for(int j=0;j<l[i];++j){
			q[i]*=2;
			c.back()+='0'+std::trunc(q[i]);
			if(q[i]>1) q[i]-=1;
		}
	}
}

void writeCodeFile(std::string file_name_in, std::string file_name_out, std::unordered_map<char,std::string> code_map){
	std::ofstream file_out(file_name_out);
	std::ifstream file_in(file_name_in);
	char symb;
	while(file_in.get(symb)){
		file_out<<code_map[symb];
	}
	file_in.close();
	file_out.close();
}

void codeFiles(std::string file_name){
	std::ifstream file_in(file_name);

	// collect info
	std::unordered_map<char,int> symbols;
	char symb;
	while(file_in.get(symb)){
		symbols[symb]+=1;
	}
	file_in.close();

	// count symbols
	unsigned int symbol_count=0;
	for(auto x:symbols) symbol_count+=x.second;

	// collect in vector
	std::vector<t_info> temp;
	for(auto x:symbols){
		temp.push_back(t_info(x.first,x.second/(double)symbol_count));
	}
	std::sort(temp.begin(),temp.end(),[](const t_info& x, const t_info& y){ return x.p>y.p; });
	symbols.clear();

	// code map
	int siz=temp.size();
	std::unordered_map<char,std::string> code_map;
	std::vector<std::string> symb_code(siz,"");
	double L=0, H=0;

	// hafman
	huffman(siz-1,temp,symb_code,std::vector<int>(siz,0));
	
	for(int i=0;i<siz;++i){
		code_map[temp[i].symb]=symb_code[i];
		L+=symb_code[i].length()*temp[i].p;
		H+=temp[i].p*std::log2(temp[i].p);
	}
	H*=-1;
	std::cout<<" Huffman: L="<<L<<" H="<<H<<" r="<<(L-H)<<'\n';
	L=0;

	writeCodeFile(file_name,"hafman_"+file_name,code_map);

	code_map.clear();
	symb_code.clear();

	// shenon
	shenon(temp,symb_code);

	for(int i=0;i<siz;++i){
		code_map[temp[i].symb]=symb_code[i];
		L+=symb_code[i].length()*temp[i].p;
	}
	std::cout<<" Shenon: L="<<L<<" H="<<H<<" r="<<(L-H)<<'\n';

	writeCodeFile(file_name,"shenon_"+file_name,code_map);
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

	std::string file_name="file_";

	for(int i=1;i<4;++i){
		std::cout<<"Code file "<<i<<":\n";
		codeFiles(file_name+(char)('0'+i)+".txt");
		std::cout<<"Code complete\n";
	}
	std::cout<<'\n';

	file_name="hafman_file_";
	for(int i=1;i<4;++i){
		std::cout<<"Hafman file "<<i<<":\n";
		mainFunction(file_name+(char)('0'+i)+".txt");
		std::cout<<'\n';
	}
	std::cout<<'\n';

	file_name="shenon_file_";
	for(int i=1;i<4;++i){
		std::cout<<"Shenon file "<<i<<":\n";
		mainFunction(file_name+(char)('0'+i)+".txt");
		std::cout<<'\n';
	}


	return 0;
}