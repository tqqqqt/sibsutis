#include <QtTest>

#include "../Converter_p1_p2/src/info.h"

class t_info : public QObject
{
    Q_OBJECT

public:
    t_info();
    ~t_info();

private slots:
    void test_getText();

};

t_info::t_info(){ }
t_info::~t_info(){ }

void t_info::test_getText()
{
    Info info;
    QString curent_text="", result="Конвертор \n Кнопка BS отвечает за удаление последнего символа. \n Кнопка CE отвечает за очистку поля.";

    curent_text=info.getText();

    QCOMPARE(curent_text,result);
}

QTEST_APPLESS_MAIN(t_info)

#include "tst_t_info.moc"
