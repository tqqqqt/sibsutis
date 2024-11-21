#ifndef NUMBERMATH_H
#define NUMBERMATH_H

#include <string>
#include <vector>
#include <algorithm>

int MaxNumber(std::string num1, std::string num2);
int FindMultiplier(std::string num1, std::string num2);

std::string MathSum(std::string num1, std::string num2);
std::string MathNeg(std::string num1, std::string num2);
std::string MathDiv(std::string num1, std::string num2);
std::string MathMul(std::string num1, std::string num2);

std::string MathDivOld(std::string num1, std::string num2);
std::string MathModDiv(std::string num1, std::string num2);
std::string MathPow(std::string num1, std::string num2);

#endif // NUMBERMATH_H
