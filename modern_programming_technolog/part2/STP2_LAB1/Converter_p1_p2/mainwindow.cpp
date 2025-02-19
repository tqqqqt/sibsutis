#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    number="";
    count_dot=0;
    converter=new Converter;
    history=new History;
    info=new Info;

    ui->setupUi(this);

    disableAllButtons();
    enableSystemButtons(10);

    this->connect(ui->pushButton_0,&QPushButton::clicked,[this]{ addDigit(0); });
    this->connect(ui->pushButton_1,&QPushButton::clicked,[this]{ addDigit(1); });
    this->connect(ui->pushButton_2,&QPushButton::clicked,[this]{ addDigit(2); });
    this->connect(ui->pushButton_3,&QPushButton::clicked,[this]{ addDigit(3); });
    this->connect(ui->pushButton_4,&QPushButton::clicked,[this]{ addDigit(4); });
    this->connect(ui->pushButton_5,&QPushButton::clicked,[this]{ addDigit(5); });
    this->connect(ui->pushButton_6,&QPushButton::clicked,[this]{ addDigit(6); });
    this->connect(ui->pushButton_7,&QPushButton::clicked,[this]{ addDigit(7); });
    this->connect(ui->pushButton_8,&QPushButton::clicked,[this]{ addDigit(8); });
    this->connect(ui->pushButton_9,&QPushButton::clicked,[this]{ addDigit(9); });

    this->connect(ui->pushButton_A,&QPushButton::clicked,[this]{ addSymbol('A'); });
    this->connect(ui->pushButton_B,&QPushButton::clicked,[this]{ addSymbol('B'); });
    this->connect(ui->pushButton_C,&QPushButton::clicked,[this]{ addSymbol('C'); });
    this->connect(ui->pushButton_D,&QPushButton::clicked,[this]{ addSymbol('D'); });
    this->connect(ui->pushButton_E,&QPushButton::clicked,[this]{ addSymbol('E'); });
    this->connect(ui->pushButton_F,&QPushButton::clicked,[this]{ addSymbol('F'); });

    this->connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(addMinus()));
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(addDot()));

    this->connect(ui->pushButton_BS,SIGNAL(clicked()),this,SLOT(del()));
    this->connect(ui->pushButton_CE,SIGNAL(clicked()),this,SLOT(clear()));

    this->connect(ui->pushButton_Execut,SIGNAL(clicked()),this,SLOT(execut()));

    this->connect(this,SIGNAL(needUpdateText()),this,SLOT(updateText()));

    this->connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(upNumChange(int)));
    this->connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(upSliderChange(int)));
    this->connect(ui->spinBox_2,SIGNAL(valueChanged(int)),this,SLOT(downNumChange(int)));
    this->connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),this,SLOT(downSliderChange(int)));

    this->connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(updateTab(int)));
}

MainWindow::~MainWindow()
{
    delete converter;
    delete history;
    delete info;

    delete ui;
}

void MainWindow::showError(const char* _error){
    QMessageBox message_box;
    message_box.critical(this,"Error",_error);
    message_box.setFixedSize(500,200);
}

void MainWindow::addMinus(){
    if(number.length()==0 || number[0]!='-') number='-'+number;
    else if(number.length()!=0 && number[0]=='-') number=QString::fromStdString(number.toStdString().substr(1));

    emit needUpdateText();
}

void MainWindow::addDot(){
    if(count_dot!=0) return;
    if(number.length()==0 || (number.length()==1 && number[0]=='-')) return;

    number+='.';
    count_dot+=1;

    emit needUpdateText();
}

void MainWindow::addDigit(int _num){
    if(number.length()==1 && number[0]=='0') number[0]='0'+_num;
    else number+='0'+_num;

    emit needUpdateText();
}

