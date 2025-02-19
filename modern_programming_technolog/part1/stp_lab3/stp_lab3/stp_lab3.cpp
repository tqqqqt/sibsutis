#include <iostream>
#include "MathLib.h"

int main()
{
    std::cout<<"Find max="<<MathLib::LabLib3::findMax(3,1,2)<<'\n';
    std::cout<<"Index num=" << MathLib::LabLib3::createIndexNum(-1357) << '\n';
    std::cout<<"Min index num="<<MathLib::LabLib3::findMinIndex(-4526)<<'\n';
    std::vector<std::vector<int>> temp_mas = { {1, 2, 3}, { 4,5,6 }, { 7,8,9 } };
    int sum_diag=0;
    try {
        sum_diag = MathLib::LabLib3::summUnderDiag(temp_mas) << '\n';
    }
    catch (const char* error_mes) {
        std::cout<<error_mes;
        return -1;
    }
    std::cout << "Sum under diag=" <<sum_diag<<'\n';
    return 0;
}