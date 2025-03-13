#ifndef REFWINDOW_H
#define REFWINDOW_H

#include <QDialog>
#include <QString>

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
    const QString text="Универсальный калькулятор с памятью.\n"
                       "Работает с тремя режимами:\n"
                       " * p-ичные числа\n"
                       " * дроби\n"
                       " * комплексные числа";

private slots:
    void closeRef();
};

#endif // REFWINDOW_H
