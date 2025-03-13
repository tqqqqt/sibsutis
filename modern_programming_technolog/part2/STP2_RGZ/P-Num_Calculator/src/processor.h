#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

#include <QVector>

#include "converter.h"
#include "pnum.h"

class Processor
{
private:
    Converter converter;
    char last_operator;
    double last_operand;
    bool round_mode;

public:
    Processor();

    void changeSystem(QVector<PNum>&, int, int);
    void execute(QVector<PNum>&, int);
    void setMode(bool);
    void clear();
};

#endif // PROCESSOR_H
