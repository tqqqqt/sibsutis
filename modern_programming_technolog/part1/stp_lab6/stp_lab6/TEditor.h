#pragma once

#include <string>
#include <iostream>

class TEditor {
private:
	std::string num_str;
	int curent_part, second_part_index;
	bool minus_oper[2];
	bool float_point[2];
	bool no_first_part;

public:
	TEditor();

	bool numIsNull();
	std::string changeMinus();
	std::string addPlus();
	std::string addNum(int);
	std::string addNull();
	std::string addFloatPoint();
	std::string delSymbol();
	std::string clear();
	std::string value();
	std::string value(std::string);
	std::string redact(int);
};

TEditor::TEditor() {
	num_str="";
	curent_part=0;
	second_part_index=-1;
	minus_oper[0]=false;
	minus_oper[1]=false;
	float_point[0]=false;
	float_point[1]=false;
}

bool TEditor::numIsNull() {
	if(num_str=="0+i*0") return true;
	if(num_str=="i*0") return true;
	return false;
}

std::string TEditor::changeMinus() {
	if (curent_part == 0) {
		if (no_first_part == true) throw std::exception("No first part");
		if (minus_oper[curent_part] == true) {
			num_str.erase(0, 1);
			second_part_index--;
		}
		else {
			num_str = '-' + num_str;
			second_part_index++;
		}
	}
	else{
		if(second_part_index==-1) throw std::exception("Second part not exist");
		if (second_part_index == 0) {
			if (minus_oper[curent_part] == true) num_str.erase(0,1);
			else num_str = '-' +num_str;
		}
		else {
			if (minus_oper[curent_part] == true) num_str[second_part_index] = '+';
			else num_str[second_part_index] = '-';
		}
	}
	minus_oper[curent_part] = !minus_oper[curent_part];
	return num_str;
}

std::string TEditor::addPlus() {
	if(curent_part==1) throw std::exception("+i* already exists");
	if(num_str.length()>0 && num_str[num_str.length() - 1]=='.') throw std::exception("Need complete float number");
	second_part_index=num_str.length();
	if(num_str.length()!=0 && num_str[0]!='-') num_str += "+i*";
	else {
		num_str = "i*";
		no_first_part = true;
	}
	curent_part=1;
	return num_str;
}

std::string TEditor::addNum(int _num) {
	if(_num<1 && _num>9) throw std::invalid_argument("Num need 1<=x<=9");
	num_str+=('0'+_num);
	return num_str;
}

std::string TEditor::addNull() {
	num_str+='0';
	return num_str;
}

std::string TEditor::addFloatPoint() {
	if (float_point[curent_part] == true) throw std::exception("Dot already exist");
	num_str += '.';
	float_point[curent_part]=true;
	return num_str;
}

std::string TEditor::delSymbol() {
	if (num_str.length() == 0) throw std::exception("String have length equal 0");
	if (num_str[num_str.length() - 1] == '*') {
		second_part_index=-1;
		curent_part=0;
		if(num_str.length()>3) num_str.erase(num_str.length()-3,3);
		else num_str.erase(num_str.length()-2,2);
		minus_oper[1]=false;
	}
	else if (num_str[num_str.length() - 1] == '.') {
		float_point[curent_part]=false;
		num_str.erase(num_str.length()-1);
	}
	else num_str.erase(num_str.length() - 1);
	if(num_str.length()==0) no_first_part=false;
	return num_str;
}

std::string TEditor::clear() {
	num_str="0+i*0";
	no_first_part=false;
	curent_part=1;
	for (int i = 0; i < 2; i++) {
		float_point[i]=false;
		minus_oper[i]=false;
	}
	second_part_index=1;
	return num_str;
}

std::string TEditor::value() {
	return num_str;
}

std::string TEditor::value(std::string _new_string) {
	if(std::count(_new_string.begin(),_new_string.end(),'i')!=1) throw std::invalid_argument("Incorect use i in string");
	if (std::count(_new_string.begin(),_new_string.end(),'*')!=1) throw std::invalid_argument("Incorect use * in string");
	int temp_part=0, temp_point_count=0, temp_minus_count=0, temp_second_part=-1;
	bool temp_minus_oper_part[2], temp_dot_part[2];
	for (int i = 0; i < _new_string.length(); i++) {
		if(!(_new_string[i]>='0' && _new_string[i]<='9') && _new_string[i]!='i' && (_new_string[i]!='+' && _new_string[i]!='-' && _new_string[i]!='*') && _new_string[i] != '.') throw std::invalid_argument("Invalid symbol in value");
		if(_new_string[i]>='0' && _new_string[i]<='9') continue;
		if (_new_string[i] == 'i' && i == 0) {
			temp_part=1;
			temp_second_part=0;
			continue;
		}
		else if(_new_string[i]=='i') continue;
		if ((_new_string[i] == '+' && (i + 1) < _new_string.length() && _new_string[i + 1] == 'i') || (_new_string[i]=='-' && (i + 1) < _new_string.length() && _new_string[i + 1] == 'i')) {
			if(_new_string[i]=='-') temp_minus_oper_part[1]=true;
			temp_part=1;
			temp_second_part=i>0?i:0;
			temp_point_count=0;
			temp_minus_count=0;
			continue;
		}
		else if(_new_string[i]=='+') throw std::invalid_argument("Incorect use +");
		if (_new_string[i] == '.') {
			temp_dot_part[temp_part]=true;
			if (++temp_point_count > 1) throw std::invalid_argument("Dot more then 1");
			continue;
		}
		if (_new_string[i] == '-') {
			temp_minus_oper_part[temp_part]=true;
			if(++temp_minus_count>1) throw std::invalid_argument("Minus oper more then 1");
			continue;
		}
		if (_new_string[i] == '*' && temp_part==0) throw std::invalid_argument("Incorect string with *");
	}
	num_str=_new_string;
	curent_part=temp_part;
	second_part_index=temp_second_part;
	for (int i = 0; i < 2; i++) {
		minus_oper[i] = temp_minus_oper_part[i];
		float_point[i] = temp_dot_part[i];
	}
	return num_str;
}

std::string TEditor::redact(int _num) {
	std::string input = "", result="";
	int temp=-1;
	try {
		switch (_num) {
		case 1:
			std::cout << "Input num -> ";
			std::cin >> input;
			result = addNum(std::stoi(input));
			break;
		case 2:
			result = addNull();
			break;
		case 3:
			std::cout << "Select part:\n0-first, 1-second\n Input -> ";
			std::cin >> input;
			if (input.length() != 1 || (input[0] != '0' && input[0] != '1')) throw std::exception("Invalid part");
			temp = curent_part;
			curent_part = std::stoi(input);
			result = changeMinus();
			curent_part = temp;
			temp = -1;
			break;
		case 4:
			result = addPlus();
			break;
		case 5:
			result = addFloatPoint();
			break;
		case 6:
			result = delSymbol();
			break;
		case 7:
			result = clear();
			break;
		case 8:
			std::cout << "Input -> ";
			std::cin >> input;
			result = value(input);
			break;
		default:
			throw std::invalid_argument("Need comand in 1<=x<=8");
			break;
		}
	}
	catch (std::exception& exp) {
		if (temp != -1) {
			curent_part = temp;
			temp = -1;
		}
		throw std::exception(exp.what());
	}
	return result;
}