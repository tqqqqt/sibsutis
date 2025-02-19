#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<cmath>
#include<regex>
#include<map>
using namespace std;

struct variableStruct {
	string name;
	int addres;
	variableStruct(string tempName, int tempAdres) {
		this->name = tempName;
		this->addres = tempAdres;
	}
};

struct comandSimpleAStruct {
	int pos, operand;
	string command;
	comandSimpleAStruct(int tempPos, string tempComand, int tempOperand) {
		this->pos = tempPos;
		this->command = tempComand;
		this->operand = tempOperand;
	}
};

int curentComand = 0, curentVariable = 99;

const std::regex CheckLine(R"((\d+)\s+(REM|INPUT|PRINT|OUTPUT|LET|GOTO|IF|END)\s*(.*))");
const std::regex CheckValue(R"(([A-Z])\s*)");
const std::regex CheckNumber(R"((\-?\d+)\s*)");

map<string, int> basicCommandsToAsembler;
vector<variableStruct> variable;
vector<comandSimpleAStruct> resComand;
vector<int> gotoQue;

int FindVariable(string variableFind) {
	for (int i = 0; i < variable.size(); i++) {
		if (variable[i].name == variableFind) {
			return i;
		}
	}
	variable.emplace_back(variableFind, curentVariable--);
	return variable.size() - 1;
}

int OpInput(string operand, string line) {
	cmatch oper;
	if (!regex_match(operand.c_str(), oper, CheckValue)) {
		cout << " -> " << line << endl << "Error - incorrect INPUT command.";
		return -1;
	}
	int operOperand = FindVariable(oper[1]);
	resComand.emplace_back(comandSimpleAStruct(curentComand++, "READ ", variable[operOperand].addres));
	return 0;
}

int OpPrint(string operand, string line) {
	cmatch oper;
	if (!regex_match(operand.c_str(), oper, CheckValue) && !regex_match(operand.c_str(), oper, CheckNumber)) {
		cout << " -> " << line << endl << "Error - incorrect PRINT command.";
		return -1;
	}
	//if (regex_match(operand, CheckNumber)) {
	if(!regex_match(operand,CheckValue)){
		//int temp = stoi(operand);
		//if (temp < -0x2000 || temp>0x1FFF) {
			cout << " -> " << line << endl << "Error - incorrect PRINT value.";
			return -1;
		//}
	}
	int operOperand = FindVariable(oper[1]);
	resComand.emplace_back(comandSimpleAStruct(curentComand++, "WRITE ", variable[operOperand].addres));
	return 0;
}

int OpGoTo(string operand, string line) {
	if (!regex_match(operand, std::regex (R"((\d+)\s*)"))) {
		cout << " -> " << line << endl << "Error - incorrect GOTO command.";
		return -1;
	}
	if (basicCommandsToAsembler.find(operand) == basicCommandsToAsembler.end()) {
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "JUMP ", stoi(operand)));
		gotoQue.emplace_back(resComand.size() - 1);
	}
	else {
		int operOperand = basicCommandsToAsembler.find(operand)->second;
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "JUMP ", operOperand));
	}
	return 0;
}

int OpIf(string operand, string line) {
	cmatch oper;
	const std::regex CheckIf(R"(([A-Z]|-?\d+)\s*(=|<|>)\s*([A-Z]|-?\d+)\s+(INPUT|PRINT|OUTPUT|LET|GOTO|END)\s*(.*))");
	if (!regex_match(operand.c_str(), oper, CheckIf)) {
		cout << " -> " << endl << "Error - incorrect IF command.";
		return -1;
	}
	string val1 = oper[1], valZnak = oper[2], val2 = oper[3], nextComand = oper[4], nextOper = oper[5];
	int operOperand1 = FindVariable(val1), operOperand2 = FindVariable(val2);
	if (valZnak == "=") {
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "LOAD ", variable[operOperand1].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "SUB ", variable[operOperand2].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "JZ ", 999));
	}
	else if (valZnak == "<") {
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "LOAD ", variable[operOperand1].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "SUB ", variable[operOperand2].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "JNEG ", 999));
	}
	else if (valZnak == ">") {
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "LOAD ", variable[operOperand2].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "SUB ", variable[operOperand1].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "JNEG ", 999));
	}

	int temp = resComand.size() - 1;
	if (basicCommandsToAsembler.find(nextOper) == basicCommandsToAsembler.end()) {
		resComand[temp].operand = stoi(nextOper);
		gotoQue.emplace_back(resComand.size() - 1);
	}
	else {
		short addressOperand = basicCommandsToAsembler.find(nextOper)->second;
		resComand[temp].operand = addressOperand;
	}
	return 0;
}

