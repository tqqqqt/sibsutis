#pragma once

#include <cmath>
#include <string>

class TMember {
private:
	int f_coeff, f_degree;

public:
	TMember(int = 0, int = 0);
	int degree();
	void setDegree(int);
	int coeff();
	void setCoeff(int);

	bool operator==(TMember);
	TMember dif();
	int calculate(int);
	std::string toString();

	TMember minus();
	bool isSumSub(TMember);
	bool isNull();
	TMember operator+(TMember);
	TMember operator-(TMember);
	TMember operator*(TMember);
};

TMember::TMember(int _coef, int _degree) {
	f_coeff=_coef;
	f_degree=_degree;
}

int TMember::degree() {
	return f_degree;
}

void TMember::setDegree(int _degree) {
	f_degree=_degree;
}

int TMember::coeff() {
	return f_coeff;
}

void TMember::setCoeff(int _coeff) {
	f_coeff=_coeff;
}

bool TMember::operator==(TMember second_num) {
	if(f_coeff!=second_num.f_coeff && f_degree!=second_num.f_degree) return false;
	return true;
}

TMember TMember::dif() {
	if(f_degree==0) return TMember();
	TMember result=TMember(f_coeff*f_degree,f_degree-1);
	return result;
}

int TMember::calculate(int x) {
	int result=f_coeff*std::pow(x,f_degree);
	return result;
}

std::string TMember::toString() {
	if(f_coeff==0 && f_degree==0) return "";
	std::string result="";
	if(f_coeff!=0) result+=std::to_string(f_coeff);
	if (f_degree > 0) {
		result+='x';
		if(f_degree>1) result+='^'+std::to_string(f_degree);
	}
	return result;
}

TMember TMember::minus() {
	TMember result=(0-f_coeff);
	if(result.f_coeff!=0) result.f_degree=f_degree;
	return result;
}

bool TMember::isSumSub(TMember second_num) {
	return f_degree==second_num.f_degree;
}

bool TMember::isNull() {
	return f_coeff==0 && f_degree==0;
}

TMember TMember::operator+(TMember second_num) {
	if(!this->isSumSub(second_num)) throw std::invalid_argument("different degrees");
	TMember result=TMember(f_coeff+second_num.f_coeff,f_degree);
	return result;
}

TMember TMember::operator-(TMember second_num) {
	if(!this->isSumSub(second_num)) throw std::invalid_argument("defferent degrees");
	TMember result=TMember(f_coeff-second_num.f_coeff);
	if(result.f_coeff>0) result.f_degree=f_degree;
	return result;
}

TMember TMember::operator*(TMember second_num) {
	TMember result=TMember(f_coeff*second_num.f_coeff,f_degree+second_num.f_degree);
	return result;
}