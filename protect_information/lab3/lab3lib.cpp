#include "lab3lib.h"
#include "MD5.h"

std::string gamal_y="";
std::string gamal_g="";
std::string gamal_p="";

std::string rsa_d="";
std::string rsa_n="";

std::string gost_q="";
std::string gost_p="";
std::string gost_y="";
std::string gost_a="";

void setElGamal(std::vector<long long> prim_mas, std::string file_name, std::string file_name_out){
	srand(time(nullptr));
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
	long long x=rand()%(p-1)+1;
	std::string y=findModule(g,x,std::to_string(p));
	gamal_y=y;
	gamal_g=g;
	gamal_p=std::to_string(p);
	std::vector<long long> h_temp, temp;
	std::ifstream file_in(file_name,std::ifstream::binary);
	std::string line="", temp_h="";
	while(std::getline(file_in,line)){
		temp_h=md5(line);
		temp=HashToVector(temp_h);
		h_temp.insert(h_temp.end(),temp.begin(),temp.end());
	}
	file_in.close();
	std::string h="0";
	for(const long long& x:h_temp) h=MathSum(h,std::to_string(x));
	long long k=1;
	for(long long i=2;i<(p-1);i++){
		if(std::get<0>(findNod(std::to_string(i),std::to_string(p-1)))=="1"){
			k=i;
			break;
		}
	}
	std::string r=findModule(g,k,std::to_string(p));
	std::string ttemp_u=MathNeg(h,MathMul(std::to_string(x),r));
	std::string u="", minus_k="";//=ttemp_u[0]=='-'?MathNeg(std::to_string(p-1),ttemp_u.substr(1)):MathModDiv(ttemp_u,std::to_string(p-1)), minus_k="";
	if(ttemp_u[0]!='-') u=MathModDiv(ttemp_u,std::to_string(p-1));
	else if(MaxNumber(ttemp_u.substr(1),std::to_string(p-1))==1) u=MathNeg(std::to_string(p-1),ttemp_u.substr(1));
	else{
		std::string tttemp_u=MathNeg(ttemp_u.substr(1),MathMul(MathDivOld(ttemp_u.substr(1),std::to_string(p-1)),std::to_string(p-1)));
		u=MathNeg(std::to_string(p-1),tttemp_u);
	}
	std::tuple<std::string,std::string,std::string> ttemp=findNod(std::to_string(k),std::to_string(p-1));
	std::string xx=std::get<1>(ttemp), yy=std::get<2>(ttemp);
	if(xx[0]=='-') xx=MathNeg(std::to_string(p-1),xx.substr(1));
	else xx=MathModDiv(xx,std::to_string(p-1));
	if(yy[0]=='-') yy=MathNeg(std::to_string(p-1),yy.substr(1));
	else yy=MathModDiv(yy,std::to_string(p-1));
	minus_k=xx;
	//if(findModule(MathMul(std::to_string(k),xx),1,std::to_string(p-1))=="1") minus_k=xx;
	//else if(findModule(MathMul(std::to_string(k),yy),1,std::to_string(p-1))=="1") minus_k=yy;
	std::string s=MathModDiv(MathMul(minus_k,u),std::to_string(p-1));
	std::ofstream file_out(file_name_out);
	file_out<<r<<" "<<s;
	file_out.close();
	std::cout<<"-------\n"<<" y="<<y<<", g="<<g<<", p="<<p<<", r="<<r<<", s="<<s<<"\n------\n";
}

void checkElGamal(std::string file_text, std::string file_name){
	std::vector<long long> h_temp;
	std::vector<long long> temp;
	std::ifstream file_in(file_text,std::ifstream::binary);
	std::string line="", temp_h="";
	while(std::getline(file_in,line)){
		temp_h=md5(line);
		temp=HashToVector(temp_h);
		h_temp.insert(h_temp.end(),temp.begin(),temp.end());
	}
	file_in.close();
	std::string h="0";
	for(const long long& x:h_temp) h=MathSum(h,std::to_string(x));
	std::ifstream file_enc(file_name);
	std::string r="", s="";
	file_enc>>r>>s;
	file_enc.close();
	std::cout<<" h = "<<h<<", r = "<<r<<", s = "<<s<<"\n ------ \n";
	std::string left_side=MathModDiv(MathMul(findModule(gamal_y,stoll(r),gamal_p),findModule(r,stoll(s),gamal_p)),gamal_p);
	std::string right_side=findModule(gamal_g,stoll(h),gamal_p);
	std::cout<<left_side<<" == "<<right_side<<"\n";
	if(MaxNumber(left_side,right_side)==0) std::cout<<"(left_side == right_side) -> true\n";
	else std::cout<<"(left_side == right_side) -> false\n-------\n";
}

