#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    ui->textEdit->setText(text);

    this->connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(closeWindow()));
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::closeWindow(){
    this->close();
}
