#include <iostream>
#include <cmath>
#include <ctime>


int main(int argc, char** argv){
	if(argc!=3){
		std::cout<<"No argums\n";
		return 4;
	}


	// take argums
	int n=0, m=0;
	try{
		n=std::stoi(argv[1]);
		m=std::stoi(argv[2]);
		if(n>=m) throw std::invalid_argument("n>=m");
		if(n>((1<<(m-n))-1)) throw std::invalid_argument("2^m<n");
	}
	catch(std::exception& exp){
		std::cout<<"Incorect input nums:"<<exp.what()<<"\n";
		return 4;
	}


	// create matrix
	srand(time(0));
	// create code to D matrix
	int count_right_var=(1<<(m-n))-1, right_table[count_right_var][m-n];
	for(int i=0;i<count_right_var;++i){
		int temp=i+1;
		for(int j=m-n-1;j>=0;--j){
			right_table[i][j]=temp&1;
			temp=temp>>1;
		}
	}


	int arr[n][m];
	for(int i=0;i<n;++i){
		int j=0;
		// E matrix
		for(j=0;j<n;++j){
			if(i==j) arr[i][j]=1;
			else arr[i][j]=0;
		}
		// D matix
		int index=std::rand()%count_right_var, temp=0;
		for(j;j<m;++j){
			arr[i][j]=right_table[index][temp++];
		}
	}


	// show matrix
	std::cout<<n<<' '<<m<<'\n';
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j) std::cout<<arr[i][j]<<' ';
		std::cout<<'\n';
	}


	// create all code words
	int count_code=(1<<n), code_words[count_code-1][m];
	for(int i=0;i<count_code-1;++i){
		for(int j=0;j<m;++j) code_words[i][j]=0;
	}
	for(int i=1;i<count_code;++i){
		for(int j=0;j<n;++j){
			if(((i>>j)&1)!=1) continue;

			for(int k=0;k<m;++k){
				code_words[i-1][k]=(code_words[i-1][k]+arr[j][k])%2;
			}
		}

	}

	// calculate weight in code words
	int code_dist=m+1;
	for(int i=0;i<count_code-1;++i){
		int count=0;
		for(int j=0;j<m;++j) count+=code_words[i][j];
		if(code_dist>count) code_dist=count;
	}


	// show table info
	std::cout<<" Code length = "<<m<<'\n';
	std::cout<<" Razmer code = "<<n<<'\n';
	std::cout<<" Count code word = "<<count_code<<'\n';
	std::cout<<" Code dist = "<<code_dist<<'\n';

	return 0;
}