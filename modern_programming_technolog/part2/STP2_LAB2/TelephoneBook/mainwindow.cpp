#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->pushButton_clear,SIGNAL(clicked()),this,SLOT(clearAll()));
    this->connect(ui->pushButton_save,SIGNAL(clicked()),this,SLOT(saveInFile()));
    this->connect(ui->pushButton_load,SIGNAL(clicked()),this,SLOT(loadFromFile()));
    this->connect(ui->pushButton_delete,SIGNAL(clicked()),this,SLOT(deleteElem()));
    this->connect(ui->pushButton_update,SIGNAL(clicked()),this,SLOT(updateElem()));
    this->connect(ui->pushButton_info,SIGNAL(clicked()),this,SLOT(openInfo()));

    this->connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(addElem()));
    this->connect(ui->pushButton_find,SIGNAL(clicked()),this,SLOT(findElem()));

    this->connect(this,SIGNAL(needUpdateTable()),this,SLOT(updateTable()));
    this->connect(ui->tableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(changeSelect()));

    emit needUpdateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openInfo(){
    InfoWindow infoWindow;
    infoWindow.exec();
}

void MainWindow::showError(const char* error_mes){
    QMessageBox message_box;
    message_box.critical(this,"Error",error_mes);
    message_box.setFixedSize(500,200);
}

void MainWindow::clearAll(){
    abonent_list.clear();

    emit needUpdateTable();
}

void MainWindow::saveInFile(){
    std::vector<std::string> list=abonent_list.getAll();
    size_t size=list.size();
    if(size==0){
        showError("Список пустой.");
        return;
    }

    QString str=QFileDialog::getSaveFileName(0,"Save file","../","Text (*.txt)");
    if(str.isEmpty()){
        showError("Invalid file");
        return;
    }

    file.saveInFile(str.toStdString(),list);
}

void MainWindow::loadFromFile(){
    std::vector<std::string> list;

    QString str=QFileDialog::getOpenFileName(0,"Load file","../","Text (*.txt)");
    if(str.isEmpty()){
        showError("Invalid file");
        return;
    }

    file.loadFromFile(str.toStdString(),list);

    int size=list.size();
    for(int i=0;i<size;i+=2){ //abonent_list.add(list[i],list[i+1]);
        ui->lineEdit_fio->setText(QString::fromStdString(list[i]));
        ui->lineEdit_telep->setText(QString::fromStdString(list[i+1]));

        try{
            addElem();
        }
        catch(std::exception){
            clearAll();
            showError("Incorect input file");
            return;
        }
    }

    emit needUpdateTable();
}

void MainWindow::deleteElem(){
    int index=ui->tableWidget->currentRow();
    abonent_list.deleteElem(index);

    emit needUpdateTable();
}

void MainWindow::updateElem(){
    int index=ui->tableWidget->currentRow();
    if(index<0){
        showError("Не выбрана запись для обновления.");
        return;
    }

    abonent_list.updateElem(index,ui->lineEdit_fio->text().toStdString(),ui->lineEdit_telep->text().toStdString());
    ui->lineEdit_fio->clear();
    ui->lineEdit_telep->clear();

    emit needUpdateTable();
}

void MainWindow::addElem(){
    QString name=ui->lineEdit_fio->text(), phone=ui->lineEdit_telep->text();
    if(name.length()==0 || phone.length()==0){
        showError("Не заполнены поля.");
        return;
    }

    for(int i=0;i<phone.length();++i){
        if(phone[i]>='0' && phone[i]<='9') continue;
        showError("В номере неправильные символы");
        return;
    }

    abonent_list.add(name.toStdString(),phone.toStdString());
    ui->lineEdit_fio->clear();
    ui->lineEdit_telep->clear();

    emit needUpdateTable();
}

void MainWindow::findElem(){
    QString name=ui->lineEdit_fio->text();
    size_t name_len=name.length();
    if(name_len==0){
        showError("Нет данных для поиска.");
        return;
    }

    int find_index=0;
    find_index=abonent_list.findName(name.toStdString());

    if(find_index==-1){
        showError("Не найдено.");
        return;
    }
    ui->tableWidget->setCurrentCell(find_index,1);
}

void MainWindow::updateTable(){
    ui->tableWidget->setCurrentCell(-1,-1);
    ui->tableWidget->clearSelection();
    ui->tableWidget->setRowCount(0);

    std::vector<std::string> list=abonent_list.getAll();
    QStringList headers{"Имя","Телефон"};

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    size_t siz=list.size();
    int row_count=0;
    for(int i=0;i<siz;i+=2, ++row_count){
        ui->tableWidget->insertRow(row_count);
        ui->tableWidget->setItem(row_count,0,new QTableWidgetItem(QString::fromStdString(list[i])));
        ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(QString::fromStdString(list[i+1])));
    }
}

void MainWindow::changeSelect(){
    int index=ui->tableWidget->currentRow();
    if(index<0) return;

    std::string name, phone;
    abonent_list.getElem(index,name,phone);

    ui->lineEdit_fio->setText(QString::fromStdString(name));
    ui->lineEdit_telep->setText(QString::fromStdString(phone));
}
