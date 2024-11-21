#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_avtomat=new avtomat();
    curent_alphabet="";

    connect(ui->push_button_add_rule,SIGNAL(clicked()),this,SLOT(addRule()));
    connect(ui->push_button_delete_rule,SIGNAL(clicked()),this,SLOT(deleteRule()));
    connect(ui->push_button_chain,SIGNAL(clicked()),this,SLOT(startCheck()));

    connect(ui->action_default,SIGNAL(triggered()),this,SLOT(setDefault()));
    connect(ui->action_read_file,SIGNAL(triggered()),this,SLOT(readFile()));
    connect(ui->action_clear,SIGNAL(triggered()),this,SLOT(clearAvtomat()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showError(const char* message){
    QMessageBox message_box;
    message_box.critical(this,"Error",message);
    message_box.setFixedSize(500,200);
}

void MainWindow::addRule(){
    try {
        my_avtomat->addRule(ui->line_rule->text().toStdString());
        curent_alphabet=QString::fromStdString(my_avtomat->getAlphabet());
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    rules_mas.push_back(ui->line_rule->text());
    ui->list_rule->insertItem(rules_mas.size(),rules_mas.back());
    ui->line_rule->setText("");
    ui->line_alphabet->setText(curent_alphabet);
}

void MainWindow::startCheck(){
    if(ui->line_chain->text().length()==0){
        showError("Length chain equal 0.");
        return;
    }
    QString result="";
    try {
        std::string temp=my_avtomat->work(ui->line_chain->text().toStdString());
        result=QString::fromStdString(temp);
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    ui->text_chain->clear();
    ui->text_chain->setText(result);
}

void MainWindow::deleteRule(){
    if(ui->list_rule->currentRow()<0) return;
    try{
        my_avtomat->deleteRule(rules_mas[ui->list_rule->currentRow()].toStdString());
        curent_alphabet=QString::fromStdString(my_avtomat->getAlphabet());
    }
    catch(std::exception &exp){
        showError(exp.what());
        return;
    }
    rules_mas.erase(rules_mas.begin()+ui->list_rule->currentRow());
    ui->list_rule->takeItem(ui->list_rule->currentRow());
    ui->list_rule->setCurrentRow(-1);
    ui->line_alphabet->setText(curent_alphabet);
}

void MainWindow::setDefault(){
    clearAvtomat();
    ui->line_rule->setText("p@=(0:q)(1:p)");
    addRule();
    ui->line_rule->setText("q=(0:r)(1:p)");
    addRule();
    ui->line_rule->setText("r^=(0:r)(1:r)");
    addRule();
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
        while(file_in>>temp){
            my_avtomat->addRule(temp);
            rules_mas.push_back(QString::fromStdString(temp));
        }
    }
    catch(std::exception &exp){
        rules_mas.clear();
        showError(exp.what());
    }
    ui->list_rule->addItems(QStringList::fromVector(rules_mas));
}

void MainWindow::clearAvtomat(){
    ui->line_rule->clear();
    ui->list_rule->clear();
    ui->line_chain->clear();
    ui->text_chain->clear();
    ui->line_alphabet->clear();
    rules_mas.clear();
    curent_alphabet="";
    my_avtomat->clearRule();
}
