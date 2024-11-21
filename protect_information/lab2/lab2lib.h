#ifndef LAB2LIB
#define LAB2LIB

#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "lab1lib.h"

void shamiraEnc(long long num_p, std::string file_name);
void shamiraDec(long long num_p, std::string file_name, std::string file_out_name);
void elGamalEnc(std::string p, std::string g, std::string file_name);
void elGamalDec(std::string p, std::string g, std::string file_name, std::string file_out_name);
void vernamEnc(std::string file_name);
void vernamDec(std::string file_name, std::string file_out_name);
void rsaEnc(std::string file_name, std::vector<long long> prim_mas);
void rsaDec(std::string file_name, std::string file_out_name);

#endif