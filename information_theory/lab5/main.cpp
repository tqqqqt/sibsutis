#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <random>

#define WORD_TO_CODE_LEN 7

void codeWord(const int& count_check_bit, const int& len_word, std::vector<int>& code_word, const std::vector<std::vector<int>>& matrix, std::ofstream& file){
	int check_bit[count_check_bit];

	// calculate check bit
	for(int i=0;i<count_check_bit;++i){
		int temp=0;
		for(int j=0;j<len_word;++j){
			temp+=code_word[j]*matrix[i][j];
		}
		check_bit[i]=temp%2;
	}

	// change check bit in code word
	for(int i=0, index=0;i<len_word;++i){
		if(((i+1)&i)==0){
			code_word[i]=check_bit[index];
			++index;
		}
		file.put('0'+code_word[i]);
	}
}

void decodeWord(const int& count_check_bit, const int& len_word, std::vector<int> code_word, const std::vector<std::vector<int>>& matrix){
	int check_bit[count_check_bit], error=0;

	// calculate check bit
	for(int i=0;i<count_check_bit;++i){
		int temp=0;
		for(int j=0;j<len_word;++j){
			temp+=code_word[j]*matrix[i][j];
		}
		check_bit[i]=temp%2;
		error+=check_bit[i];
	}

	// check error
	if(error==0) return;

	// try fix if find error
	error=0;
	for(int i=0;i<count_check_bit;++i){
		if(code_word[i]==1) error=error|(1<<i);
	}
	error-=1;
	
	if(error<0 || error>=len_word) return;
	code_word[error]=1-code_word[error];
}

void damageFile(const std::string& file_name, const std::string& file_name_new, const double& p){
	std::vector<double> prob{p, 1-p};
	std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> distribution(prob.begin(),prob.end());

    std::ifstream file_in(file_name);
    std::ofstream file_out(file_name_new);
    int res=0;
    char symb;
    while(file_in.get(symb)){
    	res=distribution(gen);
    	if(res==1){
    		file_out.put(symb);
    		continue;
    	}
    	// reverse bit
    	if(symb=='0') file_out.put('1');
    	else file_out.put('0');
    }

    file_in.close();
    file_out.close();
}

void checkFiles(const std::string& orig_file_name, const std::string& decode_file_name, const double& p){
	char s_1, s_2;
	int error_count=0;

	std::ifstream file_origin(orig_file_name), file_decode(decode_file_name);
	while(file_decode.get(s_2)){
		file_origin.get(s_1);
		if(s_1!=s_2) ++error_count;
	}
	file_origin.close();
	file_decode.close();

	std::cout<<"p="<<p<<" errors="<<error_count<<'\n';
}

int main(){
	int count_check_bit=std::ceil(std::log2(WORD_TO_CODE_LEN))+1;
	int len_word=WORD_TO_CODE_LEN+count_check_bit;
	std::vector<int> code_word(len_word,0);
	std::vector<std::vector<int>> matrix(count_check_bit,std::vector<int>(len_word,0));

	// create matrix
	for(int i=0;i<len_word;++i){
		for(int j=0;j<count_check_bit;++j){
			matrix[j][i]=((i+1)>>j)&1;
		}
	}

	// coding words
	std::ifstream file_in("hafman_file_2.txt");
	std::ofstream file_out("heming.txt");
	int curent_count=0;
	char symb;
	while(file_in.get(symb)){
		while(((curent_count+1)&curent_count)==0){
			code_word[curent_count]=0;
			++curent_count;
		}
		code_word[curent_count]=symb-'0';
		++curent_count;

		if(curent_count<len_word) continue;

		codeWord(count_check_bit,len_word,code_word,matrix,file_out);
		curent_count=0;
	}
	file_in.close();
	file_out.close();

	// damage file code
	damageFile("heming.txt","heming_0-0001.txt",0.0001);
	damageFile("heming.txt","heming_0-001.txt",0.001);
	damageFile("heming.txt","heming_0-01.txt",0.01);
	damageFile("heming.txt","heming_0-1.txt",0.1);

	// check count errors in files
	for(int i=3;i>=0;--i){
		std::string file_name="heming_0-"+std::string(i,'0')+"1.txt";
		std::ifstream damage_file(file_name);
		std::ofstream decode_damage_file("decode_"+file_name);

		curent_count=0;
		symb=' ';
		while(damage_file.get(symb)){
			code_word[curent_count]=symb-'0';
			++curent_count;

			if(curent_count<len_word) continue;

			decodeWord(count_check_bit,len_word,code_word,matrix);

			// write only words bit, not check bit
			for(int j=0;j<len_word;++j){
				if(((j+1)&j)==0) continue;
				decode_damage_file.put('0'+code_word[j]);
			}
			curent_count=0;
		}

		damage_file.close();
		decode_damage_file.close();
	}

	checkFiles("hafman_file_2.txt","decode_heming_0-0001.txt",0.0001);
	checkFiles("hafman_file_2.txt","decode_heming_0-001.txt",0.001);
	checkFiles("hafman_file_2.txt","decode_heming_0-01.txt",0.01);
	checkFiles("hafman_file_2.txt","decode_heming_0-1.txt",0.1);

	return 0;
}