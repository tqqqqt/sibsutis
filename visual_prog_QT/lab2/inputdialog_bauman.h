#ifndef INPUTDIALOG_BAUMAN_H
#define INPUTDIALOG_BAUMAN_H

#include <QDialog>
#include <QLineEdit>

class InputDialog_Bauman : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* firstName;
    QLineEdit* lastName;
public:
    InputDialog_Bauman(QWidget* pwgt=0);

    QString FirstName() const{
        return firstName->text();
    }
    QString LastName() const{
        return lastName->text();
    }
};

#endif // INPUTDIALOG_BAUMAN_H
