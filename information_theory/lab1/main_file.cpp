#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

void genF1(){
	std::ofstream file_out("file_1.txt");

	for(int i=0;i<10000;++i){
		file_out<<static_cast<char>('A'+rand()%3);
	}

	file_out.close();
	std::cout<<"First file complete.\n";
}

void genF2(){
	std::vector<double> prob{0.5,0.2,0.3};
	std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> distribution(prob.begin(),prob.end());

    std::ofstream file_out("file_2.txt");
    for(int i=0;i<10000;++i){
    	int res=distribution(gen);
    	file_out<<static_cast<char>('A'+res);
    }

    file_out.close();
    std::cout<<"Second file complete.\n";
}

int main(){
	// first file
	genF1();

	// second file
	genF2();

	return 0;
}