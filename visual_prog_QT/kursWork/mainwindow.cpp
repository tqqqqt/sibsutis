#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStringListModel>
#include <QSql>
#include <QtSql>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Welcom window");
    connect(this,SIGNAL(OpenFile(QString)),this,SLOT(HistorySave(QString)));
    connect(ui->action,SIGNAL(triggered()),this,SLOT(UpButtonOpen()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(ButtonCreate()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(UpButtonExit()));
    connect(ui->action_4,SIGNAL(triggered()),this,SLOT(ButtonOption()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(LowButtonOpen()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(ButtonCreate()));
    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(ButtonAvail()));

    listElements=QList<ListElement>();
    LoadHistory();
    for(int i=0;i<listElements.size();i++) ui->listWidget->addItem(listElements[i].fileName);

    settings=new QSettings(this);
    LoadSettings();

    int temp;
    if(theme=="White") temp=1;
    else temp=2;
    optionWindow=new OptionWindow(temp,helpWindow);
    connect(optionWindow,SIGNAL(AcceptSetings(QString,bool)),this,SLOT(loadNewSettings(QString,bool)));
    connect(optionWindow,SIGNAL(AcceptAlbumSetings(QString,bool)),this,SLOT(loadAlbumNewSettings(QString,bool)));
}

void MainWindow::ButtonAvail(){
    if(ui->listWidget->currentItem()!=NULL) ui->pushButton->setEnabled(true);
}

void MainWindow::UpButtonOpen(){
    QString fileName=QFileDialog::getOpenFileName(0,"Open file","","SQL (*.sql *.sqlite *.db)");
    if(fileName.isEmpty()==false){
        albumWindow=new AlbumMainWindow(fileName);
        connect(albumWindow,SIGNAL(SaveFile(QString)),this,SLOT(HistorySave(QString)));
        connect(albumWindow,SIGNAL(NeedOption()),this,SLOT(ButtonAlbumOption()));
        emit OpenFile(fileName);
        hide();
        LoadSettings();
        albumWindow->show();
        albumWindow->LoadTheme(theme);
    }
}

void MainWindow::UpButtonExit(){
    qApp->quit();
}

void MainWindow::ButtonCreate(){
    albumWindow=new AlbumMainWindow();
    connect(albumWindow,SIGNAL(SaveFile(QString)),this,SLOT(HistorySave(QString)));
    connect(albumWindow,SIGNAL(NeedOption()),this,SLOT(ButtonAlbumOption()));
    hide();
    LoadSettings();
    albumWindow->show();
    albumWindow->LoadTheme(theme);
    if(helpWindow==true) albumWindow->ButtonHelp();
}

void MainWindow::LowButtonOpen(){
    int needNum=ui->listWidget->currentRow();
    QFileInfo fileInfo(listElements[needNum].filePath);
    if(fileInfo.exists()){
        albumWindow=new AlbumMainWindow(listElements[needNum].filePath);
        connect(albumWindow,SIGNAL(SaveFile(QString)),this,SLOT(HistorySave(QString)));
        connect(albumWindow,SIGNAL(NeedOption()),this,SLOT(ButtonAlbumOption()));
        HistorySave(listElements[needNum].filePath);
        hide();
        LoadSettings();
        albumWindow->show();
        albumWindow->LoadTheme(theme);
    }
}

void MainWindow::ButtonOption(){
    optionWindow->show();
}

void MainWindow::ButtonAlbumOption(){
    optionWindow->chendeWindow();
    optionWindow->show();
}

void MainWindow::loadNewSettings(QString newTheme, bool newHelp){
    theme=newTheme;
    helpWindow=newHelp;
    SaveSettings();
    LoadSettings();
}

void MainWindow::loadAlbumNewSettings(QString newTheme, bool newHelp){
    theme=newTheme;
    helpWindow=newHelp;
    SaveSettings();
    LoadSettings();
    albumWindow->LoadTheme(theme);
}

void MainWindow::HistorySave(QString newFile){
    for(int i=0;i<listElements.size();i++){
        if(listElements[i].filePath==newFile){
            listElements[i].filePath="-1";
            break;
        }
    }
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("./history.db");
    if(!dataBase.open()) return;
    QSqlQuery a_query=QSqlQuery(dataBase);
    QString queryStr="DELETE FROM history";
    a_query.exec(queryStr);
    queryStr="CREATE TABLE history (id integer PRIMARY KEY NOT NULL, fileName VARCHAR(255), path VARCHAR(255));";
    a_query.exec(queryStr);
    ListElement tempElement=ListElement(newFile);
    listElements.insert(0,tempElement);
    for(int i=0;i<listElements.size();i++){
        if(listElements[i].filePath!="-1"){
            QFileInfo checkFile(listElements[i].filePath);
            if(checkFile.exists() && checkFile.isFile()){
                QString insertStr="INSERT INTO history(id, fileName, path) VALUES (%1, '%2', '%3');";
                queryStr=insertStr.arg(i).arg(listElements[i].fileName).arg(listElements[i].filePath);
                a_query.exec(queryStr);
            }
        }
    }
    dataBase.close();
}

void MainWindow::LoadHistory(){
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("./history.db");
    if(!dataBase.open()) return;
    QSqlQuery a_query=QSqlQuery(dataBase);
    QString queryStr="SELECT * FROM history";
    a_query.exec(queryStr);
    QSqlRecord queryRec=a_query.record();
    QString fileName, filePath;
    listElements.clear();
    while(a_query.next()){
        fileName=a_query.value(queryRec.indexOf("fileName")).toString();
        filePath=a_query.value(queryRec.indexOf("path")).toString();
        ListElement newElement=ListElement(filePath);
        listElements.append(newElement);
    }
    dataBase.close();
}

void MainWindow::SaveSettings(){
    settings->setValue("appTheme",theme);
    settings->setValue("helpShow",helpWindow);
}

void MainWindow::LoadSettings(){
    theme=settings->value("appTheme").toString();
    ui->pushButton->setProperty("theme",theme);
    ui->pushButton_2->setProperty("theme",theme);
    ui->pushButton->style()->unpolish(ui->pushButton);
    ui->pushButton_2->style()->unpolish(ui->pushButton_2);
    ui->pushButton->style()->polish(ui->pushButton);
    ui->pushButton_2->style()->polish(ui->pushButton_2);
    ui->pushButton->update();
    ui->pushButton_2->update();
    helpWindow=settings->value("helpShow","true").toBool();
}

MainWindow::~MainWindow()
{
    SaveSettings();
    delete ui;
}
