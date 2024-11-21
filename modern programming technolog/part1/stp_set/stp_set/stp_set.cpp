#include <iostream>

#include "TSet.h"

int main()
{
    try {
        TSet<int> set;
        set.add(2);
        set.add(4);
        set.add(3);
        for (int i = 0; i < set.count(); i++) {
            std::cout<<set.element(i)<<" ";
        }
        std::cout<<"\n \n";
        TSet<int> temp;
        temp.add(1);
        TSet<int> res=set.append(temp);
        for (int i = 0; i < res.count(); i++) {
            std::cout << res.element(i) << " ";
        }
        std::cout<<"\n \n";
        temp.clear();
        temp.add(2);
        res=set.mull(temp);
        for (int i = 0; i < res.count(); i++) {
            std::cout << res.element(i) << " ";
        }
        std::cout << "\n \n";
        res=set.sub(temp);
        for (int i = 0; i < res.count(); i++) {
            std::cout << res.element(i) << " ";
        }
        std::cout << "\n \n";
    }
    catch (...) {
        std::cout<<"Catch error. end.\n";
        return -1;
    }
    return 0;
}