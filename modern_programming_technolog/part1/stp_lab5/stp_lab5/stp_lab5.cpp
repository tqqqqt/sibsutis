#include <iostream>
#include "TPNumber.h"

int main()
{
    try {
        TPNumber num=TPNumber(123456789.987654321,13,11), temp=TPNumber("1","13","11");
        std::cout<<"Num in str = "<< num.valueStr() << '\n';
        num=num+temp;
        std::cout<<"Num + 1 in str = "<<num.valueStr()<<'\n';
    }
    catch (const char* err) {
        std::cout<<"Error: "<<err<<"\n";
        return -1;
    }
    return 0;
}