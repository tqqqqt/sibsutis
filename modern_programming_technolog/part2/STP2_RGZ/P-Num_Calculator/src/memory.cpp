#include "memory.h"

Memory::Memory()
{
    status=Memory_status::Off;
}

void Memory::clear(){
    object.clear();
    status=Memory_status::Off;
}

void Memory::save(PNum _object){
    object=_object;
    status=Memory_status::On;
}

PNum Memory::copy(){
    if(status==Memory_status::Off) throw std::invalid_argument("memory off");
    return object;
}

Memory::Memory_status Memory::curentStatus(){
    return status;
}
