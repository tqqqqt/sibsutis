#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <sstream>
#include <fstream>

#include "fileelem.h"
#include "mashine.h"

int main(){
	std::string input="";
	mashine my_mashine=mashine();
	while(1){
		std::cout<<"\n 1 - load file\n 2 - learn on data\n 3 - result data\n 4 - exit\n -> ";
		std::cin>>input;
		if(input=="1"){
			std::cout<<" Input file name -> ";
			std::cin>>input;
			if(!std::filesystem::exists(input)){
				std::cout<<" No file.\n";
				continue;
			}
			std::ifstream file(input);
			std::vector<file_element> temp_vector;
			std::string line="", cell="";
			std::getline(file,line);
			while(std::getline(file,line)){
				std::stringstream str;
				str<<line;
				std::vector<int> cell_vector(3,0);
				int curent_cell=0;
				while(std::getline(str,cell,',')) cell_vector[curent_cell++]=std::stoi(cell);
				file_element temp_element=file_element(cell_vector[0],cell_vector[1],cell_vector[2]);
				temp_vector.push_back(temp_element);
			}
			my_mashine.setData(temp_vector);
			my_mashine.sortData();
		}
		else if(input=="2") my_mashine.learnSort();
		else if(input=="3") my_mashine.workSort();
		else if(input=="4") break;
		else std::cout<<" Error input.\n";
	}
	return 0;
}