#ifndef NUM_H
#define NUM_H

#include <QString>

class Num{
public:
    enum class Object_type{ None, Num, Operator, Function };

protected:
    Object_type type;

public:
    virtual ~Num(){ }

    virtual void addNum(char)=0;
    virtual void addOper(char)=0;
    virtual void addFunc(QString)=0;

    virtual void delLast()=0;
    virtual void changeZnak()=0;

    Object_type getType(){
        return type;
    }

    virtual void clear()=0;
    virtual QString getString()=0;

    virtual Num* clone() const=0;
};

#endif // NUM_H
