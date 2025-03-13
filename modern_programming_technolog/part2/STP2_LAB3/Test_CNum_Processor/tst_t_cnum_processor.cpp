#include <QtTest>

#include "../Multi-Calculator/src/cnum.h"
#include "../Multi-Calculator/src/cnum_processor.h"

class t_cnum_processor : public QObject
{
    Q_OBJECT

public:
    t_cnum_processor();
    ~t_cnum_processor();

private slots:
    void test_execute_1();
    void test_execute_2();
    void test_execute_3();
};

t_cnum_processor::t_cnum_processor(){ }
t_cnum_processor::~t_cnum_processor(){ }

void t_cnum_processor::test_execute_1()
{
    CNum_Processor object;
    QVector<Num*> arr(1,new CNum);
    QString result="incorect execute";

    arr[0]->addFunc("Rev");

    try{
        object.execute(arr);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_cnum_processor::test_execute_2()
{
    CNum_Processor object;
    QVector<Num*> arr(9);
    for(int i=0;i<9;++i) arr[i]=new CNum;
    CNum *num;
    QString curent_result="", result="10+i*0";

    num=static_cast<CNum*>(arr[0]);
    num->setNum("6","0");
    arr[1]->addFunc("Sqr");
    arr[2]->addOper('+');
    num=static_cast<CNum*>(arr[3]);
    num->setNum("2","0");
    arr[4]->addFunc("Sqr");
    arr[5]->addOper('/');
    num=static_cast<CNum*>(arr[6]);
    num->setNum("10","0");
    arr[7]->addOper('+');
    arr[8]->addNum('6');

    object.execute(arr);
    curent_result=arr[0]->getString();

    QCOMPARE(curent_result,result);
}

void t_cnum_processor::test_execute_3()
{
    CNum_Processor object;
    QVector<Num*> arr(3);
    for(int i=0;i<3;++i) arr[i]=new CNum;
    CNum *num;
    QString curent_result_1="", curent_result_2="", result_1="5+i*5", result_2="8+i*8";

    num=static_cast<CNum*>(arr[0]);
    num->setNum("2","2");
    arr[1]->addOper('+');
    num=static_cast<CNum*>(arr[2]);
    num->setNum("3","3");

    object.execute(arr);
    curent_result_1=arr[0]->getString();
    object.execute(arr);
    curent_result_2=arr[0]->getString();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
}

QTEST_APPLESS_MAIN(t_cnum_processor)

#include "tst_t_cnum_processor.moc"
