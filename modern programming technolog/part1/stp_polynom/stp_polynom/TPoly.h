#pragma once

#include <vector>
#include <utility>
#include <string>

#include "TMember.h"

class TPoly {
public:
	enum class PolyOperator { Sum, Sub, Mull, None };

	std::vector<std::pair<PolyOperator,TMember>> polynom;

	TPoly solveMulls();

public:
	TPoly(int=0, int=0);
	TPoly(TMember);

	int degree();
	int coeff(int);
	void clear();
	void popBack();

	TPoly operator+(TMember);
	TPoly operator+(TPoly);
	TPoly operator*(TMember);
	TPoly operator*(TPoly);
	TPoly operator-(TMember);
	TPoly operator-(TPoly);
	bool operator==(TPoly);

	TPoly dif();
	int calculate(int);
	TMember operator[](int);
	std::string toString();
};

TPoly::TPoly(int _coeff, int _degree) {
	if(_coeff==0 && _degree==0) return;
	polynom.push_back(std::make_pair(PolyOperator::None,TMember(_coeff,_degree)));
}

TPoly::TPoly(TMember _num) {
	polynom.push_back(std::make_pair(PolyOperator::None,_num));
}

int TPoly::degree() {
	int result=0;
	for (auto x : polynom) {
		if(x.second.coeff()==0) continue;
		if(result<x.second.degree()) result=x.second.degree();
	}
	return result;
}

int TPoly::coeff(int _degree) {
	int result=0;
	for (auto x : polynom) {
		if (x.second.degree() == _degree) {
			result=x.second.coeff();
			break;
		}
	}
	return result;
}

void TPoly::clear() {
	polynom.clear();
}

void TPoly::popBack() {
	if(polynom.size()) polynom.pop_back();
}

TPoly TPoly::operator+(TMember _num) {
	TPoly result=*this;
	for (int i = 0; i < result.polynom.size(); i++) {
		if (_num.isSumSub(result.polynom[i].second)) {
			result.polynom[i].second = result.polynom[i].second + _num;
			if (result.polynom[i].second.coeff() < 0) result.polynom[i].first = PolyOperator::Sub;
			return result;
		}
	}
	if (_num.coeff() < 0) {
		TMember temp=_num.minus();
		result.polynom.push_back(std::make_pair(PolyOperator::Sub,temp));
	}
	else result.polynom.push_back(std::make_pair(PolyOperator::Sum,_num));
	if(result.polynom.size()==1 && result.polynom.back().first!=PolyOperator::Sub) result.polynom[0].first=PolyOperator::None;
	return result;
}

TPoly TPoly::operator+(TPoly _polynom) {
	TPoly result=*this;
	for (auto x : _polynom.polynom) {
		int flg=0;
		for (int i = 0; i < result.polynom.size(); i++) {
			if (result.polynom[i].second.isSumSub(x.second)) {
				result.polynom[i].second = result.polynom[i].second + x.second;
				if (result.polynom[i].second.coeff() < 0) result.polynom[i].first = PolyOperator::Sub;
				flg=1;
				break;
			}
		}
		if(flg) continue;
		if(x.first==PolyOperator::None) result.polynom.push_back(std::make_pair(PolyOperator::Sum,x.second));
		else result.polynom.push_back(x);
	}
	if (result.polynom.size() && result.polynom.back().first != PolyOperator::Sub) result.polynom[0].first = PolyOperator::None;
	return result;
}

TPoly TPoly::operator*(TMember _num) {
	TPoly result=*this;
	result.polynom.push_back(std::make_pair(PolyOperator::Mull,_num));
	if (result.polynom.size() == 1 && result.polynom.back().first != PolyOperator::Sub) result.polynom[0].first = PolyOperator::None;
	return result;
}

TPoly TPoly::solveMulls() {
	TPoly result;
	if(polynom.size()==0) return result;
	result.polynom.push_back(polynom[0]);
	for (int i = 1; i < polynom.size(); i++) {
		if(polynom[i].first==PolyOperator::Mull) result.polynom.back().second=result.polynom.back().second*polynom[i].second;
		else result.polynom.push_back(polynom[i]);
	}
	return result;
}

