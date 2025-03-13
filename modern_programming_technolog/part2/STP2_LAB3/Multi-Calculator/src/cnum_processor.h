#ifndef CNUM_PROCESSOR_H
#define CNUM_PROCESSOR_H

#include <string>

#include <QVector>

#include "processor.h"
#include "cnum.h"

class CNum_Processor: public Processor
{
private:
    int last_operand_first, last_operand_second;

public:
    CNum_Processor();

    void execute(QVector<Num*>&);
    void clear();
};

#endif // CNUM_PROCESSOR_H
