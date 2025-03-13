#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QVector>

#include "Num.h"

class Processor{
protected:
    char last_operator;

public:
    virtual ~Processor(){ }

    virtual void execute(QVector<Num*>&)=0;
    virtual void clear()=0;
};

#endif // PROCESSOR_H
