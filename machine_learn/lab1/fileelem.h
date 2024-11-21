#ifndef FILE_CLASS
#define FILE_CLASS

#include <cmath>

class file_element{
private:
	int num_1, num_2, num_class;
	double distance_to_null;

public:
	file_element(int _num1, int _num2, int _num3);

	int numX();
	int numY();
	int numClass();
	bool checkClass(int _class);
	double getNullDistance();
	double distanceTo(file_element _element);
};

#endif