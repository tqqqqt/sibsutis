#include "fileelem.h"

file_element::file_element(int _num1, int _num2, int _num3){
	num_1=_num1;
	num_2=_num2;
	num_class=_num3;
	distance_to_null=std::sqrt(std::pow(num_1,2)+std::pow(num_2,2));
}

double file_element::getNullDistance(){
	return distance_to_null;
}

double file_element::distanceTo(file_element _element){
	return std::sqrt(std::pow(num_1-_element.numX(),2)+std::pow(num_2-_element.numY(),2));
}

int file_element::numX(){
	return num_1;
}

int file_element::numY(){
	return num_2;
}

int file_element::numClass(){
	return num_class;
}

bool file_element::checkClass(int _class){
	return num_class==_class;
}