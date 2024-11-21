#include "albummainwindow.h"
#include "ui_albummainwindow.h"

#include <QFileDialog>
#include <QSql>
#include <QtSql>

AlbumMainWindow::AlbumMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumMainWindow)
{
    helpWindow=new HelpWindow();

    ui->setupUi(this);
    this->setWindowTitle("Album window");
    qApp->installEventFilter(this);
    ui->label_5->setText(QString("Страница - %1").arg(curentPage+1));
    ui->pushButton_9->setIcon(QIcon(QPixmap(":/trashKorz.png")));
    ui->pushButton_10->setIcon(QIcon(QPixmap(":/option.png")));

    QTimer* timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AutoSave()));
    timer->start(30000);
    elementList=QList<AlbumElement>();

    CheckNewPage();

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(ButtonBack()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(ButtonNext()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(ButtonSave()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ButtonLoad()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(ButtonSaveAs()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(ButtonChangeBackground()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(ButtonDeleteBackground()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(ButtonHelp()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(ButtonDeletePix()));
    connect(ui->pushButton_10,SIGNAL(clicked()),this,SLOT(ButtonOption()));
    connect(this,SIGNAL(ClickLabel(QObject*)),this,SLOT(SetPixLabel(QObject*)));
    connect(this,SIGNAL(ChangePage()),this,SLOT(CheckNewPage()));
}

AlbumMainWindow::AlbumMainWindow(QString fileName, QWidget *parent):
    QWidget(parent),
    ui(new Ui::AlbumMainWindow)
{
    helpWindow=new HelpWindow();

    ui->setupUi(this);
    qApp->installEventFilter(this);
    ui->label_5->setText(QString("Страница - %1").arg(curentPage+1));
    ui->pushButton_9->setIcon(QIcon(QPixmap(":/trashKorz.png")));
    ui->pushButton_10->setIcon(QIcon(QPixmap(":/option.png")));

    QTimer* timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(AutoSave()));
    timer->start(30000);
    elementList=QList<AlbumElement>();
    pathBase=fileName;

    LoadBase(pathBase);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(ButtonBack()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(ButtonNext()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(ButtonSave()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ButtonLoad()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(ButtonSaveAs()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(ButtonChangeBackground()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(ButtonDeleteBackground()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(ButtonHelp()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(ButtonDeletePix()));
    connect(ui->pushButton_10,SIGNAL(clicked()),this,SLOT(ButtonOption()));
    connect(this,SIGNAL(ClickLabel(QObject*)),this,SLOT(SetPixLabel(QObject*)));
    connect(this,SIGNAL(ChangePage()),this,SLOT(CheckNewPage()));
}

void AlbumMainWindow::SetPixLabel(QObject *object){
    if(deleteMode==0){
        QString fileName=QFileDialog::getOpenFileName(0,"Open file","","JPEG (*.jpg *jpeg);;PNG (*.png)");
        int numberPhoto=0;
        bool findErly=false;
        if(fileName.isEmpty()==false){
            QImage newImage(fileName);
            if(object==ui->label){
                ui->label->setText("");
                ui->label->setPixmap(QPixmap::fromImage(newImage));
                numberPhoto=curentPage*3;
            }
            else if(object==ui->label_2){
                ui->label_2->setText("");
                ui->label_2->setPixmap(QPixmap::fromImage(newImage));
                numberPhoto=(curentPage*3)+1;
            }
            else if(object==ui->label_3){
                ui->label_3->setText("");
                ui->label_3->setPixmap(QPixmap::fromImage(newImage));
                numberPhoto=(curentPage*3)+2;
            }
            for(int i=0;i<elementList.size();i++){
                if(elementList[i].numPhoto==numberPhoto){
                    findErly=true;
                    elementList[i].imagePath=fileName;
                }
            }
            if(findErly==false){
                AlbumElement newElement=AlbumElement(numberPhoto,curentPage,fileName);
                elementList.append(newElement);
            }
        }
    }
    else if(deleteMode==1){
        int numberPhoto=0;
        if(object==ui->label){
            ui->label->setPixmap(QPixmap::fromImage(QImage("1.png")));
            ui->label->setText("Photo 1");
            numberPhoto=curentPage*3;
        }
        else if(object==ui->label_2){
            ui->label_2->setPixmap(QPixmap::fromImage(QImage("1.png")));
            ui->label_2->setText("Photo 2");
            numberPhoto=(curentPage*3)+1;
        }
        else if(object==ui->label_3){
            ui->label_3->setPixmap(QPixmap::fromImage(QImage("1.png")));
            ui->label_3->setText("Photo 3");
            numberPhoto=(curentPage*3)+2;
        }
        for(int i=0;i<elementList.size();i++){
            if(elementList[i].numPhoto==numberPhoto){
                elementList[i].imagePath="-1";
                elementList[i].page=-1;
                break;
            }
        }
    }
}

void AlbumMainWindow::CheckNewPage(){
    if(curentPage>0){
        ui->pushButton->setEnabled(true);
    }
    else ui->pushButton->setEnabled(false);
    ui->label->setPixmap(QPixmap::fromImage(QImage("1.png")));
    ui->label->setText("Photo 1");
    ui->label_2->setPixmap(QPixmap::fromImage(QImage("1.png")));
    ui->label_2->setText("Photo 2");
    ui->label_3->setPixmap(QPixmap::fromImage(QImage("1.png")));
    ui->label_3->setText("Photo 3");
    ui->label_4->setPixmap(QPixmap::fromImage(QImage("1.png")));
    ui->label_5->setText(QString("Страница - %1").arg(curentPage+1));
    for(int i=0;i<elementList.size();i++){
        if(elementList[i].page==curentPage){
            if(elementList[i].numPhoto==curentPage*3) ui->label->setPixmap(QPixmap::fromImage(QImage(elementList[i].imagePath)));
            else if(elementList[i].numPhoto==(curentPage*3)+1) ui->label_2->setPixmap(QPixmap::fromImage(QImage(elementList[i].imagePath)));
            else if(elementList[i].numPhoto==(curentPage*3)+2) ui->label_3->setPixmap(QPixmap::fromImage(QImage(elementList[i].imagePath)));
            else if(elementList[i].numPhoto<0) ui->label_4->setPixmap(QPixmap::fromImage(QImage(elementList[i].imagePath)));
        }
    }
}

bool AlbumMainWindow::eventFilter(QObject *watched, QEvent *event){
    if(event->type()==QEvent::MouseButtonPress){
        if(watched==ui->label){
            emit ClickLabel(ui->label);
            return true;
        }
        else if(watched==ui->label_2){
            emit ClickLabel(ui->label_2);
            return true;
        }
        else if(watched==ui->label_3){
            emit ClickLabel(ui->label_3);
            return true;
        }
    }
    return false;
}

void AlbumMainWindow::ButtonBack(){
    if(curentPage>0){
        curentPage--;
        emit ChangePage();
    }
}

void AlbumMainWindow::ButtonNext(){
    curentPage++;
    emit ChangePage();
}

void AlbumMainWindow::ButtonSave(){
    if(pathBase.isEmpty()==true){
        QString fileName=QFileDialog::getSaveFileName(0,"Save file","","SQL (*.sql *.sqlite *.db)");
        pathBase=fileName;

    }
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(pathBase);
    if(!dataBase.open()) return;
    QSqlQuery a_query=QSqlQuery(dataBase);
    QString queryStr="DELETE FROM album;";
    a_query.exec(queryStr);
    queryStr="CREATE TABLE album (number integer PRIMARY KEY NOT NULL, page integer, path VARCHAR(255));";
    a_query.exec(queryStr);
    for(int i=0;i<elementList.size();i++){
        if(elementList[i].page!=-1){
            QString insertStr="INSERT INTO album(number, page, path) VALUES (%1, %2, '%3');";
            queryStr=insertStr.arg(elementList[i].numPhoto).arg(elementList[i].page).arg(elementList[i].imagePath);
            a_query.exec(queryStr);
        }
    }
    dataBase.close();
    emit SaveFile(pathBase);
}

void AlbumMainWindow::ButtonSaveAs(){
    QString fileName=QFileDialog::getSaveFileName(0,"Save file as","","SQL (*.sql *.sqlite *.db)");
    pathBase=fileName;
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(pathBase);
    if(!dataBase.open()) return;
    QSqlQuery a_query=QSqlQuery(dataBase);
    QString queryStr="CREATE TABLE album (number integer PRIMARY KEY NOT NULL, page integer, path VARCHAR(255));";
    a_query.exec(queryStr);
    for(int i=0;i<elementList.size();i++){
        if(elementList[i].page!=-1){
            QString insertStr="INSERT INTO album(number, page, path) VALUES (%1, %2, '%3');";
            queryStr=insertStr.arg(elementList[i].numPhoto).arg(elementList[i].page).arg(elementList[i].imagePath);
            a_query.exec(queryStr);
        }
    }
    dataBase.close();
    emit SaveFile(pathBase);
}

void AlbumMainWindow::ButtonLoad(){
    QString fileName=QFileDialog::getOpenFileName(0,"Open file","","SQL (*.sql *sqlite *db)");
    pathBase=fileName;
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(fileName);
    if(!dataBase.open()) return;
    QSqlQuery a_query=QSqlQuery(dataBase);
    QString queryStr="SELECT * FROM album";
    a_query.exec(queryStr);
    QSqlRecord queryRec=a_query.record();
    int numPhoto=0, page=0;
    QString pathImage;
    elementList.clear();
    while(a_query.next()){
        numPhoto=a_query.value(queryRec.indexOf("number")).toInt();
        page=a_query.value(queryRec.indexOf("page")).toInt();
        pathImage=a_query.value(queryRec.indexOf("path")).toString();
        AlbumElement newElement=AlbumElement(numPhoto,page,pathImage);
        elementList.append(newElement);
    }
    dataBase.close();
    emit CheckNewPage();
    emit SaveFile(pathBase);
}

void AlbumMainWindow::LoadBase(QString fileName){
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName(fileName);
    if(!dataBase.open()) return;
    QSqlQuery a_query=QSqlQuery(dataBase);
    QString queryStr="SELECT * FROM album";
    a_query.exec(queryStr);
    QSqlRecord queryRec=a_query.record();
    int numPhoto=0, page=0;
    QString pathImage;
    elementList.clear();
    while(a_query.next()){
        numPhoto=a_query.value(queryRec.indexOf("number")).toInt();
        page=a_query.value(queryRec.indexOf("page")).toInt();
        pathImage=a_query.value(queryRec.indexOf("path")).toString();
        AlbumElement newElement=AlbumElement(numPhoto,page,pathImage);
        elementList.append(newElement);
    }
    dataBase.close();
    emit CheckNewPage();
}

void AlbumMainWindow::AutoSave(){
    if(pathBase.isEmpty()==false){
        QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
        dataBase.setDatabaseName(pathBase);
        if(!dataBase.open()) return;
        QSqlQuery a_query=QSqlQuery(dataBase);
        QString queryStr="DELETE FROM album;";
        a_query.exec(queryStr);
        queryStr="CREATE TABLE album (number integer PRIMARY KEY NOT NULL, page integer, path VARCHAR(255));";
        a_query.exec(queryStr);
        for(int i=0;i<elementList.size();i++){
            if(elementList[i].page!=-1){
                QString insertStr="INSERT INTO album(number, page, path) VALUES (%1, %2, '%3');";
                queryStr=insertStr.arg(elementList[i].numPhoto).arg(elementList[i].page).arg(elementList[i].imagePath);
                a_query.exec(queryStr);
            }
        }
        dataBase.close();
    }
}

void AlbumMainWindow::ButtonChangeBackground(){
    QString fileName=QFileDialog::getOpenFileName(0,"Open file","","JPG (*.jpg *.jpeg);;PNG (*.png)");
    if(fileName.isEmpty()==false){
        ui->label_4->setPixmap(QPixmap::fromImage(QImage(fileName)));
        AlbumElement newElement=AlbumElement((curentPage+1)*(-1),curentPage,fileName);
        elementList.append(newElement);
    }
}

void AlbumMainWindow::ButtonDeleteBackground(){
    for(int i=0;i<elementList.size();i++){
        if(elementList[i].page==curentPage && elementList[i].numPhoto==-1){
            elementList[i].page=-1;
            break;
        }
    }
    ui->label_4->setPixmap(QPixmap::fromImage(QImage("1.png")));
}

void AlbumMainWindow::ButtonHelp(){
    helpWindow->show();
}

void AlbumMainWindow::ButtonOption(){
    emit NeedOption();
}

void AlbumMainWindow::ButtonDeletePix(){
    if(deleteMode==0){
        deleteMode=1;
        ui->pushButton_9->setStyleSheet("QPushButton{background-color: orange; }");
    }
    else if(deleteMode==1){
        deleteMode=0;
        ui->pushButton_9->setProperty("theme",theme);
        ui->pushButton_9->style()->unpolish(ui->pushButton_9);
        ui->pushButton_9->style()->polish(ui->pushButton_9);
        ui->pushButton_9->update();
    }
}

void AlbumMainWindow::LoadTheme(QString newTheme){
    theme=newTheme;
    ui->pushButton->setProperty("theme",newTheme);
    ui->pushButton_2->setProperty("theme",newTheme);
    ui->pushButton_3->setProperty("theme",newTheme);
    ui->pushButton_4->setProperty("theme",newTheme);
    ui->pushButton_5->setProperty("theme",newTheme);
    ui->pushButton_6->setProperty("theme",newTheme);
    ui->pushButton_7->setProperty("theme",newTheme);
    ui->pushButton_8->setProperty("theme",newTheme);
    ui->pushButton_9->setProperty("theme",newTheme);
    ui->pushButton->style()->unpolish(ui->pushButton);
    ui->pushButton_2->style()->unpolish(ui->pushButton_2);
    ui->pushButton_3->style()->unpolish(ui->pushButton_3);
    ui->pushButton_4->style()->unpolish(ui->pushButton_4);
    ui->pushButton_5->style()->unpolish(ui->pushButton_5);
    ui->pushButton_6->style()->unpolish(ui->pushButton_6);
    ui->pushButton_7->style()->unpolish(ui->pushButton_7);
    ui->pushButton_8->style()->unpolish(ui->pushButton_8);
    ui->pushButton_9->style()->unpolish(ui->pushButton_9);
    ui->pushButton->style()->polish(ui->pushButton);
    ui->pushButton_2->style()->polish(ui->pushButton_2);
    ui->pushButton_3->style()->polish(ui->pushButton_3);
    ui->pushButton_4->style()->polish(ui->pushButton_4);
    ui->pushButton_5->style()->polish(ui->pushButton_5);
    ui->pushButton_6->style()->polish(ui->pushButton_6);
    ui->pushButton_7->style()->polish(ui->pushButton_7);
    ui->pushButton_8->style()->polish(ui->pushButton_8);
    ui->pushButton_9->style()->polish(ui->pushButton_9);
    ui->pushButton->update();
    ui->pushButton_2->update();
    ui->pushButton_3->update();
    ui->pushButton_4->update();
    ui->pushButton_5->update();
    ui->pushButton_6->update();
    ui->pushButton_7->update();
    ui->pushButton_8->update();
    ui->pushButton_9->update();
    ui->label->setProperty("style",newTheme);
    ui->label_2->setProperty("style",newTheme);
    ui->label_3->setProperty("style",newTheme);
    ui->label->style()->unpolish(ui->label);
    ui->label_2->style()->unpolish(ui->label_2);
    ui->label_3->style()->polish(ui->label_3);
    ui->label->style()->polish(ui->label);
    ui->label_2->style()->polish(ui->label_2);
    ui->label_3->style()->polish(ui->label_3);
    ui->label->update();
    ui->label_2->update();
    ui->label_3->update();
}

AlbumMainWindow::~AlbumMainWindow()
{
    delete ui;
}
