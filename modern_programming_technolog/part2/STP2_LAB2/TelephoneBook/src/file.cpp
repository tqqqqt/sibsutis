#include "file.h"

File::File(){ }

void File::saveInFile(std::string file_name, const std::vector<std::string>& list){
    std::ofstream file_out(file_name);

    size_t size=list.size();
    for(int i=0;i<size;i+=2) file_out<<list[i]<<' '<<list[i+1]<<'\n';

    file_out.close();
}

void File::loadFromFile(std::string file_name, std::vector<std::string>& list){
    std::ifstream file_in(file_name);

    std::string name="", phone="";
    while(file_in>>name>>phone){
        list.push_back(name);
        list.push_back(phone);
    }

    file_in.close();
}