int OpLet(string operand, string line) {
	const std::regex oneParam(R"(([A-Z])\s*=\s*([A-Z]|-?\d+)\s*)");
	const std::regex twoParam(R"(([A-Z])\s*=\s*([A-Z]|-?\d+)\s*([\+\-\*\/])\s*([A-Z]|-?\d+)\s*)");
	cmatch oper;
	if (!regex_match(operand.c_str(), oper, oneParam) && !regex_match(operand.c_str(), oper, twoParam)) {
		cout << " -> " << line << endl << "Error - incorrect LET command.";
		return -1;
	}
	if (regex_match(operand, oneParam)) {
		string op1 = oper[1], op2 = oper[2];
		if (regex_match(op2, CheckNumber)) {
			int temp = stoi(op2);
			if (temp < -0x2000 || temp>0x1FFF) {
				cout << " -> " << line << endl << "Error - incorrect LET value.";
				return -1;
			}
		}
		int operOperand1 = FindVariable(op1), operOperand2 = FindVariable(op2);
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "LOAD ", variable[operOperand2].addres));
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "STORE ", variable[operOperand1].addres));
	}
	else if (regex_match(operand, twoParam)) {
		string mainOp = oper[1], op1 = oper[2], sign = oper[3], op2 = oper[4];
		if (regex_match(op1, CheckNumber)) {
			int temp = stoi(op1);
			if (temp < -0x2000 || temp>0x1FFF) {
				cout << " -> " << line << endl << "Error - incorrect LET value.";
				return -1;
			}
		}
		int opOperand1 = FindVariable(op1);
		if (regex_match(op2, CheckNumber)) {
			int temp = stoi(op2);
			if (temp < -0x2000 || temp>0x1FFF) {
				cout << " -> " << line << endl << "Error - incorrect LET value.";
				return -1;
			}
		}
		int opOperand2 = FindVariable(op2);
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "LOAD ", variable[opOperand1].addres));
		if (sign == "+") {
			resComand.emplace_back(comandSimpleAStruct(curentComand++, "ADD ", variable[opOperand2].addres));
		}
		else if (sign == "-") {
			resComand.emplace_back(comandSimpleAStruct(curentComand++, "SUB ", variable[opOperand2].addres));
		}
		else if (sign == "*") {
			resComand.emplace_back(comandSimpleAStruct(curentComand++, "MUL ", variable[opOperand2].addres));
		}
		else if (sign == "/") {
			resComand.emplace_back(comandSimpleAStruct(curentComand++, "DIVIDE ", variable[opOperand2].addres));
		}
		int mainOpOperand = FindVariable(mainOp);
		resComand.emplace_back(comandSimpleAStruct(curentComand++, "STORE ", variable[mainOpOperand].addres));
	}
	return 0;
}

int OpEnd(string operand, string line) {
	if (!regex_match(operand, std::regex(R"(\s*)"))) {
		cout << " -> " << line << endl << "Error - incorrect END comand.";
		return -1;
	}
	resComand.emplace_back(comandSimpleAStruct(curentComand++, "HALT ", 0));
	return 0;
}

