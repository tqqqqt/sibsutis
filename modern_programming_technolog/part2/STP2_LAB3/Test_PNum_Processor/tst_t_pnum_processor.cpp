#include <QtTest>

#include "../Multi-Calculator/src/pnum.h"
#include "../Multi-Calculator/src/pnum_converter.h"
#include "../Multi-Calculator/src/pnum_processor.h"

class t_pnum_processor : public QObject
{
    Q_OBJECT

public:
    t_pnum_processor();
    ~t_pnum_processor();

private slots:
    void test_changeSystem();

    void test_execute_1();
    void test_execute_2();
    void test_execute_3();
};

t_pnum_processor::t_pnum_processor(){ }
t_pnum_processor::~t_pnum_processor(){ }

void t_pnum_processor::test_changeSystem()
{
    PNum_Processor object;
    QVector<Num*> arr(3);
    for(int i=0;i<3;++i) arr[i]=new PNum;
    QString curent_num_1="", curent_num_2="", result_num_1="10", result_num_2="(-11)";
    QString curent_oper="", result_oper="+";

    arr[0]->addNum('2');
    arr[1]->addOper('+');
    arr[2]->addNum('3');
    arr[2]->changeZnak();

    try{
        object.changeSystem(arr,10,2);
        curent_num_1=arr[0]->getString();
        curent_oper=arr[1]->getString();
        curent_num_2=arr[2]->getString();
    }
    catch(std::exception){
        QCOMPARE(1,0);
    }

    QCOMPARE(curent_num_1,result_num_1);
    QCOMPARE(curent_oper,result_oper);
    QCOMPARE(curent_num_2,result_num_2);
}

void t_pnum_processor::test_execute_1(){
    PNum_Processor object;
    QVector<Num*> arr(1,new PNum);
    QString result="incorect execute";

    arr[0]->addFunc("Rev");

    try{
        object.setSystem(10);
        object.execute(arr);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_pnum_processor::test_execute_2(){
    PNum_Processor object;
    QVector<Num*> arr(9);
    for(int i=0;i<9;++i) arr[i]=new PNum;
    QString curent_result="", result="10";

    arr[0]->addNum('6');
    arr[1]->addFunc("Sqr");
    arr[2]->addOper('+');
    arr[3]->addNum('2');
    arr[4]->addFunc("Sqr");
    arr[5]->addOper('/');
    arr[6]->addNum('1');
    arr[6]->addNum('0');
    arr[7]->addOper('+');
    arr[8]->addNum('6');

    object.setSystem(10);
    object.execute(arr);
    curent_result=arr[0]->getString();

    QCOMPARE(curent_result,result);
}

void t_pnum_processor::test_execute_3(){
    PNum_Processor object;
    QVector<Num*> arr(3);
    for(int i=0;i<3;++i) arr[i]=new PNum;
    QString curent_result_1="", curent_result_2="", result_1="5", result_2="8";

    arr[0]->addNum('2');
    arr[1]->addOper('+');
    arr[2]->addNum('3');

    object.setSystem(10);
    object.execute(arr);
    curent_result_1=arr[0]->getString();
    object.execute(arr);
    curent_result_2=arr[0]->getString();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
}

QTEST_APPLESS_MAIN(t_pnum_processor)

#include "tst_t_pnum_processor.moc"
