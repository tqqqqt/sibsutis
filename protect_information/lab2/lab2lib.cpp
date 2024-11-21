#include "lab2lib.h"

std::string save_d_b="";
std::string save_el_c_b="", save_el_d_b="";
std::vector<int> save_keys;
std::string save_rsa_c_b="", save_rsa_n_b="";

void shamiraEnc(long long num_p, std::string file_name){
	std::string c_a="", d_a="";
	for(long long i=3;i<num_p-2;i++){
		if(c_a=="" && std::get<0>(findNod(std::to_string(i),std::to_string(num_p-1)))=="1"){
			c_a=std::to_string(i);
			break;
		}
	}
	std::tuple<std::string,std::string,std::string> temp=findNod(std::to_string(num_p-1),c_a);
	std::string x=std::get<1>(temp), y=std::get<2>(temp);
	if(x[0]=='-') x=MathNeg(std::to_string(num_p-1),x.substr(1));
	else x=MathModDiv(x,std::to_string(num_p-1));
	if(y[0]=='-') y=MathNeg(std::to_string(num_p-1),y.substr(1));
	else y=MathModDiv(y,std::to_string(num_p-1));
	if(findModule(MathMul(c_a,x),1,std::to_string(num_p-1))=="1") d_a=x;
	else if(findModule(MathMul(c_a,y),1,std::to_string(num_p-1))=="1") d_a=y;

	std::string c_b="", d_b="";
	for(long long i=3;i<num_p-2;i++){
		if(c_b=="" && std::to_string(i)!=c_a && std::to_string(i)!=d_a && std::get<0>(findNod(std::to_string(i),std::to_string(num_p-1)))=="1"){
			c_b=std::to_string(i);
			break;
		}
	}
	temp=findNod(std::to_string(num_p-1),c_b);
	x=std::get<1>(temp), y=std::get<2>(temp);
	if(x[0]=='-') x=MathNeg(std::to_string(num_p-1),x.substr(1));
	else x=MathModDiv(x,std::to_string(num_p-1));
	if(y[0]=='-') y=MathNeg(std::to_string(num_p-1),y.substr(1));
	else y=MathModDiv(y,std::to_string(num_p-1));
	if(findModule(MathMul(c_b,x),1,std::to_string(num_p-1))=="1") d_b=x;
	else if(findModule(MathMul(c_b,y),1,std::to_string(num_p-1))=="1") d_b=y;

	std::cout<<"p="<<num_p<<", c_a="<<c_a<<", d_a="<<d_a<<", c_b="<<c_b<<", d_b="<<d_b<<"\n";
	std::string x_1="", x_2="", x_3="";
	std::vector<std::string> result;
	std::vector<char> messege;
	char t;

	save_d_b=d_b;
	std::ifstream file_in(file_name,std::ifstream::binary);
	while(file_in.read((char*)&t,sizeof(t))) messege.push_back(t);
	file_in.close();
	std::cout<<messege.size()<<"\n";
	for(auto x:messege){
		x_1=findModule(std::to_string((int)x),std::stoll(c_a),std::to_string(num_p));
		x_2=findModule(x_1,std::stoll(c_b),std::to_string(num_p));
		x_3=findModule(x_2,std::stoll(d_a),std::to_string(num_p));
		result.push_back(x_3);
	}
	std::ofstream file_enc("shamira_enc.txt");
	for(auto x:result) file_enc<<x<<" ";
	file_enc.close();
}

void shamiraDec(long long num_p, std::string file_name, std::string file_out_name){
	std::vector<std::string> mes;
	std::string temp;
	std::ifstream file_enc(file_name,std::ofstream::binary);
	while(file_enc>>temp) mes.push_back(temp);
	std::string x_4="";
	std::vector<char> result;
	for(auto x:mes){
		x_4=findModule(x,stoll(save_d_b),std::to_string(num_p));
		result.push_back(stoi(x_4));
	}
	std::ofstream file_dec(file_out_name);
	for(auto x:result) file_dec<<(char)x;
	file_dec.close();
}

void elGamalEnc(std::string num_p, std::string num_g, std::string file_name){
	std::string c_a=std::to_string(rand()%1000000+10), c_b=std::to_string(rand()%1000000+10);
	std::string d_a=findModule(num_g,stoll(c_a),num_p), d_b=findModule(num_g,stoll(c_b),num_p);
	std::cout<<"num_p="<<num_p<<", num_g="<<num_g<<", c_a="<<c_a<<", c_b="<<c_b<<", d_a="<<d_a<<", d_b="<<d_b<<'\n';
	save_el_c_b=c_b;
	save_el_d_b=d_b;
	std::ifstream file_in(file_name,std::iostream::binary);
	std::vector<char> message;
	char temp;
	while(file_in.read((char*)&temp,sizeof(temp))) message.push_back(temp);
	file_in.close();
	std::string r="", e="";
	long long k=0;
	std::ofstream file_enc("el_gamal_enc.txt");
	for(auto m:message){
		k=rand()%1000000+10;
		r=findModule(num_g,k,num_p);
		e=MathModDiv(MathMul(std::to_string((int)m),findModule(d_b,k,num_p)),num_p);
		file_enc<<r<<" "<<e<<'\n';
	}
	file_enc.close();
}

