#ifndef LAB1LIB
#define LAB1LIB

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <algorithm>

#include "numbermath.h"

std::string findModule(std::string num1, long long num2, std::string num3);
std::tuple<std::string,std::string,std::string> findNod(std::string num1, std::string num2);
void twoKeys(long long p, long long g);
void findKey(std::string num1, std::string num3, std::string module_res);

#endif