#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    my_automat=new automat();

    this->connect(ui->pushButton_add_rule,SIGNAL(clicked()),this,SLOT(addRule()));
    this->connect(ui->pushButton_del_rule,SIGNAL(clicked()),this,SLOT(deleteRule()));
    this->connect(ui->pushButton_start,SIGNAL(clicked()),this,SLOT(startCheck()));

    this->connect(ui->action_load,SIGNAL(triggered()),this,SLOT(readFile()));
    this->connect(ui->action_clear,SIGNAL(triggered()),this,SLOT(clearProg()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showError(const char* _error){
    QMessageBox message_box;
    message_box.critical(this,"Error",_error);
    message_box.setFixedSize(500,200);
}

void MainWindow::addRule(){
    QString temp=ui->lineEdit_rule->text();
    try {
        my_automat->addRule(temp.toStdString());
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    rules.push_back(temp);
    ui->listWidget_rule->clear();
    ui->listWidget_rule->addItems(QStringList::fromVector(rules));
    ui->lineEdit_rule->clear();
}

void MainWindow::deleteRule(){
    if(ui->listWidget_rule->currentRow()<0) return;
    try {
        my_automat->deleteRule(rules[ui->listWidget_rule->currentRow()].toStdString());
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    rules.erase(rules.begin()+ui->listWidget_rule->currentRow());
    ui->listWidget_rule->takeItem(ui->listWidget_rule->currentRow());
    ui->listWidget_rule->setCurrentRow(-1);
    ui->lineEdit_rule->clear();
}

void MainWindow::startCheck(){
    QString result="";
    try {
        result=QString::fromStdString(my_automat->work(ui->lineEdit_chain->text().toStdString()));
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    ui->textEdit_result->setText(result);
}

void MainWindow::readFile(){
    QString str=QFileDialog::getOpenFileName(0,"Open file","","Text (*.txt)");
    if(str.isEmpty()){
        showError("Invalid file.");
        return;
    }
    std::ifstream file_in(str.toStdString());
    std::string temp="";
    try{
        while(std::getline(file_in,temp)){
            ui->lineEdit_rule->setText(QString::fromStdString(temp));
            addRule();
        }
    }
    catch(std::exception &exp){
        clearProg();
        showError(exp.what());
    }
}

void MainWindow::clearProg(){
    ui->listWidget_rule->clear();
    ui->lineEdit_rule->clear();
    ui->lineEdit_chain->clear();
    ui->textEdit_result->clear();
    rules.clear();
    my_automat->clearAutomat();
}
