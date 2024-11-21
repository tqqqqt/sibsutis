#ifndef LAB3_LIB
#define LAB3_LIB

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <tuple>
#include <cmath>

#include "lab1lib.h"
#include "numbermath.h"

void setElGamal(std::vector<long long> prim_mas, std::string file_name, std::string file_out);
void checkElGamal(std::string file_text, std::string file_name);
void setRSA(std::vector<long long> prim_mas, std::string file_input, std::string file_name_out);
void checkRSA(std::string file_text, std::string file_name);
void setGOST(std::vector<long long> prim_mas, std::string file_text, std::string file_name_out);
void checkGOST(std::string file_name_text, std::string file_podp);

#endif