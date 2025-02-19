#include<iostream>
#include<fstream>
#include<map>
#include<bitset>
#include<sstream>
#include<algorithm>
#include<cstring>
using namespace std;

map<string, int> d = {
        {"READ", 0x10},
        {"WRITE", 0x11},
        {"LOAD", 0x20},
        {"STORE", 0x21},
        {"ADD", 0x30},
        {"SUB", 0x31},
        {"DIVIDE", 0x32},
        {"MUL", 0x33},
        {"JUMP", 0x40},
        {"JNEG", 0x41},
        {"JZ", 0x42},
        {"HALT", 0x43},
        {"JNS", 0x55}};

int sc_commandEncode (int command, int operand, int *value){
  *value = 0;
  *value |= (command & 127);
  *value = *value << 7;
  *value |= (operand & 127);
  return 0;
}

int main(int argc, char* arg[]) {
	if(argc!=3){
		cout << "Not enought argc."<<endl;
		return -1;
	}
    uint16_t memory[100] = {0};
    string file_name_input = (const char*)arg[argc-2];
    ifstream INPUT(file_name_input);
    FILE *file = fopen(arg[argc-1],"wb");
    string line;
    while (getline(INPUT, line)) {
        int pos, operand, temp;
        string command;
        istringstream iss(line);
        iss >> pos >> command >> operand;
        pos = int(pos);
        transform(command.begin(), command.end(), command.begin(), ::toupper);
        if (d.find(command) != d.end() && -1 < pos < 100 && -1 < operand < 100) {
			string tempComand = std::bitset<7>(d[command]).to_string();
			int finalTempComand = std::stoi(tempComand,NULL,2);
			int tempRes = 0;
			sc_commandEncode(finalTempComand,operand,&tempRes);
			memory[pos]=tempRes;
	    } 
		else if (command == "=" && -1 < pos < 100 && -0x3FFF <= operand <= 0x3FFF) {
			if (operand < 0) {
				operand = operand | 0x4000;
			}
			memory[pos]=operand;
	    }
    }
    fwrite(memory,sizeof(uint16_t),100,file);
    fclose(file);
    INPUT.close();
    return 0;
}
