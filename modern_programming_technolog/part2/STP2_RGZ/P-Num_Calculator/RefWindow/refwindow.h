#ifndef REFWINDOW_H
#define REFWINDOW_H

#include <QDialog>

namespace Ui {
class RefWindow;
}

class RefWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RefWindow(QWidget *parent = nullptr);
    ~RefWindow();

private:
    Ui::RefWindow *ui;

    const QString text="Тема: Калькулятор p-ичных чисел\n"
                       "\n"
                       "Вариант: 2\n"
                       "Тип числа: действительное в системе счисления с основанием от 2 до 16\n"
                       "Прецеденты: 1-6\n"
                       "Операнды могут браться из: памяти-Да, буфера обмена-нет\n"
                       "История: нет\n"
                       "Настройки: да\n\n"
                       "Выполнил: студент группы ИП-111\n"
                       "\t Бауман Сергей";

private slots:
    void windowClose();
};

#endif // REFWINDOW_H