void setRSA(std::vector<long long> prim_mas, std::string file_input, std::string file_name_out){
	srand(time(nullptr));
	std::vector<long long> h_temp;
	std::vector<long long> temp;
	std::ifstream file_in(file_input,std::ifstream::binary);
	std::string line="", temp_h="";
	while(std::getline(file_in,line)){
		temp_h=md5(line);
		temp=HashToVector(temp_h);
		h_temp.insert(h_temp.end(),temp.begin(),temp.end());
	}
	file_in.close();
	std::string y="0";
	for(const long long& x:h_temp) y=MathSum(y,std::to_string(x));
	int n_a_1=rand()%(prim_mas.size()-1)+0, n_a_2=rand()%(prim_mas.size()-1)+0;
	std::string n_a=MathMul(std::to_string(prim_mas[n_a_1]),std::to_string(prim_mas[n_a_2]));
	std::string f_a=MathMul(MathNeg(std::to_string(prim_mas[n_a_1]),"1"),MathNeg(std::to_string(prim_mas[n_a_2]),"1")), d_a="";
	for(long long i=2;i<stoll(f_a);i++){
		if(std::get<0>(findNod(std::to_string(i),f_a))=="1"){
			d_a=std::to_string(i);
			break;
		}
	}
	rsa_d=d_a;
	rsa_n=n_a;
	std::string c_a="";
	std::tuple<std::string,std::string,std::string> ttemp=findNod(d_a,f_a);
	std::string xx=std::get<1>(ttemp), yy=std::get<2>(ttemp);
	if(xx[0]=='-') xx=MathNeg(f_a,xx.substr(1));
	else xx=MathModDiv(xx,f_a);
	if(yy[0]=='-') yy=MathNeg(f_a,yy.substr(1));
	else yy=MathModDiv(yy,f_a);
	c_a=xx;
	//if(findModule(MathMul(d_a,xx),1,f_a)=="1") c_a=xx;
	//else if(findModule(MathMul(d_a,yy),1,f_a)=="1") c_a=yy;
	std::string s=findModule(y,stoll(c_a),n_a);
	std::ofstream file_out(file_name_out);
	file_out<<s;
	file_out.close();
	std::cout<<"-------\n d="<<d_a<<", n="<<n_a<<", s="<<s<<"\n--------------\n";
}

void checkRSA(std::string file_text, std::string file_name){
	std::ifstream file_in(file_text,std::ifstream::binary);
	std::string line="", temp_h="";
	std::vector<long long> temp, h_temp;
	while(std::getline(file_in,line)){
		temp_h=md5(line);
		temp=HashToVector(temp_h);
		h_temp.insert(h_temp.end(),temp.begin(),temp.end());
	}
	file_in.close();
	std::ifstream file_pod(file_name);
	std::string s="";
	file_pod>>s;
	file_pod.close();
	std::string h="0";
	for(const long long& x:h_temp) h=MathSum(h,std::to_string(x));
	std::string w=findModule(s,stoll(rsa_d),rsa_n);
	std::cout<<w<<" == "<<h<<"\n";
	if(w==h) std::cout<<"("<<w<<"=="<<h<<") -> true\n";
	else std::cout<<"("<<w<<"=="<<h<<") -> false\n";
}

