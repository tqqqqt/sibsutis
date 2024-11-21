#include <vector>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char *argv[]){
	if(argc<2){
		std::cout<<"Error argum.\n";
		return 0;
	}
	std::vector<long long> ttemp;
	int num=std::stoll(argv[1]);
	std::ofstream file("prim2.txt");
	std::vector<int> temp(num+1,1);
	for(long long i=2;i<=num;i++){
		if(!temp[i]) continue;
		if(i>=pow(10,6)) ttemp.push_back(i);
		for(long long j=2;(i*j)<=num;j++) temp[i*j]=0;
	}
    int k=0;
	for(auto x:ttemp){
		file<<x<<" ";
		k++;
		if(k==20){
			k=0;
			file<<'\n';
		}
	}
	return 0;
}