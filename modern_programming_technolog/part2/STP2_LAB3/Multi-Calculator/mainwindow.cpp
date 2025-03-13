#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    last_system=10;
    dot_enable=1;

    curent_mode=Calculator_mode::PNum;
    processor=nullptr;
    object=nullptr;

    modeUpdate();
    sliderValueChange(10);
    memoryUpdate();

    this->connect(ui->pushButton_num0,&QPushButton::clicked,[this]{ addNum('0'); });
    this->connect(ui->pushButton_num1,&QPushButton::clicked,[this]{ addNum('1'); });
    this->connect(ui->pushButton_num2,&QPushButton::clicked,[this]{ addNum('2'); });
    this->connect(ui->pushButton_num3,&QPushButton::clicked,[this]{ addNum('3'); });
    this->connect(ui->pushButton_num4,&QPushButton::clicked,[this]{ addNum('4'); });
    this->connect(ui->pushButton_num5,&QPushButton::clicked,[this]{ addNum('5'); });
    this->connect(ui->pushButton_num6,&QPushButton::clicked,[this]{ addNum('6'); });
    this->connect(ui->pushButton_num7,&QPushButton::clicked,[this]{ addNum('7'); });
    this->connect(ui->pushButton_num8,&QPushButton::clicked,[this]{ addNum('8'); });
    this->connect(ui->pushButton_num9,&QPushButton::clicked,[this]{ addNum('9'); });
    this->connect(ui->pushButton_znak,SIGNAL(clicked()),this,SLOT(changeZnak()));
    this->connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(addDot()));

    this->connect(ui->pushButton_numa,&QPushButton::clicked,[this]{ addNum('A'); });
    this->connect(ui->pushButton_numb,&QPushButton::clicked,[this]{ addNum('B'); });
    this->connect(ui->pushButton_numc,&QPushButton::clicked,[this]{ addNum('C'); });
    this->connect(ui->pushButton_numd,&QPushButton::clicked,[this]{ addNum('D'); });
    this->connect(ui->pushButton_nume,&QPushButton::clicked,[this]{ addNum('E'); });
    this->connect(ui->pushButton_numf,&QPushButton::clicked,[this]{ addNum('F'); });

    this->connect(ui->pushButton_backspace,SIGNAL(clicked()),this,SLOT(delLast()));
    this->connect(ui->pushButton_ce,SIGNAL(clicked()),this,SLOT(clearNull()));
    this->connect(ui->pushButton_c,SIGNAL(clicked()),this,SLOT(clear()));

    this->connect(ui->pushButton_drob,SIGNAL(clicked()),this,SLOT(addObjectSpace()));
    this->connect(ui->pushButton_complex,SIGNAL(clicked()),this,SLOT(addObjectSpace()));

    this->connect(ui->pushButton_div,&QPushButton::clicked,[this]{ addOper('/'); });
    this->connect(ui->pushButton_mul,&QPushButton::clicked,[this]{ addOper('*'); });
    this->connect(ui->pushButton_minus,&QPushButton::clicked,[this]{ addOper('-'); });
    this->connect(ui->pushButton_plus,&QPushButton::clicked,[this]{ addOper('+'); });

    this->connect(ui->pushButton_sqr,&QPushButton::clicked,[this]{ addFunc("Sqr"); });
    this->connect(ui->pushButton_reverse,&QPushButton::clicked,[this]{ addFunc("Rev"); });

    this->connect(ui->pushButton_result,SIGNAL(clicked()),this,SLOT(execute()));

    this->connect(ui->pushButton_memc,SIGNAL(clicked()),this,SLOT(memoryClear()));
    this->connect(ui->pushButton_memr,SIGNAL(clicked()),this,SLOT(memoryCopy()));
    this->connect(ui->pushButton_mems,SIGNAL(clicked()),this,SLOT(memorySave()));
    this->connect(ui->pushButton_memp,SIGNAL(clicked()),this,SLOT(memoryAdd()));

    // signals
    this->connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChange(int)));
    this->connect(this,SIGNAL(needUpdateText()),this,SLOT(textUpdate()));
    this->connect(this,SIGNAL(needCheckMemory()),this,SLOT(memoryUpdate()));
    this->connect(this,SIGNAL(needUpdateMode()),this,SLOT(modeUpdate()));

    // actions
    this->connect(ui->action_ref,SIGNAL(triggered()),this,SLOT(openRef()));
    this->connect(ui->action_pmode,&QAction::triggered,[this]{ changeMode(1); });
    this->connect(ui->action_dmode,&QAction::triggered,[this]{ changeMode(2); });
    this->connect(ui->action_cmode,&QAction::triggered,[this]{ changeMode(3); });
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

void MainWindow::addNum(char _input){
    if(object->getType()==PNum::Object_type::Function) return;
    if(object->getType()==PNum::Object_type::Operator){
        all_objects.push_back(object->clone());
        object->clear();
    }
    object->addNum(_input);

    emit needUpdateText();
}

