#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myForm=new form_bauman();
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(OnButtonSend()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(LoadImageClick()));
    connect(this,SIGNAL(SendData(QString)),myForm,SLOT(RecieveData(QString)));
    connect(ui->pushButton_2,SIGNAL(clicked()),myForm,SLOT(show()));
    connect(ui->lineEdit,SIGNAL(textEdited(QString)),this,SLOT(AvalibleButton()));
    connect(ui->lineEdit_2,SIGNAL(textEdited(QString)),this,SLOT(AvalibleButton()));
    connect(ui->lineEdit_3,SIGNAL(textEdited(QString)),this,SLOT(AvalibleButton()));
    connect(ui->lineEdit_4,SIGNAL(textEdited(QString)),this,SLOT(AvalibleButton()));
    ui->radioButton->setChecked(true);
}

void MainWindow::LoadImageClick(){
    QString fileName = QFileDialog::getOpenFileName(0, "Выберети изображение","");
    if(fileName.isEmpty()==false){
        ui->lineEdit_4->setText(fileName);
        QImage image1(fileName);
        ui->label_4->setPixmap(QPixmap::fromImage(image1));
    }
}

void MainWindow::OnButtonSend(){
    QString str=ui->lineEdit_4->text()+"*"+ui->lineEdit->text()+"\n"+ui->lineEdit_2->text()+"\n"+ui->dateEdit->text()+"\n"+ui->lineEdit_3->text();
    if(ui->radioButton->isChecked()==true) str+="\nпол: мужской";
    else str+="\nпол: женский";
    emit SendData(str);
}

void MainWindow::AvalibleButton(){
    if(!ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() && !ui->lineEdit_4->text().isEmpty()){
        ui->pushButton_2->setEnabled(true);
    }
    else{
        ui->pushButton_2->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
