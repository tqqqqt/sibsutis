#include <iostream>
#include <cmath>

void calculateResult(int n_2, int n_2k_star, int n, int v){
	double k=(double)(n_2/(double)8);
	std::cout<<"k = "<<k<<'\n';
	double i=(double)(std::trunc((std::log(n_2))/(double)3)+1);
	std::cout<<"i = "<<i<<'\n';
	double K=1;
	for(int j=1;j<i;j++) K+=(double)(n_2/std::pow(8,j));
	std::cout<<"K = "<<K<<'\n';
    double n_2k=(double)(n_2k_star*std::log2(n_2k_star));
	double Nk=(double)(2*n_2k*std::log(n_2k));
	std::cout<<"Nk = "<<Nk<<'\n';
	double N=(double)(K*Nk);
	std::cout<<"N = "<<N<<'\n';
	double V=(double)(K*Nk*std::log(2*n_2k));
	std::cout<<"V = "<<V<<'\n';
	double P=(double)((3/(double)8)*N);
	std::cout<<"P = "<<P<<'\n';
	double Tk=(double)(P/(double)(n*v));
	std::cout<<"Tk = "<<Tk<<'\n';
	double B0=(double)(V/3000.0);
	std::cout<<"B0 = "<<B0<<'\n';
	double tn=(double)((0.5*Tk)/(double)(std::log(B0)));
	std::cout<<"tn = "<<tn<<'\n';
}

int main(){
	std::cout<<"n*2=4\n";
	calculateResult(4,8,5,20);
	std::cout<<'\n';

	std::cout<<"n*2=300\n";
	calculateResult(300,8,5,20);
	std::cout<<'\n';

	std::cout<<"n*2=400\n";
	calculateResult(400,8,5,20);
	std::cout<<'\n';

	std::cout<<"n*2=512\n";
	calculateResult(512,8,5,20);
	std::cout<<'\n';

	return 0;
}