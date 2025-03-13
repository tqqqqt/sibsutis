#include <QtTest>

#include "../Multi-Calculator/src/dnum.h"
#include "../Multi-Calculator/src/dnum_processor.h"

class t_dnum_processor : public QObject
{
    Q_OBJECT

public:
    t_dnum_processor();
    ~t_dnum_processor();

private slots:
    void test_execute_1();
    void test_execute_2();
    void test_execute_3();
};

t_dnum_processor::t_dnum_processor(){ }
t_dnum_processor::~t_dnum_processor(){ }

void t_dnum_processor::test_execute_1()
{
    DNum_Processor object;
    QVector<Num*> arr(1,new DNum);
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

void t_dnum_processor::test_execute_2()
{
    DNum_Processor object;
    QVector<Num*> arr(9);
    for(int i=0;i<9;++i) arr[i]=new DNum;
    DNum *num;
    QString curent_result="", result="10|1";

    num=static_cast<DNum*>(arr[0]);
    num->setNum("6","1");
    arr[1]->addFunc("Sqr");
    arr[2]->addOper('+');
    num=static_cast<DNum*>(arr[3]);
    num->setNum("2","1");
    arr[4]->addFunc("Sqr");
    arr[5]->addOper('/');
    num=static_cast<DNum*>(arr[6]);
    num->setNum("10","1");
    arr[7]->addOper('+');
    arr[8]->addNum('6');

    object.execute(arr);
    curent_result=arr[0]->getString();

    QCOMPARE(curent_result,result);
}

void t_dnum_processor::test_execute_3()
{
    DNum_Processor object;
    QVector<Num*> arr(3);
    for(int i=0;i<3;++i) arr[i]=new DNum;
    DNum *num;
    QString curent_result_1="", curent_result_2="", result_1="1|6", result_2="1|18";

    num=static_cast<DNum*>(arr[0]);
    num->setNum("1","2");
    arr[1]->addOper('*');
    num=static_cast<DNum*>(arr[2]);
    num->setNum("1","3");

    object.execute(arr);
    curent_result_1=arr[0]->getString();
    object.execute(arr);
    curent_result_2=arr[0]->getString();

    QCOMPARE(curent_result_1,result_1);
    QCOMPARE(curent_result_2,result_2);
}

QTEST_APPLESS_MAIN(t_dnum_processor)

#include "tst_t_dnum_processor.moc"
