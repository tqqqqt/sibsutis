#include "lib.h"

std::string findModule(std::string num1, long long num_stepen, std::string num2){
	long long n_step=log2(num_stepen)+1, k=0;
	std::string temp_calc="0", back_calc="0";
	std::string result="";
	while(num_stepen && n_step--){
		if(k++==0) temp_calc=num1;
		else temp_calc=MathModDiv(MathMul(MathModDiv(back_calc,num2),MathModDiv(back_calc,num2)),num2);
		if(num_stepen&1==1){
			if(result=="") result=temp_calc;
			else result=MathMul(result,temp_calc);
		}
		back_calc=temp_calc;
		temp_calc="0";
		num_stepen=num_stepen>>1;
	}
	return MathModDiv(result,num2);
}

std::string findNod(std::string num1, std::string num2){
	std::vector<std::string> u={num1,"1","0"}, v={num2,"0","1"}, temp={"0","0","0"};
	std::string q="0", temp_math="";
	while(v[0]!="0"){
		q=MathDivOld(u[0],v[0]);
		temp[0]=MathModDiv(u[0],v[0]);
		temp[1]=MathNeg(u[1],MathMul(q,v[1]));
		temp[2]=MathNeg(u[2],MathMul(q,v[2]));
		u=v;
		v=temp;
	}
	std::cout<<"\n x="<<u[1]<<"\n y="<<u[2]<<"\n res=";
	return u[0];
}

void twoKeys(long long p, long long g){
	srand(time(nullptr));
	long long x_a=rand()%RAND_MAX+1000000000, x_b=rand()%RAND_MAX+1000000000; //close key
	std::string y_a=findModule(std::to_string(g),x_a,std::to_string(p)), y_b=findModule(std::to_string(g),x_b,std::to_string(p)); //open key
	std::cout<<"player A -> close key = "<<x_a<<", open key = "<<y_a<<"\n";
	std::cout<<"player B -> close key = "<<x_b<<", open key = "<<y_b<<"\n";
	std::string z_ab=findModule(y_b,x_a,std::to_string(p)), z_ba=findModule(y_a,x_b,std::to_string(p)); //connect key
	std::cout<<" Z_a-b = "<<z_ab<<", Z_b-a = "<<z_ba<<"\n";
}

void findKey(std::string num1, std::string num3, std::string module_res){
	std::string m="0", k="0";
	k=m=std::to_string((int)(std::floor(std::sqrt(stoll(num3))))+1);
	std::vector<std::tuple<std::string,int,int>> vec={{MathModDiv(module_res,num3),1,0}};
	//std::vector<std::string> vec2, vec1={MathModDiv(module_res,num3)};
	std::string temp_m="1", r_m=MathNeg(m,"1"), temp_k="1";
	int kk=1;
	while(MaxNumber(temp_m,r_m)!=-1){
		//vec1.push_back(MathModDiv(MathMul(findModule(num1,stoll(temp_m),num3),module_res),num3));
		vec.push_back(std::make_tuple(MathModDiv(MathMul(findModule(num1,stoll(temp_m),num3),module_res),num3),1,kk));
		temp_m=MathSum(temp_m,"1");
		kk++;
	}
	kk=0;
	while(MaxNumber(temp_k,k)!=-1){
		//vec2.push_back(findModule(num1,stoll(MathMul(m,temp_k)),num3));
		vec.push_back(std::make_tuple(findModule(num1,stoll(MathMul(m,temp_k)),num3),2,kk));
		temp_k=MathSum(temp_k,"1");
		kk++;
	}
	/*for(int i=0;i<vec1.size();i++){
		std::string temp="";
		for(int j=0;j<vec2.size();j++){
			if(vec1[i]==vec2[j]){
				temp=MathNeg(MathMul(std::to_string(i),m),std::to_string(j+1));
				if(temp[0]=='-') continue;
				if(findModule(num1,stoll(temp),num3)==module_res) std::cout<<temp<<", ";
			}
		}
	}*/
	std::sort(vec.begin(),vec.end(),[](const std::tuple<std::string,int,int>& x, const std::tuple<std::string,int,int>& y){ return MaxNumber(std::get<0>(x),std::get<0>(y))==1;});
	int temp_point=0;
	for(int i=1;i<vec.size();i++){
		if(std::get<0>(vec[i])!=std::get<0>(vec[temp_point])){
			temp_point=i;
			continue;
		}
		if(std::get<0>(vec[temp_point])==std::get<0>(vec[i]) && std::get<1>(vec[temp_point])!=std::get<1>(vec[i])){
			int temp_i=0, temp_j=0;
			temp_i=std::get<1>(vec[i])==1?std::get<2>(vec[i]):std::get<2>(vec[temp_point]);
			temp_j=std::get<1>(vec[i])==2?std::get<2>(vec[i]):std::get<2>(vec[temp_point]);
			std::string temp=MathNeg(MathMul(std::to_string(temp_i),m),std::to_string(temp_j+1));
			if(temp[0]=='-') continue;
			if(findModule(num1,stoll(temp),num3)==module_res) std::cout<<temp<<", ";
		}
	}
}