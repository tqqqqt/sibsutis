#include <iostream>
#include <cmath>

const double pi=3.141592653589;

void printResult(int _size){
	double M=0.9*_size*std::log2(_size);
	std::cout<<"M = "<<M<<'\n';
	double L=0.9*_size*std::log2(_size);
	std::cout<<"L = "<<L<<'\n';
	double D=(std::pow(pi,2)*std::pow(_size,2))/6;
	std::cout<<"D = "<<D<<'\n';
	double sqrt_d=std::sqrt(D);
	std::cout<<"sqrt D = "<<sqrt_d<<'\n';
	double b=1/(2*std::log2(_size));
	std::cout<<"b = "<<b<<'\n';
}

int main(int argc, char** argv){
	std::cout<<"\nsize = 16\n";
	printResult(16);

	std::cout<<"\nsize = 32\n";
	printResult(32);

	std::cout<<"\nsize = 64\n";
	printResult(64);

	std::cout<<"\nsize = 128\n";
	printResult(128);

	return 0;
}