#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    my_translator=new translator();

    this->connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(addRule()));
    this->connect(ui->pushButton_delete,SIGNAL(clicked()),this,SLOT(deleteRule()));
    this->connect(ui->pushButton_translate,SIGNAL(clicked()),this,SLOT(translateChain()));

    this->connect(ui->action_load,SIGNAL(triggered()),this,SLOT(loadFile()));
    this->connect(ui->action_clear,SIGNAL(triggered()),this,SLOT(clearAll()));
}

MainWindow::~MainWindow()
{
    delete my_translator;
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
        my_translator->addRule(temp.toStdString());
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
        my_translator->deleteRule(rules[ui->listWidget_rule->currentRow()].toStdString());
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

void MainWindow::translateChain(){
    QString result="";
    try{
        result=QString::fromStdString(my_translator->translateChain(ui->lineEdit_chain->text().toStdString()));
    }
    catch(std::exception &exp){
        showError(exp.what());
        return;
    }
    ui->textEdit_chain->clear();
    ui->textEdit_chain->setText(result);
}

void MainWindow::loadFile(){
    QString str=QFileDialog::getOpenFileName(nullptr,"Open file","","Text (*.txt)");
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
        clearAll();
        showError(exp.what());
    }
}

void MainWindow::clearAll(){
    ui->listWidget_rule->clear();
    ui->lineEdit_rule->clear();
    ui->lineEdit_chain->clear();
    ui->textEdit_chain->clear();
    rules.clear();
    my_translator->clearTranslator();
}