void elGamalDec(std::string num_p, std::string num_g, std::string file_name, std::string file_out_name){
	std::vector<std::string> mes;
	std::ifstream file_enc(file_name);
	std::string line="", cell="";
	while(file_enc>>line) mes.push_back(line);
	file_enc.close();
	std::ofstream file_dec(file_out_name,std::ofstream::binary);
	std::string m="", step=MathNeg(MathNeg(num_p,"1"),save_el_c_b);
	std::vector<char> result;
	for(int i=1;i<mes.size();i+=2){
		m=MathModDiv(MathMul(mes[i],findModule(mes[i-1],stoll(step),num_p)),num_p);
		result.push_back(stoll(m));
	}
	for(auto x:result) file_dec<<x;
	file_dec.close();
}

void vernamEnc(std::string file_name){
	std::ifstream file_in(file_name,std::ifstream::binary);
	std::vector<char> mes;
	char temp;
	while(file_in.read((char*)&temp,sizeof(temp))) mes.push_back(temp);
	file_in.close();
	//for(const char& x:mes) 
	for(auto x:mes)	save_keys.push_back(rand()%255+0);
	std::ofstream file_out("vernam_enc.txt");
	for(int i=0;i<mes.size();i++){
		int new_m=mes[i]^save_keys[i];
		file_out<<new_m<<" ";
	}
	file_out.close();
}

void vernamDec(std::string file_name, std::string file_out_name){
	std::ifstream file_enc(file_name);
	std::vector<long long> mes;
	int temp=0;
	while(file_enc>>temp) mes.push_back(temp);
	file_enc.close();
	std::ofstream file_dec(file_out_name,std::ifstream::binary);
	for(int i=0;i<mes.size();i++){
		int dec_m=mes[i]^save_keys[i];
		file_dec<<(char)dec_m;
	}
	file_dec.close();
}

void rsaEnc(std::string file_name, std::vector<long long> prim_mas){
	std::ifstream file_in(file_name,std::ifstream::binary);
	std::vector<char> mes;
	char ttemp;
	while(file_in.read((char*)&ttemp,sizeof(ttemp))) mes.push_back(ttemp);
	file_in.close();
	int n_a_1=rand()%(prim_mas.size()-1)+0, n_a_2=rand()%(prim_mas.size()-1)+0, n_b_1=rand()%(prim_mas.size()-1)+0, n_b_2=rand()%(prim_mas.size()-1)+0;
	std::string n_a=MathMul(std::to_string(prim_mas[n_a_1]),std::to_string(prim_mas[n_a_2]));
	std::string n_b=MathMul(std::to_string(prim_mas[n_b_1]),std::to_string(prim_mas[n_b_2]));
	std::string f_a=MathMul(MathNeg(std::to_string(prim_mas[n_a_1]),"1"),MathNeg(std::to_string(prim_mas[n_a_2]),"1"));
	std::string f_b=MathMul(MathNeg(std::to_string(prim_mas[n_b_1]),"1"),MathNeg(std::to_string(prim_mas[n_b_2]),"1"));
	std::string d_a="", d_b="";
	for(long long i=2;i<stoll(f_a);i++){
		if(std::get<0>(findNod(std::to_string(i),f_a))=="1"){
			d_a=std::to_string(i);
			break;
		}
	}
	for(long long i=2;i<stoll(f_b);i++){
		if(std::get<0>(findNod(std::to_string(i),f_b))=="1"){
			d_b=std::to_string(i);
			break;
		}
	}
	std::string c_a="", c_b="";
	std::tuple<std::string,std::string,std::string> temp=findNod(d_a,f_a);
	std::string x=std::get<1>(temp), y=std::get<2>(temp);
	if(x[0]=='-') x=MathNeg(f_a,x.substr(1));
	else x=MathModDiv(x,f_a);
	if(y[0]=='-') y=MathNeg(f_a,y.substr(1));
	else y=MathModDiv(y,f_a);
	if(findModule(MathMul(d_a,x),1,f_a)=="1") c_a=x;
	else if(findModule(MathMul(d_a,y),1,f_a)=="1") c_a=y;
	temp=findNod(d_b,f_b);
	x=std::get<1>(temp);
	y=std::get<2>(temp);
	if(x[0]=='-') x=MathNeg(f_b,x.substr(1));
	else x=MathModDiv(x,f_b);
	if(y[0]=='-') y=MathNeg(f_b,y.substr(1));
	else y=MathModDiv(y,f_b);
	if(findModule(MathMul(d_b,x),1,f_b)=="1") c_b=x;
	else if(findModule(MathMul(d_b,y),1,f_b)=="1") c_b=y;
	save_rsa_c_b=c_b;
	save_rsa_n_b=n_b;
	std::cout<<"d_a="<<d_a<<", d_b="<<d_b<<", c_a="<<c_a<<", c_b="<<c_b<<"\n";

	std::ofstream file_enc("rsa_enc.txt");
	for(auto x:mes){
		std::string e=findModule(std::to_string((int)x),stoll(d_b),n_b);
		file_enc<<e<<" ";
	}
	file_enc.close();
}

void rsaDec(std::string file_name, std::string file_out_name){
	std::ifstream file_in(file_name);
	std::vector<std::string> mes;
	std::string temp="";
	while(file_in>>temp) mes.push_back(temp);
	file_in.close();
	std::ofstream file_out(file_out_name,std::ofstream::binary);
	for(auto x:mes){
		std::string m=findModule(x,stoll(save_rsa_c_b),save_rsa_n_b);
		file_out<<(char)stoi(m);
	}
	file_out.close();
}