#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_generator=new generator();

    ui->comboBox->insertItem(0,"Укороченный режим");
    ui->comboBox->insertItem(1,"Расширенный режим");
    ui->comboBox->setCurrentIndex(0);

    ui->combo_box_side->insertItem(0,"Левосторонний");
    ui->combo_box_side->insertItem(1,"Правосторонний");
    ui->comboBox->setCurrentIndex(0);

    connect(ui->push_button_add_rule,SIGNAL(clicked()),this,SLOT(addRule()));
    connect(ui->push_button_start,SIGNAL(clicked()),this,SLOT(startGenerator()));
    connect(ui->push_button_delete,SIGNAL(clicked()),this,SLOT(deleteRule()));
    connect(ui->action_default,SIGNAL(triggered()),this,SLOT(setDefault()));
    connect(ui->action_clear,SIGNAL(triggered()),this,SLOT(clearGenerator()));
    connect(ui->action_metod,SIGNAL(triggered()),this,SLOT(setMetod()));
    connect(ui->push_button_tree,SIGNAL(clicked()),this,SLOT(createTree()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showError(const char* error_mes){
    QMessageBox message_box;
    message_box.critical(this,"Error",error_mes);
    message_box.setFixedSize(500,200);
}

void MainWindow::addRule(){
    try {
        my_generator->setRule(ui->line_inpute_rule->text().toStdString());
    }
    catch (const char* error_mes) {
        showError(error_mes);
        return;
    }
    rules_mas.push_back(ui->line_inpute_rule->text());
    ui->list_view_rules->insertItem(rules_mas.size(),rules_mas.back());
    ui->line_inpute_rule->setText("");
}

void MainWindow::startGenerator(){
    if(ui->line_input_start->text()==""){
        showError("No start point.");
        return;
    }
    if(ui->spin_box_len_left->value()>ui->spin_box_len_right->value()){
        showError("Left length border > right length border.");
        return;
    }
    ui->list_view_chain->clear();
    QVector<QString> result_vector;
    curent_side=ui->combo_box_side->currentIndex()==0?1:2;
    try {
        ui->label_alph_res->setText(QString::fromStdString(my_generator->getAlphabet()));
        ui->label_rules_res->setText(QString::fromStdString(my_generator->getRulesNames()));
        save_chain=my_generator->startWork(ui->spin_box_len_left->value(),ui->spin_box_len_right->value(),ui->line_input_start->text().toStdString(),curent_side);
    }
    catch (const char* error_mes) {
        showError(error_mes);
        return;
    }
    int chain_mode=ui->comboBox->currentIndex()==0?1:2;
    for(size_t i=0;i<save_chain.size();i++){
        if(chain_mode==1) result_vector.push_back(QString::fromStdString(std::get<0>(save_chain[i])));
        else result_vector.push_back(QString::fromStdString(std::get<1>(save_chain[i])));
    }
    ui->list_view_chain->insertItems(1,QStringList(QList<QString>::fromVector(result_vector)));
}

void MainWindow::deleteRule(){
    if(ui->list_view_rules->currentRow()<0) return;
    try {
        my_generator->deleteRule(rules_mas[ui->list_view_rules->currentRow()].toStdString());
    }
    catch (const char* error_mes) {
        showError(error_mes);
    }
    rules_mas.erase(rules_mas.begin()+ui->list_view_rules->currentRow());
    ui->list_view_rules->takeItem(ui->list_view_rules->currentRow());
    ui->list_view_rules->setCurrentRow(-1);

}

void MainWindow::setDefault(){
    clearGenerator();
    ui->line_inpute_rule->setText("S->aS|bB|cC");
    addRule();
    ui->line_inpute_rule->setText("B->bB|b|cC");
    addRule();
    ui->line_inpute_rule->setText("C->cC|c");
    addRule();
}

void MainWindow::setMetod(){
    clearGenerator();
    ui->line_inpute_rule->setText("S->T|+T|-T");
    addRule();
    ui->line_inpute_rule->setText("T->F|TF");
    addRule();
    ui->line_inpute_rule->setText("F->0|1|2|3|4|5|6|7|8|9");
    addRule();
}

void MainWindow::clearGenerator(){
    my_generator->clearAllData();
    ui->list_view_rules->clear();
    ui->list_view_chain->clear();
    ui->line_input_start->setText("");
    ui->line_inpute_rule->setText("");
    ui->label_alph_res->setText("");
    ui->label_rules_res->setText("");
    rules_mas.clear();
    save_chain.clear();
}

void MainWindow::createTree(){
    int curent_row=ui->list_view_chain->currentRow();
    if(curent_row<0 || curent_row>save_chain.size()){
        showError("No curent chain.");
        return;
    }
    TreeWindow *tree_window=new TreeWindow(ui->line_input_start->text(),std::get<2>(save_chain[curent_row]),my_generator,curent_side,this);
    tree_window->show();
}
