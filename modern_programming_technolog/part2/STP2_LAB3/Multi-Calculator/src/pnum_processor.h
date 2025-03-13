#ifndef PNUM_PROCESSOR_H
#define PNUM_PROCESSOR_H

#include <string>

#include <QVector>

#include "processor.h"
#include "pnum_converter.h"
#include "pnum.h"

class PNum_Processor: public Processor
{
private:
    PNum_Converter converter;
    double last_operand;
    int curent_system;

public:
    PNum_Processor();

    void changeSystem(QVector<Num*>&, int, int);
    void execute(QVector<Num*>&);
    void setSystem(int);
    void clear();
};

#endif // PNUM_PROCESSOR_H
