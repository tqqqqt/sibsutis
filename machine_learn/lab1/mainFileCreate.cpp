#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>

int main(){
	while(1){
		std::string fileName="";
		std::cout<<"Enter file name -> ";
		std::cin>>fileName;
		if(fileName=="e") break;
		if(!(std::filesystem::exists(fileName))){
			std::cout<<"No file.\n";
			continue;
		}
		std::ifstream file(fileName);
		std::vector<std::ofstream> filestr(3);
		int dotPos=fileName.find('.'), curentPoint=0;
		for(int i=0;i<3;i++){
			std::string temp=fileName;
			temp.insert(dotPos,("-"+(std::to_string(i+1))));
			filestr[i]=std::ofstream(temp);
		}
		std::string line="";
		std::getline(file,line);
		for(int i=0;i<3;i++) filestr[i]<<line<<"\n";
		while(std::getline(file,line)){
			filestr[curentPoint++]<<line<<"\n";
			if(curentPoint>=3) curentPoint=0;
		}
	}
	return 0;
}