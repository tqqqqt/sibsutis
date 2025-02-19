#include <QtTest>

#include "../Converter_p1_p2/src/history.h"

class t_history : public QObject
{
    Q_OBJECT

public:
    t_history();
    ~t_history();

private slots:
    void test_at_1();
    void test_at_2();

    void test_addRecord();

    void test_clear();

    void test_count();

};

t_history::t_history(){ }
t_history::~t_history(){ }

void t_history::test_at_1()
{
    History history;
    int curent_p1=0, curent_p2=0;
    QString n1="", n2="";
    int result_p1=10, result_p2=16;
    QString result_n1="144", result_n2="90";

    history.addRecord(10,10,"","");
    history.addRecord(result_p1,result_p2,result_n1,result_n2);

    curent_p1=history.at(1).p_1;
    curent_p2=history.at(1).p_2;
    n1=history.at(1).number_1;
    n2=history.at(1).number_2;

    QCOMPARE(curent_p1,result_p1);
    QCOMPARE(curent_p2,result_p2);
    QCOMPARE(n1,result_n1);
    QCOMPARE(n2,result_n2);
}

void t_history::test_at_2()
{
    History history;
    QString result="incorect index";

    try{
        history.at(9);
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }

}

void t_history::test_addRecord()
{
    History history;
    int curent_p1=0, curent_p2=0;
    QString n1="", n2="";
    int result_p1=10, result_p2=16;
    QString result_n1="144", result_n2="90";

    history.addRecord(result_p1,result_p2,result_n1,result_n2);

    curent_p1=history.at(0).p_1;
    curent_p2=history.at(0).p_2;
    n1=history.at(0).number_1;
    n2=history.at(0).number_2;

    QCOMPARE(curent_p1,result_p1);
    QCOMPARE(curent_p2,result_p2);
    QCOMPARE(n1,result_n1);
    QCOMPARE(n2,result_n2);
}

void t_history::test_clear()
{
    History history;
    int curent_count=0, result_count=0;

    history.addRecord(10,10,"","");

    history.clear();

    curent_count=history.count();

    QCOMPARE(curent_count,result_count);
}

void t_history::test_count()
{
    History history;
    int curent_count=0, result_count=2;

    history.addRecord(10,10,"","");
    history.addRecord(10,10,"","");

    curent_count=history.count();

    QCOMPARE(curent_count,result_count);
}

QTEST_APPLESS_MAIN(t_history)

#include "tst_t_history.moc"
