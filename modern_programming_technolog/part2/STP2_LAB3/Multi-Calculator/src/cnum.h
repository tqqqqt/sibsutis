#ifndef CNUM_H
#define CNUM_H

#include <QString>

#include <string>

#include "num.h"

class CNum: public Num
{
private:
    std::string first_num, second_num;
    bool complex_space;
    int minus_flag_1, minus_flag_2;
    size_t length_first, length_second;

public:
    CNum();

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

    Num* clone() const;
};

#endif // CNUM_H
