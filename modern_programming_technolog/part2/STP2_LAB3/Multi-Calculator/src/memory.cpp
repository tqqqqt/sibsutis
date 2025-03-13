#include "memory.h"

Memory::Memory()
{
    status=Memory_status::Off;
}

void Memory::clear(){
    status=Memory_status::Off;
}

void Memory::save(Num* _object){
    object=_object;
    status=Memory_status::On;
}

Num* Memory::copy(){
    if(status==Memory_status::Off) throw std::invalid_argument("memory off");

    return object;
}

Memory::Memory_status Memory::curentStatus(){
    return status;
}
