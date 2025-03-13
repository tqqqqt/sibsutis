#include <QtTest>

#include "../Multi-Calculator/src/cnum.h"

class t_cnum : public QObject
{
    Q_OBJECT

public:
    t_cnum();
    ~t_cnum();

private slots:
    void test_addNum_1();
    void test_addNum_2();
    void test_addNum_3();
    void test_addNum_4();
    void test_addNum_5();

    void test_addOper_1();
    void test_addOper_2();

    void test_addFunc_1();
    void test_addFunc_2();

    void test_setSpace();

    void test_delLast_1();
    void test_delLast_2();
    void test_delLast_3();
    void test_delLast_4();
    void test_delLast_5();

    void test_changeZnak_1();
    void test_changeZnak_2();

    void test_clear();

    void test_getString_1();
    void test_getString_2();
    void test_getString_3();

    void test_getFirstNum_1();
    void test_getFirstNum_2();

    void test_getSecondNum_1();
    void test_getSecondNum_2();

    void test_setNum_1();
    void test_setNum_2();
    void test_setNum_3();
};

t_cnum::t_cnum(){ }
t_cnum::~t_cnum(){ }

void t_cnum::test_addNum_1(){
    CNum object;
    QString result="incorect object";

    object.addOper('+');

    try{
        object.addNum('1');
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_addNum_2(){
    CNum object;
    QString curent_result="", result="1";

    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_addNum_3(){
    CNum object;
    QString curent_result="", result="1";

    object.addNum('0');
    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_addNum_4(){
    CNum object;
    QString curent_result="", result="i*1";

    object.setSpace();
    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_addNum_5(){
    CNum object;
    QString curent_result="", result="i*1";

    object.setSpace();
    object.addNum('0');
    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_addOper_1(){
    CNum object;
    QString result="incorect object";

    object.addNum('1');

    try{
        object.addOper('+');
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_addOper_2(){
    CNum object;
    QString curent_result="", result="+";

    object.addOper('+');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_addFunc_1(){
    CNum object;
    QString result="incorect object";

    object.addNum('1');

    try{
        object.addFunc("Rev");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_addFunc_2(){
    CNum object;
    QString curent_result="", result="Rev";

    object.addFunc("Rev");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_setSpace(){
    CNum object;
    QString curent_result="", result="i*";

    object.setSpace();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_delLast_1(){
    CNum object;
    QString curent_result="", result="";

    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_delLast_2(){
    CNum object;
    QString curent_result="", result="";

    object.addFunc("Rev");
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_delLast_3(){
    CNum object;
    QString curent_result="", result="i*";

    object.setSpace();
    object.addNum('2');
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_delLast_4(){
    CNum object;
    QString curent_result="", result="";

    object.setSpace();
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_delLast_5(){
    CNum object;
    QString curent_result="", result="1";

    object.addNum('1');
    object.addNum('2');
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_changeZnak_1(){
    CNum object;
    QString result="incorect object";

    object.addOper('+');

    try{
        object.changeZnak();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_changeZnak_2(){
    CNum object;
    QString curent_result_1="", curent_result_2="", result_1="(-2)", result_2="2";

    object.addNum('2');
    object.changeZnak();
    curent_result_1=object.getString();
    object.changeZnak();
    curent_result_2=object.getString();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
}

void t_cnum::test_clear(){
    CNum object;
    QString curent_result="", result="";

    object.addNum('1');
    object.clear();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_getString_1(){
    CNum object;
    QString curent_result="", result="2+i*2";

    object.setNum("2","2");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_getString_2(){
    CNum object;
    QString curent_result="", result="(-2)+(-i*2)";

    object.setNum("-2","-2");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_getString_3(){
    CNum object;
    QString curent_result="", result="i*2";

    object.setSpace();
    object.addNum('2');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_getFirstNum_1(){
    CNum object;
    QString result="incorect object";
    int curent_result=0;

    object.addOper('+');

    try{
        curent_result=object.getFirstNum();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_getFirstNum_2(){
    CNum object;
    int curent_result=0, result=2;

    object.addNum('2');
    curent_result=object.getFirstNum();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_getSecondNum_1(){
    CNum object;
    QString result="incorect object";
    int curent_result=0;

    object.addOper('+');

    try{
        curent_result=object.getSecondNum();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_getSecondNum_2(){
    CNum object;
    int curent_result=0, result=2;

    object.setSpace();
    object.addNum('2');
    curent_result=object.getSecondNum();

    QCOMPARE(curent_result,result);
}

void t_cnum::test_setNum_1(){
    CNum object;
    QString result="incorect first num";

    try {
        object.setNum("a","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_setNum_2(){
    CNum object;
    QString result="incorect second num";

    try {
        object.setNum("2","a");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum::test_setNum_3(){
    CNum object;
    QString curent_result="", result="2+i*3";

    object.setNum("2","3");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(t_cnum)

#include "tst_t_cnum.moc"
