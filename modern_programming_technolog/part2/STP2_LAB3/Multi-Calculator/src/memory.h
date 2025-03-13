#ifndef MEMORY_H
#define MEMORY_H

#include <QString>

#include "num.h"

class Memory
{
public:
    enum class Memory_status{ On, Off };

private:
    Memory_status status;
    Num* object;

public:
    Memory();

    void clear();
    void save(Num*);
    Num* copy();

    Memory_status curentStatus();
};

#endif // MEMORY_H
