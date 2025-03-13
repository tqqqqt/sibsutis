#ifndef DNUM_H
#define DNUM_H

#include <string>

#include <QString>

#include "num.h"

class DNum: public Num
{
private:
    std::string first_num, second_num;
    bool drob_space;
    int minus_flag;
    size_t length_first, length_second;

private:
    int gcd(int, int);

public:
    DNum();

    void addNum(char);
    void addOper(char);
    void addFunc(QString);
    void setSpace();

    void delLast();
    void changeZnak();

    void clear();
    QString getString();
    int getFirstNum();
    int getSecondNum();
    void setNum(std::string, std::string);

    void simplifyNum();

    Num* clone() const;
};

#endif // DNUM_H