void MainWindow::addSymbol(char _symbol){
    if(number.length()==1 && number[0]=='0') number[0]=_symbol;
    else if(number.length()==2 && number[0]=='-' && number[1]=='0') number[1]=_symbol;
    else number+=_symbol;

    emit needUpdateText();
}

void MainWindow::del(){
    if(number.length()==0) return;
    if(number.back()=='.') count_dot=0;
    number.chop(1);

    emit needUpdateText();
}

void MainWindow::clear(){
    number.clear();
    count_dot=0;

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    emit needUpdateText();
}

void MainWindow::updateText(){
    ui->lineEdit_2->setText(number);
}

void MainWindow::execut(){
    int p1=ui->spinBox->value(), p2=ui->spinBox_2->value();

    if(p1==p2) ui->lineEdit->setText(number);
    else{
        std::string result="";
        try{
            double temp_result=converter->convertTo10(number.toStdString(),p1);
            result=converter->convertFrom10(temp_result,p2,20);

            if(result.length()>32767) throw std::invalid_argument("result out of range");
        }
        catch(std::exception& exp){
            showError(exp.what());
        }

        ui->lineEdit->setText(QString::fromStdString(result));
    }

    history->addRecord(p1,p2,ui->lineEdit_2->text(),ui->lineEdit->text());
}

void MainWindow::upNumChange(int _val){
    if(ui->horizontalSlider->value()==_val) return;
    ui->horizontalSlider->setValue(_val);

    disableAllButtons();
    enableSystemButtons(_val);
}

void MainWindow::upSliderChange(int _val){
    if(ui->spinBox->value()==_val) return;
    ui->spinBox->setValue(_val);

    disableAllButtons();
    enableSystemButtons(_val);
}

void MainWindow::downNumChange(int _val){
    if(ui->horizontalSlider_2->value()==_val) return;
    ui->horizontalSlider_2->setValue(_val);

    //execut();
}

void MainWindow::downSliderChange(int _val){
    if(ui->spinBox_2->value()==_val) return;
    ui->spinBox_2->setValue(_val);

    //execut();
}

void MainWindow::disableAllButtons(){
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);

    ui->pushButton_A->setEnabled(false);
    ui->pushButton_B->setEnabled(false);
    ui->pushButton_C->setEnabled(false);
    ui->pushButton_D->setEnabled(false);
    ui->pushButton_E->setEnabled(false);
    ui->pushButton_F->setEnabled(false);
}

void MainWindow::enableSystemButtons(int _system){
    if(_system==2) return;

    if(_system>=3) ui->pushButton_2->setEnabled(true);
    else return;
    if(_system>=4) ui->pushButton_3->setEnabled(true);
    else return;
    if(_system>=5) ui->pushButton_4->setEnabled(true);
    else return;
    if(_system>=6) ui->pushButton_5->setEnabled(true);
    else return;
    if(_system>=7) ui->pushButton_6->setEnabled(true);
    else return;
    if(_system>=8) ui->pushButton_7->setEnabled(true);
    else return;
    if(_system>=9) ui->pushButton_8->setEnabled(true);
    else return;
    if(_system>=10) ui->pushButton_9->setEnabled(true);
    else return;
    if(_system>=11) ui->pushButton_A->setEnabled(true);
    else return;
    if(_system>=12) ui->pushButton_B->setEnabled(true);
    else return;
    if(_system>=13) ui->pushButton_C->setEnabled(true);
    else return;
    if(_system>=14) ui->pushButton_D->setEnabled(true);
    else return;
    if(_system>=15) ui->pushButton_E->setEnabled(true);
    else return;
    if(_system>=16) ui->pushButton_F->setEnabled(true);
    else return;
}

void MainWindow::updateTab(int _curent_tab){
    if(_curent_tab==0) return;

    if(_curent_tab==1){
        ui->listWidget->clear();

        int size=history->count();
        for(int i=0;i<size;i++){
            ui->listWidget->addItem(history->at(i).toString());
        }

        return;
    }

    ui->textEdit->setText(info->getText());
}
