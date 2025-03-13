#include <QtTest>

#include "../Multi-Calculator/src/pnum.h"

class t_pnum : public QObject
{
    Q_OBJECT

public:
    t_pnum();
    ~t_pnum();

private slots:
    void test_addNum_1();
    void test_addNum_2();
    void test_addNum_3();
    void test_addNum_4();

    void test_addOper_1();
    void test_addOper_2();

    void test_addFunc_1();
    void test_addFunc_2();

    void test_changeZnak_1();
    void test_changeZnak_2();
    void test_changeZnak_3();

    void test_addDot_1();
    void test_addDot_2();
    void test_addDot_3();

    void test_delLast_1();
    void test_delLast_2();
    void test_delLast_3();
    void test_delLast_4();
    void test_delLast_5();

    void test_getType();

    void test_clear();

    void test_getString();

    void test_getNum_1();
    void test_getNum_2();
    void test_getNum_3();

    void test_setNum_1();
    void test_setNum_2();
    void test_setNum_3();
};

t_pnum::t_pnum(){ }
t_pnum::~t_pnum(){ }

void t_pnum::test_addNum_1(){
    PNum object;
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

void t_pnum::test_addNum_2(){
    PNum object;
    QString curent_num="", result="1";

    object.addNum('0');
    object.addNum('1');
    curent_num=object.getString();

    QCOMPARE(curent_num,result);
}

void t_pnum::test_addNum_3(){
    PNum object;
    QString curent_num="", result="(-23)";

    object.addNum('2');
    object.changeZnak();
    object.addNum('3');
    curent_num=object.getString();

    QCOMPARE(curent_num,result);
}

void t_pnum::test_addNum_4(){
    PNum object;
    QString curent_num="", result="2";

    object.addNum('2');
    curent_num=object.getString();

    QCOMPARE(curent_num,result);
}

void t_pnum::test_addOper_1(){
    PNum object;
    QString result="incorect object";

    object.addNum('1');

    try {
        object.addOper('+');
        QCOMPARE(1,0);
    }
    catch (std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum::test_addOper_2(){
    PNum object;
    QString curent_result="", result="+";

    object.addOper('+');
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_addFunc_1(){
    PNum object;
    QString result="incorect object";

    object.addNum('1');

    try {
        object.addFunc("Rev");
        QCOMPARE(1,0);
    }
    catch (std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum::test_addFunc_2(){
    PNum object;
    QString curent_result="", result="Rev";

    object.addFunc("Rev");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_changeZnak_1(){
    PNum object;
    QString result="incorect object";

    object.addOper('+');

    try {
        object.changeZnak();
        QCOMPARE(1,0);
    }
    catch (std::exception& exp) {
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum::test_changeZnak_2(){
    PNum object;
    QString curent_result="", result="12";

    object.setNum("-12");
    object.changeZnak();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_changeZnak_3(){
    PNum object;
    QString curent_result="", result="(-12)";

    object.setNum("12");
    object.changeZnak();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_addDot_1(){
    PNum object;
    QString curent_result="", result="12.2";

    object.setNum("12.2");
    object.addDot();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_addDot_2(){
    PNum object;
    QString curent_result="", result="(-12.)";

    object.setNum("-12");
    object.addDot();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_addDot_3(){
    PNum object;
    QString curent_result="", result="12.";

    object.setNum("12");
    object.addDot();
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_delLast_1(){
    PNum object;
    QString curent_string="", result="";

    object.delLast();
    curent_string=object.getString();

    QCOMPARE(curent_string,result);
}

void t_pnum::test_delLast_2(){
    PNum object;
    QString curent_string="", result="";

    object.addFunc("Rev");
    object.delLast();
    curent_string=object.getString();

    QCOMPARE(curent_string,result);
}

void t_pnum::test_delLast_3(){
    PNum object;
    QString curent_string="", result="(-12)";

    object.setNum("-12.");
    object.delLast();
    curent_string=object.getString();

    QCOMPARE(curent_string,result);
}

void t_pnum::test_delLast_4(){
    PNum object;
    QString curent_string="", result="1";

    object.setNum("12");
    object.delLast();
    curent_string=object.getString();

    QCOMPARE(curent_string,result);
}

void t_pnum::test_delLast_5(){
    PNum object;
    QString curent_string="", result="";

    object.setNum("1");
    object.delLast();
    curent_string=object.getString();

    QCOMPARE(curent_string,result);
}

void t_pnum::test_getType(){
    PNum object;
    PNum::Object_type curent_result_1, curent_result_2, curent_result_3;
    PNum::Object_type result_1=PNum::Object_type::None, result_2=PNum::Object_type::Num, result_3=PNum::Object_type::Operator;

    curent_result_1=object.getType();

    object.addNum('1');
    curent_result_2=object.getType();
    object.clear();

    object.addOper('+');
    curent_result_3=object.getType();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
    QCOMPARE(curent_result_3,result_3);
}

void t_pnum::test_clear(){
    PNum object;
    QString curent_result="", result="";
    PNum::Object_type curent_type, result_type=PNum::Object_type::None;

    object.setNum("12");
    object.clear();
    curent_result=object.getString();
    curent_type=object.getType();

    QCOMPARE(curent_result,result);
    QCOMPARE(curent_type,result_type);
}

void t_pnum::test_getString(){
    PNum object;
    QString curent_result="", result="12";

    object.setNum("12");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_getNum_1(){
    PNum object;
    QString curent_result="", result="incorect object";

    try{
        curent_result=object.getNum();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum::test_getNum_2(){
    PNum object;
    QString curent_result="", result="12";

    object.setNum("12");
    curent_result=object.getNum();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_getNum_3(){
    PNum object;
    QString curent_result="", result="-23";

    object.setNum("-23");
    curent_result=object.getNum();

    QCOMPARE(curent_result,result);
}

void t_pnum::test_setNum_1(){
    PNum object;
    QString result="incorect num";

    try{
        object.setNum("Hello");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum::test_setNum_2(){
    PNum object;
    QString result="incorect num";

    try{
        object.setNum("12..");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum::test_setNum_3(){
    PNum object;
    QString curent_result="", result="(-123)";

    object.setNum("-123");
    curent_result=object.getString();

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(t_pnum)

#include "tst_t_pnum.moc"
