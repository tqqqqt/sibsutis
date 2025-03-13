#include <QtTest>

#include "../P-Num_Calculator/src/pnum.h"
#include "../P-Num_Calculator/src/converter.h"
#include "../P-Num_Calculator/src/processor.h"

class t_processor : public QObject
{
    Q_OBJECT

public:
    t_processor();
    ~t_processor();

private slots:
    void test_changeSystem();

    void test_execute_1();
    void test_execute_2();
    void test_execute_3();
};

t_processor::t_processor(){ }
t_processor::~t_processor(){ }

void t_processor::test_changeSystem()
{
    Processor object;
    QVector<PNum> arr(3);
    QString curent_num_1="", curent_num_2="", result_num_1="10", result_num_2="(-11)";
    QString curent_oper="", result_oper="+";

    arr[0].addNum('2');
    arr[1].addOper('+');
    arr[2].addNum('3');
    arr[2].changeZnak();

    try{
        object.changeSystem(arr,10,2);
        curent_num_1=arr[0].getString();
        curent_oper=arr[1].getString();
        curent_num_2=arr[2].getString();
    }
    catch(std::exception){
        QCOMPARE(1,0);
    }

    QCOMPARE(curent_num_1,result_num_1);
    QCOMPARE(curent_oper,result_oper);
    QCOMPARE(curent_num_2,result_num_2);
}

void t_processor::test_execute_1(){
    Processor object;
    QVector<PNum> arr(1);
    QString result="incorect execute";

    arr[0].addFunc("Rev");

    try{
        object.execute(arr,10);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_processor::test_execute_2(){
    Processor object;
    QVector<PNum> arr(9);
    QString curent_result="", result="10";

    arr[0].setNum("6");
    arr[1].addFunc("Sqr");
    arr[2].addOper('+');
    arr[3].setNum("2");
    arr[4].addFunc("Sqr");
    arr[5].addOper('/');
    arr[6].setNum("10");
    arr[7].addOper('+');
    arr[8].setNum("6");

    object.execute(arr,10);
    curent_result=arr[0].getString();

    QCOMPARE(curent_result,result);
}

void t_processor::test_execute_3(){
    Processor object;
    QVector<PNum> arr(3);
    QString curent_result_1="", curent_result_2="", result_1="5", result_2="8";

    arr[0].setNum("2");
    arr[1].addOper('+');
    arr[2].setNum("3");

    object.execute(arr,10);
    curent_result_1=arr[0].getString();
    object.execute(arr,10);
    curent_result_2=arr[0].getString();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
}

QTEST_APPLESS_MAIN(t_processor)

#include "tst_t_processor.moc"
