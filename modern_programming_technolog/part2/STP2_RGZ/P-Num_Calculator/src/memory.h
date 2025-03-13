#ifndef MEMORY_H
#define MEMORY_H

#include <QString>

#include "pnum.h"

class Memory
{
public:
    enum class Memory_status{ On, Off };

private:
    Memory_status status;
    PNum object;

public:
    Memory();

    void clear();
    void save(PNum);
    PNum copy();

    Memory_status curentStatus();
};

#endif // MEMORY_H