void setGOST(std::vector<long long> prim_mas, std::string file_text, std::string file_name_out){
	srand(time(nullptr));
	std::string q=std::to_string(rand()%ULLONG_MAX+10000);
	while(!checkPrime(q)) q=std::to_string(rand()%ULLONG_MAX+10000);
	std::string b="6", p=MathSum(MathMul(b,q),"1");
	while(!checkPrime(p)){
		b=std::to_string(rand()%ULLONG_MAX+10000);
		p=MathSum(MathMul(b,q),"1");
	}
	std::string g=std::to_string(rand()%(stoll(p)-1)+1), stepen=MathDivOld(MathNeg(p,"1"),q), a=findModule(g,stoll(stepen),p);
	while(MaxNumber(a,"1")!=-1){
		g=std::to_string(rand()%(stoll(p)-1)+1);
		//a=findModule(g,stoll(stepen),p);
		a=findModule(g,stoll(b),p);
	}
	std::string x=std::to_string(rand()%(stoll(q)-1)+0);
	std::string y=findModule(a,stoll(x),p);
	std::ifstream file_in(file_text,std::ifstream::binary);
	std::vector<long long> temp_h, temp;
	std::string hash_temp="", line="";
	while(std::getline(file_in,line)){
		hash_temp=md5(line);
		temp=HashToVector(hash_temp);
		temp_h.insert(temp_h.end(),temp.begin(),temp.end());
	}
	file_in.close();
	gost_q=q;
	gost_p=p;
	gost_y=y;
	gost_a=a;
	std::string h="0";
	for(const long long& x:temp_h) h=MathSum(h,std::to_string(x));
	std::string r="", s="";
	long long k=0;
	while(1){
		k=rand()%stoll(q)+0;
		r=MathModDiv(findModule(a,k,p),q);
		if(r=="0"){
			std::cout<<"no r\n";
			continue;
		}
		s=MathModDiv(MathSum(MathMul(std::to_string(k),h),MathMul(x,r)),q);
		if(s=="0"){
			std::cout<<"no s |\n";
			continue;
		}
		break;
	}
	std::cout<<"------------\n q="<<q<<", p="<<p<<", a="<<a<<", y="<<y<<", r="<<r<<", s="<<s<<"\n--------";
	std::ofstream file_out(file_name_out);
	file_out<<r<<" "<<s;
	file_out.close();
}

void checkGOST(std::string file_name_text, std::string file_podp){
	std::ifstream file_text(file_name_text,std::ifstream::binary);
	std::vector<long long> temp_h, temp;
	std::string hash_temp="", line="";
	while(std::getline(file_text,line)){
		hash_temp=md5(line);
		temp=HashToVector(hash_temp);
		temp_h.insert(temp_h.end(),temp.begin(),temp.end());
	}
	file_text.close();
	std::string h="0";
	for(const long long& x:temp_h) h=MathSum(h,std::to_string(x));
	std::ifstream file_in(file_podp);
	std::string r="", s="";
	file_in>>r>>s;
	if(stoll(r)<0 || stoll(r)>stoll(gost_q) || stoll(s)<0 || stoll(s)>stoll(gost_q)){
		std::cout<<"Fail: 0<r<q && 0<s<q\n";
		return;
	}
	std::string u_1="", u_2="", minus_h="";
	std::tuple<std::string,std::string,std::string> ttemp=findNod(h,gost_q);
	std::string xx=std::get<1>(ttemp), yy=std::get<2>(ttemp);
	if(xx[0]=='-') xx=MathNeg(gost_q,xx.substr(1));
	else minus_h=MathModDiv(xx,gost_q);
	if(yy[0]=='-') yy=MathNeg(gost_q,yy.substr(1));
	else minus_h=MathModDiv(yy,gost_q);
	minus_h=xx;
	//if(findModule(MathMul(gost_q,xx),1,gost_q)=="1") minus_h=xx;
	//else if(findModule(MathMul(gost_q,yy),1,gost_q)=="1") minus_h=yy;
	u_1=MathModDiv(MathMul(s,minus_h),gost_q);
	u_2=MathMul("-"+r,minus_h);
	if(MaxNumber(u_2.substr(1),gost_q)==1) u_2=MathNeg(gost_q,u_2.substr(1));
	else{
		std::string ttemp_u=MathNeg(u_2.substr(1),MathMul(MathDivOld(u_2.substr(1),gost_q),gost_q));
		u_2=MathNeg(gost_q,ttemp_u);
	}
	std::string v=MathModDiv(MathModDiv(MathMul(findModule(gost_a,stoll(u_1),gost_p),findModule(gost_y,stoll(u_2),gost_p)),gost_p),gost_q);
	std::cout<<"\n"<<v<<" == "<<r<<"\n";
	if(v==r) std::cout<<"("<<v<<"=="<<r<<") -> true\n";
	else std::cout<<"("<<v<<"=="<<r<<") -> false\n";
}