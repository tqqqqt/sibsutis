#ifndef DNUM_PROCESSOR_H
#define DNUM_PROCESSOR_H

#include <string>

#include <QVector>

#include "processor.h"
#include "dnum.h"

class DNum_Processor: public Processor
{
private:
    int last_operand_first, last_operand_second;

public:
    DNum_Processor();

    void execute(QVector<Num*>&);
    void clear();
};

#endif // DNUM_PROCESSOR_H
