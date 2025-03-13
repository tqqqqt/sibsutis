#ifndef PNUM_H
#define PNUM_H

#include <QString>

#include <string>

class PNum
{
public:
    enum class Object_type{ None, Num, Operator, Function };

private:
    Object_type type;
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

    Object_type getType();
    void clear();
    QString getString();
    QString getNum();
    void setNum(std::string);
};

#endif // PNUM_H
