#include <iostream>
#include "TMemory.h"

int main()
{
    try {
        int object=1;
        TMemory<int> mem_block;
        std::cout<<mem_block.readNum()<<" : "<<mem_block.readState()<<'\n';

        mem_block.write(object);
        std::cout<<mem_block.get() << " : " << mem_block.readState() << '\n';

        object=4;
        mem_block.add(object);
        std::cout<<mem_block.get() << " : " << mem_block.readState() << '\n';

        mem_block.clear();
        std::cout << mem_block.readNum() << " : " << mem_block.readState() << '\n';
    }
    catch (...) {
        std::cout<<"get error.\n";
        return -1;
    }
    return 0;
}
