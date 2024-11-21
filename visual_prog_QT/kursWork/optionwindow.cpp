#include "optionwindow.h"
#include "ui_optionwindow.h"

OptionWindow::OptionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Option window");

    connect(ui->checkBox,SIGNAL(clicked()),this,SLOT(checkBox1()));
    connect(ui->checkBox_2,SIGNAL(clicked()),this,SLOT(checkBox2()));
    connect(ui->checkBox_3,SIGNAL(clicked()),this,SLOT(checkBox3()));
}

OptionWindow::OptionWindow(int tempTheme, bool helpWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Option window");

    connect(ui->checkBox,SIGNAL(clicked()),this,SLOT(checkBox1()));
    connect(ui->checkBox_2,SIGNAL(clicked()),this,SLOT(checkBox2()));
    connect(ui->checkBox_3,SIGNAL(clicked()),this,SLOT(checkBox3()));

    if(tempTheme==2){
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setEnabled(true);
        ui->checkBox_2->setChecked(true);
        ui->checkBox->setEnabled(false);
        theme="Black";
    }
    else if(tempTheme==1){
        ui->checkBox->setEnabled(true);
        ui->checkBox->setChecked(true);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_2->setEnabled(false);
        theme="white";
    }
    if(helpWindow==true){
        ui->checkBox_3->setChecked(true);
        helpWindow=true;
    }
    else{
        ui->checkBox_3->setChecked(false);
        helpWindow=false;
    }
}

OptionWindow::~OptionWindow()
{
    delete ui;
}

void OptionWindow::on_buttonBox_accepted()
{
    if(tempWindow==0) emit AcceptSetings(theme,help);
    else if(tempWindow==1) emit AcceptAlbumSetings(theme,help);
}

void OptionWindow::on_buttonBox_rejected()
{
    if(theme=="white"){
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setEnabled(true);
        ui->checkBox_2->setChecked(true);
        ui->checkBox->setEnabled(false);
    }
    else if(theme=="Black"){
        ui->checkBox->setEnabled(true);
        ui->checkBox->setChecked(true);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_2->setEnabled(false);
    }
    this->hide();
}

void OptionWindow::checkBox1(){
    if(ui->checkBox->isChecked()==true){
        ui->checkBox_2->setEnabled(false);
        theme="White";
    }
    else ui->checkBox_2->setEnabled(true);
}

void OptionWindow::checkBox2(){
    if(ui->checkBox_2->isChecked()==true){
        ui->checkBox->setEnabled(false);
        theme="Black";
    }
    else ui->checkBox->setEnabled(true);
}

void OptionWindow::checkBox3(){
    if(ui->checkBox_3->isChecked()==true) help=true;
    else help=false;
}

void OptionWindow::chendeWindow(){
    tempWindow=1;
}
