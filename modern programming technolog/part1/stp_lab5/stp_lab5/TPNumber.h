#pragma once

#include <string>
#include <cmath>

class TPNumber {
public:
	TPNumber(double, int, int);
	TPNumber(std::string, std::string, std::string);

	int system();
	int accuracy();
	double value();
	std::string systemStr();
	std::string accuracyStr();
	std::string valueStr();
	void setSystem(int);
	void setSystem(std::string);
	void setAccuracy(int);
	void setAccuracy(std::string);

	TPNumber copy();
	TPNumber reverse();
	TPNumber square();

	TPNumber operator+(TPNumber);
	TPNumber operator*(TPNumber);
	TPNumber operator-(TPNumber);
	TPNumber operator/(TPNumber);
	
private:
	int num_system, num_accuracy;
	double num_double;
};

TPNumber::TPNumber(double _num, int _system, int _accuracy) {
	if(_system<2 || _system>16) throw "incorrect system of p-num";
	if(_accuracy<0) throw "incorrect accuracy on p-num";
	num_double = _num;
	num_system=_system;
	num_accuracy=_accuracy;
}

TPNumber::TPNumber(std::string _num, std::string _system, std::string _accuracy) {
	if (_num.length() == 0) throw "incorrect num, length str 0";
	if (_system.length()==0) throw "incorrect system, length str 0";
	if (_accuracy.length()==0) throw "incorrect accuracy, length str 0";
	int temp_system=0, temp_accuracy=0, temp_num=0;
	try {
		temp_system = std::stoi(_system);
		temp_accuracy = std::stoi(_accuracy);
		temp_num=std::stod(_num); //incorect, need convert num to 10-system num
	}
	catch (...) {
		throw "incorect arguments, can't convert string to num";
	}
	if (temp_system < 2 || temp_system>16) throw "incorrect system of p-num";
	if (temp_accuracy < 0) throw "incorrect accuracy on p-num";
	num_system=temp_system;
	num_accuracy=temp_accuracy;
	num_double=temp_num;
}

TPNumber TPNumber::operator+(TPNumber second_num) {
	if(this->num_system!=second_num.system()) throw "incorect systems";
	if(this->num_accuracy!=second_num.accuracy()) throw "incorrect accuracy";
	TPNumber result=TPNumber(this->num_double+second_num.value(), this->num_system, this->num_accuracy);
	return result;
}

TPNumber TPNumber::operator*(TPNumber second_num) {
	if (this->num_system != second_num.system()) throw "incorect systems";
	if (this->num_accuracy != second_num.accuracy()) throw "incorrect accuracy";
	TPNumber result = TPNumber(this->num_double * second_num.value(), this->num_system, this->num_accuracy);
	return result;
}

TPNumber TPNumber::operator-(TPNumber second_num) {
	if (this->num_system != second_num.system()) throw "incorect systems";
	if (this->num_accuracy != second_num.accuracy()) throw "incorrect accuracy";
	TPNumber result = TPNumber(this->num_double - second_num.value(), this->num_system, this->num_accuracy);
	return result;
}

TPNumber TPNumber::operator/(TPNumber second_num) {
	if (this->num_system != second_num.system()) throw "incorect systems";
	if (this->num_accuracy != second_num.accuracy()) throw "incorrect accuracy";
	if (second_num.value() == 0) throw "incorrect divide to 0";
	TPNumber result = TPNumber(this->num_double / second_num.value(), this->num_system, this->num_accuracy);
	return result;
}

TPNumber TPNumber::copy() {
	return TPNumber(this->num_double,this->num_system,this->num_accuracy);
}

TPNumber TPNumber::reverse() {
	if(this->num_double==0) throw "num equal 0.";
	TPNumber result=TPNumber((double)(1/this->num_double), this->num_system, this->num_accuracy);
	return result;
}

TPNumber TPNumber::square() {
	TPNumber result=TPNumber((double)(this->num_double*this->num_double), this->num_system, this->num_accuracy);
	return result;
}

int TPNumber::system() {
	return num_system;
}

std::string TPNumber::systemStr() {
	return std::to_string(this->num_system);
}

int TPNumber::accuracy() {
	return num_accuracy;
}

std::string TPNumber::accuracyStr() {
	return std::to_string(this->num_accuracy);
}

double TPNumber::value() {
	return num_double;
}

std::string TPNumber::valueStr() {
	if(this->num_system==10) return std::to_string(num_double); //1 2
	double full_num = 0, num_after_dot=0; //3 4
	int cary = 0, temp=0; //5 6
	num_after_dot=modf(this->num_double,&full_num); //7
	std::string result=""; //8
	while (full_num >= this->num_system) { //9
		cary=floor(full_num/this->num_system);//10
		temp=(int)(full_num -(this->num_system * cary));//11
		if(temp>9) result=(char)('a'+(temp-10))+result;//12 13
		else result=std::to_string(temp)+result;//14
		full_num=cary;//15
	}
	if(full_num>9) result=(char)('a'+(full_num-10))+result;//16 17
	else result=std::to_string((int)full_num)+result;//18
	if(this->num_accuracy>0 && num_after_dot != 0) {//19
		result += '.';//20
		int length=0;//21
		while (length < this->num_accuracy) {//22
			num_after_dot*=this->num_system;//23
			num_after_dot=modf(num_after_dot,&full_num);//24
			if((int)full_num>9) result+='A'+(full_num-10);//25 26
			else result+=std::to_string((int)full_num);//27
			length++;//28
		}
	}
	return result;//29
}

void TPNumber::setSystem(int _system) {
	if(_system<2 || _system>16) throw "incorrect system value.";
	this->num_system=_system;
}

void TPNumber::setSystem(std::string _system) {
	if(_system.length()==0) throw "length new system equal 0.";
	int temp_system=0;
	try {
		temp_system = std::stoi(_system);
	}
	catch (std::invalid_argument& exp) {
		throw "incorect arguments, can't convert string to num";
	}
	if(temp_system<2 || temp_system>16) throw "incorrect system value.";
	this->num_system=temp_system;
}

void TPNumber::setAccuracy(int _accuracy) {
	if(_accuracy<0) throw "incorrect accuracy value.";
	this->num_accuracy=_accuracy;
}

void TPNumber::setAccuracy(std::string _accuracy) {
	if(_accuracy.length()==0) throw "length new accuracy equal 0.";
	int temp_accuracy=0;
	try {
		temp_accuracy=std::stoi(_accuracy);
	}
	catch (std::invalid_argument &exp) {
		throw "incorect arguments, can't convert string to num";
	}
	if(temp_accuracy<0) throw "incorrect accuracy value.";
	this->num_accuracy=temp_accuracy;
}
