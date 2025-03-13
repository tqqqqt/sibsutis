#ifndef PNUM_H
#define PNUM_H

#include <QString>

#include <string>

#include "num.h"

class PNum: public Num
{
private:
    int count_dot;
    size_t length;
    std::string text;

public:
    PNum();

    void addNum(char);
    void addOper(char);
    void addFunc(QString);
    void changeZnak();
    void addDot();
    void delLast();

    void clear();
    QString getString();
    QString getNum();
    void setNum(std::string);

    Num* clone() const;
};

#endif // PNUM_H