void MainWindow::addOper(char _input){
    if(object->getType()==PNum::Object_type::Operator || object->getType()==PNum::Object_type::None) return;

    all_objects.push_back(object->clone());
    object->clear();
    object->addOper(_input);

    emit needUpdateText();
}

void MainWindow::addFunc(QString _input){
    if(object->getType()==PNum::Object_type::Operator || object->getType()==PNum::Object_type::None) return;

    all_objects.push_back(object->clone());
    object->clear();
    object->addFunc(_input);

    emit needUpdateText();
}

void MainWindow::changeZnak(){
    if(object->getType()!=PNum::Object_type::Num) return;

    object->changeZnak();

    emit needUpdateText();
}

void MainWindow::addDot(){
    if(object->getType()!=PNum::Object_type::Num || curent_mode!=Calculator_mode::PNum) return;

    PNum *temp_object=dynamic_cast<PNum*>(object);
    if(temp_object==nullptr){
        showError("incorect object type");
        return;
    }
    temp_object->addDot();
    object=temp_object;

    emit needUpdateText();
}

void MainWindow::addObjectSpace(){
    if(curent_mode==Calculator_mode::PNum) return;
    if(object->getType()==Num::Object_type::Function) return;

    if(object->getType()==Num::Object_type::Operator){
        all_objects.push_back(object->clone());
        object->clear();
    }

    if(curent_mode==Calculator_mode::DNum){
        if(object->getType()!=Num::Object_type::Num) return;

        DNum *num=static_cast<DNum*>(object);
        num->setSpace();
    }
    else{
        CNum *num=static_cast<CNum*>(object);
        num->setSpace();
    }

    emit needUpdateText();
}

void MainWindow::execute(){
    if(all_objects.size()==0 && object->getType()==PNum::Object_type::None) return;

    all_objects.push_back(object->clone());
    if(object->getType()==PNum::Object_type::Operator) all_objects.push_back(all_objects[0]->clone());

    try{
        if(curent_mode==Calculator_mode::PNum){
            PNum_Processor *proc=static_cast<PNum_Processor*>(processor);
            proc->setSystem(last_system);
            proc->execute(all_objects);
        }
        else{
            processor->execute(all_objects);
        }
    }
    catch(std::exception& exp){
        showError(exp.what());
        clear();
        return;
    }

    object=all_objects.back();
    all_objects.pop_back();

    emit needUpdateText();
}

void MainWindow::delLast(){
    object->delLast();

    while(object->getType()==PNum::Object_type::None && all_objects.size()>0){
        object=all_objects.back();
        all_objects.pop_back();
    }
    if(object->getType()==PNum::Object_type::None && all_objects.size()==0) clear();

    emit needUpdateText();
}

void MainWindow::clearNull(){
    object->clear();
    all_objects.clear();
    processor->clear();

    object->addNum('0');

    emit needUpdateText();
}

void MainWindow::clear(){
    object->clear();
    all_objects.clear();
    processor->clear();

    emit needUpdateText();
}

void MainWindow::disableAllButtons(){
    ui->pushButton_num2->setEnabled(false);
    ui->pushButton_num3->setEnabled(false);
    ui->pushButton_num4->setEnabled(false);
    ui->pushButton_num5->setEnabled(false);
    ui->pushButton_num6->setEnabled(false);
    ui->pushButton_num7->setEnabled(false);
    ui->pushButton_num8->setEnabled(false);
    ui->pushButton_num9->setEnabled(false);

    ui->pushButton_numa->setEnabled(false);
    ui->pushButton_numb->setEnabled(false);
    ui->pushButton_numc->setEnabled(false);
    ui->pushButton_numd->setEnabled(false);
    ui->pushButton_nume->setEnabled(false);
    ui->pushButton_numf->setEnabled(false);
}

void MainWindow::enableSystemButtons(int _system){
    switch(_system){
    case 16:
        ui->pushButton_numf->setEnabled(true);
    case 15:
        ui->pushButton_nume->setEnabled(true);
    case 14:
        ui->pushButton_numd->setEnabled(true);
    case 13:
        ui->pushButton_numc->setEnabled(true);
    case 12:
        ui->pushButton_numb->setEnabled(true);
    case 11:
        ui->pushButton_numa->setEnabled(true);
    case 10:
        ui->pushButton_num9->setEnabled(true);
    case 9:
        ui->pushButton_num8->setEnabled(true);
    case 8:
        ui->pushButton_num7->setEnabled(true);
    case 7:
        ui->pushButton_num6->setEnabled(true);
    case 6:
        ui->pushButton_num5->setEnabled(true);
    case 5:
        ui->pushButton_num4->setEnabled(true);
    case 4:
        ui->pushButton_num3->setEnabled(true);
    case 3:
        ui->pushButton_num2->setEnabled(true);
    }
}

