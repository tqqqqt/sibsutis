#include "inputdialog_bauman.h"
#include <QLabel>
#include <QLayout>
#include <QString>
#include <QPushButton>

InputDialog_Bauman::InputDialog_Bauman(QWidget *pwgt): QDialog(pwgt)
{
    firstName=new QLineEdit;
    lastName=new QLineEdit;
    QLabel* firstNameLabel=new QLabel("&Имя");
    QLabel* lastNameLabel=new QLabel("&Фамилия");
    firstNameLabel->setBuddy(firstName);
    lastNameLabel->setBuddy(lastName);
    QPushButton* buttonOk=new QPushButton("&OK");
    QPushButton* buttonCancel=new QPushButton("&CANCEL");
    connect(buttonOk,SIGNAL(clicked()),SLOT(accept()));
    connect(buttonCancel,SIGNAL(clicked()),SLOT(reject()));

    QGridLayout* screnLayout=new QGridLayout;
    screnLayout->addWidget(firstNameLabel,0,0);
    screnLayout->addWidget(lastNameLabel,1,0);
    screnLayout->addWidget(firstName,0,1);
    screnLayout->addWidget(lastName,1,1);
    screnLayout->addWidget(buttonOk,2,0);
    screnLayout->addWidget(buttonCancel,2,1);
    setLayout(screnLayout);
}
