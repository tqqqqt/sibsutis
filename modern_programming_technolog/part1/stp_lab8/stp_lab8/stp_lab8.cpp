#include <iostream>
#include "TProc.h"

int main()
{
    try {
        TProc<int> proc;
        proc.writeLeftOper(2);
        proc.writeRightOper(0);
        proc.writeOperation(TOprtn::Mul);
        proc.executeOper();
        int left_oper=proc.readLeftOper(), right_oper=proc.readRightOper();
        std::cout<<"left oper = "<<left_oper<<", right = "<<right_oper<< '\n';
        proc.executeFunc(TFunc::Rev);
        left_oper = proc.readLeftOper();
        right_oper = proc.readRightOper();
        std::cout <<"left oper = " << left_oper << ", right = " << right_oper << '\n';
    }
    catch (std::exception& exp) {
        std::cout<<"Error: " << exp.what() << '\n';
        return -1;
    }
    return 0;
}