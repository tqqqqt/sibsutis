#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

class Converter
{
private:
    // convert from 10
    char intToChar(int num);
    std::string intToP(int num, int p);
    std::string fltToP(double num, int p, int c);

    // convert to 10
    int charToInt(char num);
    double strToFlt(std::string num, int p, double width);

public:
    Converter();

    std::string convertFrom10(double num, int p, int c);
    double convertTo10(std::string p_num, int p);
};

#endif // CONVERTER_H
