#include "refwindow.h"
#include "ui_refwindow.h"

RefWindow::RefWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RefWindow)
{
    ui->setupUi(this);

    ui->textEdit->setText(text);

    this->connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(closeRef()));
}

RefWindow::~RefWindow()
{
    delete ui;
}

void RefWindow::closeRef(){
    this->close();
}
