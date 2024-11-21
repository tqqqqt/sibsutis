#ifndef STARTDIALOG_BAUMAN_H
#define STARTDIALOG_BAUMAN_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "inputdialog_bauman.h"

class StartDialog_Bauman : public QPushButton{
    Q_OBJECT
public:
        StartDialog_Bauman(QWidget* pwgt=0 );
public slots:
    void slotButtonClicked(){
        InputDialog_Bauman* inputDialogWindow=new InputDialog_Bauman;
        if(inputDialogWindow->exec()==QDialog::Accepted){
            QMessageBox::information(0,"Ваша информация: ","Имя: " +inputDialogWindow->FirstName() + "\nФамилия: " +inputDialogWindow->LastName());
        }
        delete inputDialogWindow;
    }
};

#endif // STARTDIALOG_BAUMAN_H
