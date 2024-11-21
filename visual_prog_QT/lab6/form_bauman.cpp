#include "form_bauman.h"
#include "ui_form_bauman.h"
#include <QFileDialog>
#include "qtextdocumentwriter.h"

form_bauman::form_bauman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::form_bauman)
{
    ui->setupUi(this);
}

void form_bauman::RecieveData(QString str){
    QStringList listStr=str.split("*");
    ui->textEdit->setText(listStr.at(1)+"\n"+listStr.at(0));
    if(listStr.size()>1){
        QImage image(listStr.at(0));
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

form_bauman::~form_bauman()
{
    delete ui;
}

void form_bauman::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text()=="Reset") ui->textEdit->clear();
    else if(button->text()=="Save"){
        QString fileName=QFileDialog::getSaveFileName(0,"Save file","","");
        if(fileName.isEmpty()==false){
            QTextDocumentWriter textWriter;
            textWriter.setFileName(fileName);
            textWriter.write(ui->textEdit->document());
        }
    }
    else if(button->text()=="Open"){
        QString fileName=QFileDialog::getOpenFileName(0,"Open file","","");
        if(fileName.isEmpty()==false){
            QFile file(fileName);
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->textEdit->setPlainText(file.readAll());
            QStringList textList=ui->textEdit->toPlainText().split("\n");
            QImage image(textList.at(5));
            ui->label->setPixmap(QPixmap::fromImage(image));
        }
    }
}
