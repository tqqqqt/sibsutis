#include <QtTest>

#include "../P-Num_Calculator/src/pnum.h"
#include "../P-Num_Calculator/src/memory.h"

class t_memory : public QObject
{
    Q_OBJECT

public:
    t_memory();
    ~t_memory();

private slots:
    void test_clear();

    void test_save();

    void test_copy_1();
    void test_copy_2();

    void test_curentStatus();
};

t_memory::t_memory(){ }
t_memory::~t_memory(){ }

void t_memory::test_clear()
{
    Memory object;
    PNum num;
    Memory::Memory_status curent_status, result_status=Memory::Memory_status::Off;
    num.addNum('1');

    object.save(num);
    object.clear();
    curent_status=object.curentStatus();

    QCOMPARE(curent_status,result_status);
}

void t_memory::test_save(){
    Memory object;
    PNum num;
    Memory::Memory_status curent_status, result_status=Memory::Memory_status::On;
    QString curent_num="", result_num="1";
    num.addNum('1');

    object.save(num);
    curent_status=object.curentStatus();
    curent_num=object.copy().getString();

    QCOMPARE(curent_status,result_status);
    QCOMPARE(curent_num,result_num);
}

void t_memory::test_copy_1(){
    Memory object;
    QString result="memory off";
    PNum temp_num;

    try{
        temp_num=object.copy();
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_memory::test_copy_2(){
    Memory object;
    PNum num;
    Memory::Memory_status curent_status_1, curent_status_2, result_status_1=Memory::Memory_status::Off, result_status_2=Memory::Memory_status::On;
    QString curent_num="", result_num="12";
    num.addNum('1');
    num.addNum('2');

    curent_status_1=object.curentStatus();
    object.save(num);
    curent_status_2=object.curentStatus();
    curent_num=object.copy().getString();

    QCOMPARE(curent_status_1,result_status_1);
    QCOMPARE(curent_status_2,result_status_2);
    QCOMPARE(curent_num,result_num);
}

void t_memory::test_curentStatus(){
    Memory object;
    Memory::Memory_status curent_status, result_status=Memory::Memory_status::Off;

    curent_status=object.curentStatus();

    QCOMPARE(curent_status,result_status);
}

QTEST_APPLESS_MAIN(t_memory)

#include "tst_t_memory.moc"
