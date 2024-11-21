#ifndef MASHINE_CLASS
#define MASHINE_CLASS

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <unordered_map>
#include "fileelem.h"

class mashine{
private:
	double curent_h;
	bool sort_data;
	std::vector<file_element> data;

	double yadro(int _h);

public:
	mashine();

	bool isDataSort();
	void setData(std::vector<file_element>& _data);
	void sortData();
	void learnSort();
	void workSort();
};

#endif