int main(int argc, char* arg[]) {
	if (argc != 3) {
		cout << "Error - not enough arguments.";
		return -1;
	}
	if (!regex_match(arg[argc-2], regex(R"(\w+\.sb)"))) {
		cout << "Error - second file is not .sb.";
		return -1;
	}

	string inputFile = (const char*)arg[argc - 2];
	ifstream INPUT(inputFile);
	if (!INPUT.is_open()) {
		cout << "Error - no input file";
		return -1;
	}

	int oldNumber = -1, flagEnd = 0;
	string line;
	std::cmatch parsedLine;

	while (getline(INPUT, line)) {
		string operand, comand;
		if (!regex_match(line.c_str(), parsedLine, CheckLine)) {
			cout << " -> " << line << endl << "Error check line.";
			return -1;
		}
		if (oldNumber >= stoi(parsedLine[1])) {
			cout << " -> " << line << endl << "Error number comand. ";
			return -1;
		}
		comand = parsedLine[2];
		if (comand == "REM") continue;
		else if (comand == "INPUT") {
			operand = parsedLine[3];
			basicCommandsToAsembler[parsedLine[1]] = curentComand;
			if (OpInput(operand, line)) {
				return -1;
			}
		}
		else if (comand == "OUTPUT" || comand == "PRINT") {
			operand = parsedLine[3];
			basicCommandsToAsembler[parsedLine[1]] = curentComand;
			if (OpPrint(operand, line)) {
				return -1;
			}
		}
		else if (comand == "GOTO") {
			operand = parsedLine[3];
			basicCommandsToAsembler[parsedLine[1]] = curentComand;
			if (OpGoTo(operand, line)) {
				return -1;
			}
		}
		else if (comand == "IF") {
			operand = parsedLine[3];
			basicCommandsToAsembler[parsedLine[1]] = curentComand;
			if (OpIf(operand, line)) {
				return -1;
			}
		}
		else if (comand == "LET") {
			operand = parsedLine[3];
			basicCommandsToAsembler[parsedLine[1]] = curentComand;
			if (OpLet(operand, line)) {
				return -1;
			}
		}
		else if (comand == "END") {
			operand = parsedLine[3];
			basicCommandsToAsembler[parsedLine[1]] = curentComand;
			if (OpEnd(operand, line)) {
				return -1;
			}
			flagEnd = 1;
		}

		if (curentComand > curentVariable) {
			cout << "Error - comand > memory";
			return -1;
		}
		oldNumber++;
	}

	INPUT.close();

	if (flagEnd != 1) {
		cout << "Error - no end command";
		return -1;
	}

	for (auto& i : gotoQue) {
		if (basicCommandsToAsembler.find(to_string(resComand[i].operand)) == basicCommandsToAsembler.end()) {
			cout << "GoTo check error.";
			return -1;
		}
		else {
			int operOperand = basicCommandsToAsembler.find(to_string(resComand[i].operand))->second;
			resComand[i].operand = operOperand;
		}
	}

	ofstream OUTPUT(arg[argc - 1]);
	if (!OUTPUT.is_open()) {
		cout << "Error output";
		return -1;
	}
	for (auto& i : resComand) {
		OUTPUT << i.pos << " " << i.command << " " << i.operand << endl;
	}
	for (int i = variable.size() - 1; i >= 0; i--) {
		if (!regex_match(variable[i].name, CheckValue)) {
			OUTPUT << variable[i].addres << " = ";
			int temp = stoi(variable[i].name);
			if (i > 0) {
				if (i < 10) OUTPUT << "+000" << temp << endl;
				else if (i >= 10 && i < 100) OUTPUT << "+00" << temp << endl;
				else if (i >= 100 && i < 1000) OUTPUT << "+0" << temp << endl;
				else OUTPUT << "+" << temp << endl;
			}
			else if (i < 0) {
				if (i > -10 && i <= -1) OUTPUT << "-000" << temp << endl;
				else if (i > -100 && i <= -10) OUTPUT << "-00" << temp << endl;
				else if (i > -1000 && i <= -100) OUTPUT << "-0" << temp << endl;
				else OUTPUT << "-" << temp << endl;
			}
		}
	}
	OUTPUT.close();
	return 0;
}
