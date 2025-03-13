#include <QtTest>

#include "../Multi-Calculator/src/dnum.h"

class t_dnum : public QObject
{
    Q_OBJECT

public:
    t_dnum();
    ~t_dnum();

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

    void test_setSpace_1();
    void test_setSpace_2();

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

    void test_getFirstNum_1();
    void test_getFirstNum_2();

    void test_getSecondNum_1();
    void test_getSecondNum_2();
    void test_getSecondNum_3();

    void test_setNum_1();
    void test_setNum_2();
    void test_setNum_3();
    void test_setNum_4();
    void test_setNum_5();
    void test_setNum_6();
    void test_setNum_7();

    void test_simplifyNum_1();
    void test_simplifyNum_2();
};

t_dnum::t_dnum(){ }
t_dnum::~t_dnum(){ }

void t_dnum::test_addNum_1(){
    DNum object;
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

void t_dnum::test_addNum_2(){
    DNum object;
    QString curent_result="", result="1";

    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_addNum_3(){
    DNum object;
    QString curent_result="", result="1";

    object.addNum('0');
    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_addNum_4(){
    DNum object;
    QString curent_result="", result="1|1";

    object.addNum('1');
    object.setSpace();
    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_addNum_5(){
    DNum object;
    QString curent_result="", result="1|1";

    object.addNum('1');
    object.setSpace();
    object.addNum('0');
    object.addNum('1');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_addOper_1(){
    DNum object;
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

void t_dnum::test_addOper_2(){
    DNum object;
    QString curent_result="", result="+";

    object.addOper('+');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_addFunc_1(){
    DNum object;
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

void t_dnum::test_addFunc_2(){
    DNum object;
    QString curent_result="", result="Rev";

    object.addFunc("Rev");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_setSpace_1(){
    DNum object;
    QString result="incorect object";

    try{
        object.setSpace();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_dnum::test_setSpace_2(){
    DNum object;
    QString curent_result="", result="1|";

    object.addNum('1');
    object.setSpace();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_delLast_1(){
    DNum object;
    QString curent_result="", result="";

    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_delLast_2(){
    DNum object;
    QString curent_result="", result="";

    object.addFunc("Rev");
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_delLast_3(){
    DNum object;
    QString curent_result="", result="1|";

    object.addNum('1');
    object.setSpace();
    object.addNum('2');
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_delLast_4(){
    DNum object;
    QString curent_result="", result="1";

    object.addNum('1');
    object.setSpace();
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_delLast_5(){
    DNum object;
    QString curent_result="", result="1";

    object.addNum('1');
    object.addNum('2');
    object.delLast();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_changeZnak_1(){
    DNum object;
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

void t_dnum::test_changeZnak_2(){
    DNum object;
    QString curent_result_1="", curent_result_2="", result_1="(-2)", result_2="2";

    object.addNum('2');
    object.changeZnak();
    curent_result_1=object.getString();
    object.changeZnak();
    curent_result_2=object.getString();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
}

void t_dnum::test_clear(){
    DNum object;
    QString curent_result="", result="";

    object.addNum('1');
    object.clear();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_getString_1(){
    DNum object;
    QString curent_result="", result="";

    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_getString_2(){
    DNum object;
    QString curent_result="", result="2|2";

    object.setNum("-2","-2");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_getFirstNum_1(){
    DNum object;
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

void t_dnum::test_getFirstNum_2(){
    DNum object;
    int curent_result=0, result=2;

    object.addNum('2');
    curent_result=object.getFirstNum();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_getSecondNum_1(){
    DNum object;
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

void t_dnum::test_getSecondNum_2(){
    DNum object;
    int curent_result=0, result=1;

    object.addNum('1');
    object.setSpace();
    curent_result=object.getSecondNum();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_getSecondNum_3(){
    DNum object;
    int curent_result=0, result=2;

    object.addNum('1');
    object.setSpace();
    object.addNum('2');
    curent_result=object.getSecondNum();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_setNum_1(){
    DNum object;
    QString result="incorect first num";

    try {
        object.setNum("a","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_dnum::test_setNum_2(){
    DNum object;
    QString result="incorect second num";

    try {
        object.setNum("2","a");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_dnum::test_setNum_3(){
    DNum object;
    QString curent_result="", result="2|3";

    object.setNum("-2","-3");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_setNum_4(){
    DNum object;
    QString curent_result="", result="(-2|3)";

    object.setNum("2","-3");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_setNum_5(){
    DNum object;
    QString curent_result="", result="(-2|3)";

    object.setNum("-2","3");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_setNum_6(){
    DNum object;
    QString result="div 0";

    try {
        object.setNum("1","0");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_dnum::test_setNum_7(){
    DNum object;
    QString curent_result="", result="0";

    object.setNum("0","3");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_simplifyNum_1(){
    DNum object;
    QString curent_result="", result="2|3";

    object.setNum("2","3");
    object.simplifyNum();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_dnum::test_simplifyNum_2(){
    DNum object;
    QString curent_result="", result="1|2";

    object.setNum("2","4");
    object.simplifyNum();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(t_dnum)

#include "tst_t_dnum.moc"
