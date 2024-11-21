#pragma once

#include <string>
#include <concepts>

enum class Mode { _On, _Off };

template<typename T>
concept CorrectType = requires(T a, T b) {
	T();
	a=b;
	a+b;
};

template<CorrectType T>
class TMemory {
private:
	T fNumber;
	Mode fState;

public:
	TMemory();
	TMemory(T);

	void write(T);
	T get();
	void add(T);
	void clear();
	std::string readState();
	T readNum();
};

template<CorrectType T>
TMemory<T>::TMemory() {
	fNumber=T();
	fState = Mode::_Off;
}

template<CorrectType T>
TMemory<T>::TMemory(T _fNumber) {
	fNumber=_fNumber;
	fState=Mode::_On;
}

template<CorrectType T>
void TMemory<T>::write(T _element) {
	fNumber=_element;
	fState=Mode::_On;
}

template<CorrectType T>
T TMemory<T>::get() {
	T result=fNumber;
	fState=Mode::_On;
	return result;
}

template<CorrectType T>
void TMemory<T>::add(T _element) {
	fNumber=fNumber+_element;
	fState=Mode::_On;
}

template<CorrectType T>
void TMemory<T>::clear() {
	fNumber=T();
	fState=Mode::_Off;
}

template<CorrectType T>
std::string TMemory<T>::readState() {
	std::string result="";
	if(fState==Mode::_On) result="On";
	else result="Off";
	return result;
}

template<CorrectType T>
T TMemory<T>::readNum() {
	T result=fNumber;
	return result;
}