#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    automat=new DKAutomat();

    this->connect(ui->pushButton_gener_dka,SIGNAL(clicked()),this,SLOT(generateDKA()));
    this->connect(ui->pushButton_table,SIGNAL(clicked()),this,SLOT(showTable()));
    this->connect(ui->pushButton_graph,SIGNAL(clicked()),this,SLOT(showGraph()));
    this->connect(ui->pushButton_check_chain,SIGNAL(clicked()),this,SLOT(checkChain()));

    this->connect(ui->action_save_automat,SIGNAL(triggered()),this,SLOT(saveDKA()));
    this->connect(ui->action_save_check,SIGNAL(triggered()),this,SLOT(saveCheck()));
    this->connect(ui->action_load,SIGNAL(triggered()),this,SLOT(loadFile()));
    this->connect(ui->action_clear,SIGNAL(triggered()),this,SLOT(clearAll()));
    this->connect(ui->action_author,&QAction::triggered,[this]{ showInfo(1); });
    this->connect(ui->action_tema,&QAction::triggered,[this]{ showInfo(2); });
    this->connect(ui->action_rule,&QAction::triggered,[this]{ showInfo(3); });
}

void MainWindow::showError(const char *_error){
    QMessageBox message_box;
    message_box.critical(this,"Error",_error);
    message_box.setFixedSize(500,200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateDKA(){
    if(ui->lineEdit_alpthabet->text().length()==0){
        showError("No alphabet");
        return;
    }
    try {
        QString alpabet=ui->lineEdit_alpthabet->text(), start_chain=ui->lineEdit_start->text(), end_chain=ui->lineEdit_end->text();
        automat->clear();
        automat->setAlphabet(alpabet.toStdString());
        automat->checkQuestChain(start_chain.toStdString(),"start");
        automat->checkQuestChain(end_chain.toStdString(),"end");
        automat->generateDKA();
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    ui->pushButton_table->setEnabled(true);
    ui->pushButton_graph->setEnabled(true);
}

void MainWindow::showTable(){
    QVector<QString> headers;
    std::vector<std::string> temp=automat->getHaders();
    for(auto x:temp) headers.push_back(QString::fromStdString(x));
    QVector<QVector<QString>> data;
    std::vector<std::vector<std::string>> ttemp=automat->getRules();
    for(size_t i=0;i<ttemp.size();i++){
        data.push_back(QVector<QString>(ttemp[i].size()));
        for(size_t j=0;j<ttemp[i].size();j++) data[i][j]=QString::fromStdString(ttemp[i][j]);
    }
    TableWindow *table_window=new TableWindow();
    table_window->createTable(headers,data);
    table_window->show();
}

void MainWindow::showGraph(){
    std::vector<std::string> headers=automat->getHaders();
    std::vector<std::vector<std::string>> data=automat->getRules();
    GraphWindow *graph_window=new GraphWindow();
    graph_window->setData(headers,data);
    graph_window->draw();
    graph_window->show();
}

void MainWindow::checkChain(){
    QString result="";
    try {
        QString temp=ui->lineEdit_chain->text();
        result=QString::fromStdString(automat->checkChain(temp.toStdString()));
    }
    catch (std::exception &exp) {
        showError(exp.what());
        return;
    }
    ui->textEdit_chain_result->clear();
    ui->textEdit_chain_result->setText(result);
}

void MainWindow::saveDKA(){
    if(!automat->isDKAGenerate()){
        showError("DKA not generate");
        return;
    }
    QString str=QFileDialog::getSaveFileName(0,"Save file","../","Text (*.txt)");
    if(str.isEmpty()){
        showError("Invalid file");
        return;
    }
    try{
        automat->saveDKAInFile(str.toStdString());
    }
    catch(std::exception &exp){
        showError(exp.what());
        return;
    }
}

void MainWindow::saveCheck(){
    std::string check_text=ui->textEdit_chain_result->toPlainText().toStdString();
    size_t len=check_text.length();
    if(len==0){
        showError("Check is empty");
        return;
    }
    QString str=QFileDialog::getSaveFileName(0,"Save file","../","Text (*.txt)");
    if(str.isEmpty()){
        showError("Invalid file");
        return;
    }
    std::ofstream file_out(str.toStdString());
    size_t save_point=0, count_bracket=0;
    for(size_t i=0;i<len;i++){
        if(check_text[i]=='>') count_bracket++;
        if(count_bracket==3){
            file_out<<check_text.substr(save_point,i-save_point+1)+'\n';
            save_point=i-1;
            count_bracket=0;
        }
    }
    if(save_point<(len-1)) file_out<<check_text.substr(save_point);
    file_out.close();
}

void MainWindow::loadFile(){
    QString str=QFileDialog::getOpenFileName(0,"Open file","../","Text (*.txt)");
    if(str.isEmpty()){
        showError("Invalid file");
        return;
    }
    std::ifstream file_in(str.toStdString());
    std::string alphabet="", start_chain="", end_chain="";
    std::getline(file_in,alphabet);
    std::getline(file_in,start_chain);
    std::getline(file_in,end_chain);
    ui->lineEdit_alpthabet->setText(QString::fromStdString(alphabet));
    ui->lineEdit_start->setText(QString::fromStdString(start_chain));
    ui->lineEdit_end->setText(QString::fromStdString(end_chain));
    generateDKA();
}

void MainWindow::clearAll(){
    ui->lineEdit_alpthabet->clear();
    ui->lineEdit_start->clear();
    ui->lineEdit_end->clear();
    ui->lineEdit_chain->clear();
    ui->textEdit_chain_result->clear();
    ui->pushButton_table->setEnabled(false);
    ui->pushButton_graph->setEnabled(false);
    automat->clear();
}

void MainWindow::showInfo(int _mode){
    InfoWindow *info_window=new InfoWindow();
    info_window->setText(_mode);
    info_window->show();
}
