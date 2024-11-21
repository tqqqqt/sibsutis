#pragma once

#include <vector>

template <typename T>
concept ValidType = requires(T a, T b) {
	a<b;
	a>b;
	a==b;
};

template<ValidType T>
class TSet {
private:
	std::vector<T> my_set;

public:
	TSet();
	TSet(const TSet<T>&);

	void clear();
	void add(T);
	void del(T);
	bool isEmpty();
	bool isIn(T);
	TSet append(TSet<T>);
	TSet sub(TSet<T>);
	TSet mull(TSet<T>);
	int count();
	T element(int);
};

template <ValidType T>
TSet<T>::TSet() {
	my_set=std::vector<T>();
}

template <ValidType T>
TSet<T>::TSet<T>(const TSet<T>& second_set) {
	my_set=second_set.my_set;
}

template <ValidType T>
void TSet<T>::clear() {
	my_set.clear();
}

template <ValidType T>
void TSet<T>::add(T _element) {
	for (int i=0;i<my_set.size();i++) {
		if(my_set[i] == _element) return;
		if (my_set[i] > _element) {
			my_set.insert(my_set.begin()+i,_element);
			return;
		}
	}
	my_set.push_back(_element);
}

template <ValidType T>
void TSet<T>::del(T _element) {
	for (int i = 0; i < my_set.size(); i++) {
		if (my_set[i] == _element) {
			my_set.erase(my_set.begin()+i);
			return;
		}
	}
}

template <ValidType T>
bool TSet<T>::isEmpty() {
	return my_set.size()==0;
}

template <ValidType T>
bool TSet<T>::isIn(T _element) {
	for (auto x : my_set) {
		if(x==_element) return true;
	}
	return false;
}

template <ValidType T>
TSet<T> TSet<T>::append(TSet<T> second_set) {
	TSet<T> result;
	for (auto x : this->my_set) result.add(x);
	for (auto x : second_set.my_set) result.add(x);
	return result;
}

template <ValidType T>
TSet<T> TSet<T>::sub(TSet<T> second_set) {
	TSet<T> result;
	for (auto x : this->my_set) result.add(x);
	for (auto x : second_set.my_set) result.del(x);
	return result;
}

template <ValidType T>
TSet<T> TSet<T>::mull(TSet<T> second_set) {
	TSet<T> result;
	for (auto x : this->my_set) {
		if(this->isIn(x) && second_set.isIn(x)) result.add(x);
	}
	for (auto x : second_set.my_set) {
		if (this->isIn(x) && second_set.isIn(x)) result.add(x);
	}
	return result;
}

template <ValidType T>
int TSet<T>::count() {
	int result=my_set.size();
	return result;
}

template <ValidType T>
T TSet<T>::element(int _index) {
	if(_index<0 || _index>=my_set.size()) throw std::exception("out of range");
	T result=my_set[_index];
	return result;
}