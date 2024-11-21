#include <iostream>

#include "TPoly.h"
#include "TMember.h"

int main()
{
    try {
        TPoly my_polinom1, my_polinom2;
        my_polinom1=my_polinom1+TMember(1,2);
        my_polinom1=my_polinom1+TMember(1,3);
        std::cout<<"polynom1: "<< my_polinom1.toString()<<'\n';
        my_polinom2=my_polinom2+TMember(1,2);
        my_polinom2=my_polinom2+TMember(1,3);
        std::cout<<"polynom2: "<<my_polinom2.toString()<<'\n';
        my_polinom1=my_polinom1*my_polinom2;
        std::cout<<"polynom1*polynom2: "<<my_polinom1.toString()<<'\n';
        std::cout<<"calculate x=2: "<<my_polinom1.calculate(2)<<'\n';
    }
    catch (...) {
        std::cout<<"Catch error. end.";
        return -1;
    }
    return 0;
}