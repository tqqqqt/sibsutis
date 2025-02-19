#include <QtTest>

#include "../Converter_p1_p2/src/converter.h"

class t_converter : public QObject
{
    Q_OBJECT

public:
    t_converter();
    ~t_converter();

private slots:
    void test_convertFrom10_1();
    void test_convertFrom10_2();

    void test_convertTo10();

};

t_converter::t_converter(){ }
t_converter::~t_converter(){ }

void t_converter::test_convertFrom10_1()
{
    Converter converter;
    double input=-24.12;
    QString curent_result="", result="-18.1EB8";

    curent_result=QString::fromStdString(converter.convertFrom10(input,16,4));

    QCOMPARE(curent_result,result);
}

void t_converter::test_convertFrom10_2()
{
    Converter converter;
    double input=99999999999999;
    QString curent_result="", result="out of range";

    try{
        curent_result=QString::fromStdString(converter.convertFrom10(input,16,4));
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result);
    }
}

void t_converter::test_convertTo10()
{
    Converter converter;
    std::string input="-12.24";
    double curent_result=0, result=-18.140625;

    curent_result=converter.convertTo10(input,16);

    QCOMPARE(curent_result,result);
}

QTEST_APPLESS_MAIN(t_converter)

#include "tst_t_converter.moc"
