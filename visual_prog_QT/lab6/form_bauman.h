#ifndef FORM_BAUMAN_H
#define FORM_BAUMAN_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class form_bauman;
}

class form_bauman : public QWidget
{
    Q_OBJECT

public:
    explicit form_bauman(QWidget *parent = 0);
    ~form_bauman();

private:
    Ui::form_bauman *ui;

public slots:
    void RecieveData(QString str);
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // FORM_BAUMAN_H
