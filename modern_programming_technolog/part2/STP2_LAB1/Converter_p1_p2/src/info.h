#ifndef INFO_H
#define INFO_H

#include <QString>

class Info
{
private:
    const QString text="Конвертор \n Кнопка BS отвечает за удаление последнего символа. \n Кнопка CE отвечает за очистку поля.";

public:
    Info();

    QString getText();
};

#endif // INFO_H