void MainWindow::memoryClear(){
    if(memory.curentStatus()==Memory::Memory_status::Off) return;

    memory.clear();

    emit needCheckMemory();
}

void MainWindow::memorySave(){
    if(object->getType()!=PNum::Object_type::Num) return;

    memory.save(object->clone());

    emit needCheckMemory();
}

void MainWindow::memoryCopy(){
    if(memory.curentStatus()==Memory::Memory_status::Off) return;
    if(object->getType()!=PNum::Object_type::Operator && object->getType()!=PNum::Object_type::None) return;
    if(object->getType()!=PNum::Object_type::None) all_objects.push_back(object->clone());

    try{
        object=memory.copy();
    }
    catch(std::exception& exp){
        showError(exp.what());
        return;
    }

    emit needCheckMemory();
    emit needUpdateText();
}

void MainWindow::memoryAdd(){
    if(memory.curentStatus()==Memory::Memory_status::Off) return;

    QVector<Num*> temp;
    temp.push_back(memory.copy());
    if(curent_mode==Calculator_mode::PNum) temp.push_back(new PNum());
    else if(curent_mode==Calculator_mode::DNum) temp.push_back(new DNum());
    else if(curent_mode==Calculator_mode::CNum) temp.push_back(new CNum());
    temp.back()->addOper('+');
    temp.push_back(object->clone());

    try{
        if(curent_mode==Calculator_mode::PNum){
            PNum_Processor *proc=static_cast<PNum_Processor*>(processor);
            proc->setSystem(last_system);
            proc->execute(temp);
        }
        else{
            processor->execute(temp);
        }
    }
    catch(std::exception& exp){
        showError(exp.what());
        return;
    }

    memory.save(temp.back());

    emit needCheckMemory();
}

void MainWindow::sliderValueChange(int _system){
    if(curent_mode!=Calculator_mode::PNum) return;
    ui->label_system->setText("Основание "+QString::fromStdString(std::to_string(_system)));

    all_objects.push_back(object->clone());
    if(memory.curentStatus()==Memory::Memory_status::On) all_objects.push_back(memory.copy());

    PNum_Processor *proc=static_cast<PNum_Processor*>(processor);
    proc->changeSystem(all_objects,last_system,_system);

    if(memory.curentStatus()==Memory::Memory_status::On){
        memory.save(all_objects.back());
        all_objects.pop_back();
    }

    object=all_objects.back();
    all_objects.pop_back();
    last_system=_system;

    disableAllButtons();
    enableSystemButtons(_system);

    emit needUpdateText();
}

void MainWindow::textUpdate(){
    int size=all_objects.size();
    QString text="";
    for(int i=0;i<size;++i) text+=all_objects[i]->getString();
    text+=object->getString();

    ui->textEdit->setText(text);
}

void MainWindow::memoryUpdate(){
    if(memory.curentStatus()==Memory::Memory_status::Off) ui->label_memory->setText("");
    else ui->label_memory->setText("M");
}

void MainWindow::modeUpdate(){
    // clear all objects
    if(object!=nullptr) delete object;
    if(processor!=nullptr) delete processor;
    object=nullptr;
    processor=nullptr;
    for(int i=all_objects.size()-1;i>=0;--i) delete all_objects[i];
    all_objects.clear();
    memory.clear();

    // change buttons enables
    enableSystemButtons(10);
    ui->horizontalSlider->setEnabled(false);
    ui->pushButton_dot->setEnabled(false);
    ui->pushButton_drob->setEnabled(false);
    ui->pushButton_complex->setEnabled(false);

    // create new
    if(curent_mode==Calculator_mode::PNum){
        object=new PNum;
        processor=new PNum_Processor;
        ui->horizontalSlider->setEnabled(true);
        ui->pushButton_dot->setEnabled(true);
        ui->label_mode->setText("Режим: p-ичные числа");
    }
    else if(curent_mode==Calculator_mode::DNum){
        object=new DNum;
        processor=new DNum_Processor;
        ui->pushButton_drob->setEnabled(true);
        ui->label_mode->setText("Режим: Дроби");
    }
    else{
        object=new CNum;
        processor=new CNum_Processor;
        ui->pushButton_complex->setEnabled(true);
        ui->label_mode->setText("Режим: Комплексные числа");
    }

    emit needCheckMemory();
    emit needUpdateText();
}

void MainWindow::openRef(){
    RefWindow ref_window;
    ref_window.exec();
}

void MainWindow::changeMode(int _mode){
    if(_mode==static_cast<int>(curent_mode)) return;

    if(_mode==1) curent_mode=Calculator_mode::PNum;
    else if(_mode==2) curent_mode=Calculator_mode::DNum;
    else curent_mode=Calculator_mode::CNum;

    emit needUpdateMode();
}