TPoly TPoly::operator*(TPoly _polynom) {
	TPoly result;
	TPoly left=solveMulls(), right=_polynom.solveMulls();
	for (auto x : left.polynom) {
		for (auto y : right.polynom) {
			result.polynom.push_back(std::make_pair(PolyOperator::Sum,x.second*y.second));
			if((x.first==PolyOperator::Sub && y.first!=PolyOperator::Sub) || (x.first != PolyOperator::Sub && y.first == PolyOperator::Sub)) result.polynom.back().first=PolyOperator::Sub;
		}
	}
	for (int i = 0; i < result.polynom.size(); i++) {
		for (int j = i + 1; j < result.polynom.size(); j++) {
			if (result.polynom[i].second.isSumSub(result.polynom[j].second)) {
				result.polynom[i].second= result.polynom[i].second+ result.polynom[j].second;
				if (result.polynom[i].second.coeff() < 0) result.polynom[i].first = PolyOperator::Sub;
				result.polynom.erase(result.polynom.begin()+j);
				j--;
				if(j<0) j=0;
			}
		}
	}
	if(result.polynom.size() && result.polynom.back().first != PolyOperator::Sub) result.polynom[0].first=PolyOperator::None;
	return result;
}

TPoly TPoly::operator-(TMember _num) {
	TPoly result=*this;
	for (int i = 0; i < result.polynom.size(); i++) {
		if (result.polynom[i].second.isSumSub(_num)) {
			result.polynom[i].second = result.polynom[i].second - _num;
			if (result.polynom[i].second.coeff() < 0) {
				result.polynom[i].first = PolyOperator::Sub;
				result.polynom[i].second = result.polynom[i].second.minus();
			}
			return result;
		}
	}
	if (_num.coeff() < 0) {
		TMember temp=_num.minus();
		result.polynom.push_back(std::make_pair(PolyOperator::Sum,temp));
	}
	else result.polynom.push_back(std::make_pair(PolyOperator::Sub,_num));
	if (result.polynom.size() == 1 && result.polynom.back().first != PolyOperator::Sub) result.polynom[0].first = PolyOperator::None;
	return result;
}

TPoly TPoly::operator-(TPoly _polynom) {
	TPoly result=*this;
	TPoly right=_polynom.solveMulls();
	for (auto x : right.polynom) {
		int flg=0;
		for (int i = 0; i < result.polynom.size(); i++) {
			if (result.polynom[i].second.isSumSub(x.second)) {
				result.polynom[i].second = result.polynom[i].second - x.second;
				if (result.polynom[i].second.coeff() < 0) {
					result.polynom[i].first = PolyOperator::Sub;
					result.polynom[i].second = result.polynom[i].second.minus();
				}
				flg = 1;
				break;
			}
		}
		if(flg) continue;
		if(x.first==PolyOperator::Sum || x.first==PolyOperator::None) result.polynom.push_back(std::make_pair(PolyOperator::Sub,x.second));
		else result.polynom.push_back(std::make_pair(PolyOperator::Sum,x.second));
	}
	if (result.polynom.size() && result.polynom.back().first != PolyOperator::Sub) result.polynom[0].first = PolyOperator::None;
	return result;
}

bool TPoly::operator==(TPoly _polynom) {
	TPoly left=solveMulls(), right=_polynom.solveMulls();
	if(left.polynom.size()!=right.polynom.size()) return false;
	for (auto x : left.polynom) {
		int flag=0;
		for (auto y : right.polynom) {
			if (x.first == y.first && x.second == y.second) {
				flag=1;
				break;
			}
		}
		if(!flag) return false;
	}
	return true;
}

TPoly TPoly::dif() {
	TPoly result, temp=solveMulls();
	for (auto x : temp.polynom) {
		TMember temp_num=x.second.dif();
		if(!temp_num.isNull()) result.polynom.push_back(std::make_pair(x.first,temp_num));
	}
	return result;
}

int TPoly::calculate(int _x) {
	int result=0;
	for (auto x : polynom) {
		int temp=x.second.calculate(_x);
		if(x.first==PolyOperator::Sub) temp*=-1;
		result+=temp;
	}
	return result;
}

TMember TPoly::operator[](int _index) {
	if(_index<0 || _index>=polynom.size()) throw std::out_of_range("out of range");
	TMember result=polynom[_index].second;
	return result;
}

std::string TPoly::toString() {
	std::string result="";
	for (auto x : polynom) {
		if(x.second.isNull()) continue;
		if(x.first==PolyOperator::Sum) result+='+';
		else if(x.first==PolyOperator::Sub) result+='-';
		else if(x.first==PolyOperator::Mull) result+='*';
		result+=x.second.toString();
	}
	return result;
}