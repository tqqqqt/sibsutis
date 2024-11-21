#pragma once

#include <concepts>
#include <exception>

enum class TOprtn{ None, Add, Sub, Mul, Dvd };

enum class TFunc{ Rev, Sqr };

template <typename T>
concept ValidType = requires(T a, T b) {
	T();
	a=b;
	a+b;
	a-b;
	a/b;
	a*b;
};

template <ValidType T>
class TProc {
private:
	T lop_res;
	T rop;
	TOprtn operation;

	T divideOper(T, T);
	T reverseFunc(T);

public:
	TProc();

	void clearProc();
	void clearOper();
	void executeOper();
	void executeFunc(TFunc);

	T readLeftOper();
	void writeLeftOper(T);

	T readRightOper();
	void writeRightOper(T);

	TOprtn readOperation();
	void writeOperation(TOprtn);
};

template <ValidType T>
TProc<T>::TProc() {
	lop_res=T();
	rop=T();
	operation=TOprtn::None;
}

template <ValidType T>
void TProc<T>::clearProc() {
	lop_res=T();
	rop=T();
	operation=TOprtn::None;
}

template <ValidType T>
void TProc<T>::clearOper() {
	operation=TOprtn::None;
}

int TProc<int>::divideOper(int _left_oper, int _right_oper) {
	if(_right_oper==0) throw std::invalid_argument("Right oper equal 0");
	return _left_oper/_right_oper;
}

template<ValidType T>
T TProc<T>::divideOper(T _left_oper, T _right_oper) {
	return _left_oper/_right_oper;
}

template <ValidType T>
void TProc<T>::executeOper() {
	try {
		switch (operation) {
		case TOprtn::None:
			break;
		case TOprtn::Add:
			lop_res = lop_res + rop;
			break;
		case TOprtn::Sub:
			lop_res = lop_res - rop;
			break;
		case TOprtn::Dvd:
			lop_res=divideOper(lop_res,rop);
			break;
		case TOprtn::Mul:
			lop_res = lop_res * rop;
			break;
		}
	}
	catch (std::exception &exp) {
		throw exp;
	}
}

int TProc<int>::reverseFunc(int _num) {
	if(_num==0) return 0;
	return 1/_num;
}

template <ValidType T>
T TProc<T>::reverseFunc(T _num) {
	return 1/_num;
}

template <ValidType T>
void TProc<T>::executeFunc(TFunc _function) {
	try {
		switch (_function) {
		case TFunc::Rev:
			rop = reverseFunc(rop);
			break;
		case TFunc::Sqr:
			rop = rop * rop;
			break;
		}
	}
	catch (std::exception& exp) {
		throw exp;
	}
}

template <ValidType T>
T TProc<T>::readLeftOper() {
	T result=lop_res;
	return result;
}

template <ValidType T>
void TProc<T>::writeLeftOper(T _element) {
	T temp=_element;
	lop_res=temp;
}

template <ValidType T>
T TProc<T>::readRightOper() {
	T result=rop;
	return result;
}

template <ValidType T>
void TProc<T>::writeRightOper(T _element) {
	T temp=_element;
	rop=temp;
}

template <ValidType T>
TOprtn TProc<T>::readOperation() {
	TOprtn result=operation;
	return result;
}

template <ValidType T>
void TProc<T>::writeOperation(TOprtn _element) {
	operation=_element;
}