#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auth.h"
#include "ui_auth.h"
#include "QFileDialog"
#include "QTextDocumentWriter"

void MainWindow::About_Lab1(){
    auth *authWindow=new auth();
    authWindow->show();
}

void MainWindow::slotOpen(){
    QString fileName=QFileDialog::getOpenFileName(0, "Open file window", "", "*.cpp *.h *.txt");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) ui->textEdit->setPlainText(file.readAll());
}

void MainWindow::slotSave(){
    QString fileName=QFileDialog::getSaveFileName(0,"Save file window","","*.cpp *.h *.txt");
    QTextDocumentWriter writer;
    writer.setFileName(fileName);
    writer.write(ui->textEdit->document());
}

void MainWindow::slotClear(){
    ui->textEdit->clear();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action,SIGNAL(triggered()),this,SLOT(About_Lab1()));

    QAction* openAction=new QAction("file open action", 0);
    openAction->setText("&Open");
    openAction->setShortcut(QKeySequence("CTRL+S"));
    openAction->setToolTip("Open document");
    openAction->setStatusTip("Open file");
    openAction->setWhatsThis("Open file");
    openAction->setIcon(QPixmap("1.jpg"));
    connect(openAction, SIGNAL(triggered()), SLOT(slotOpen()));
    QAction* saveAction=new QAction("file save action", 0);
    saveAction->setText("&Save");
    saveAction->setShortcut(QKeySequence("CTRL+O"));
    saveAction->setToolTip("Save document");
    saveAction->setStatusTip("Save file");
    saveAction->setWhatsThis("Save file");
    saveAction->setIcon(QPixmap("1.jpg"));
    connect(saveAction, SIGNAL(triggered()), SLOT(slotSave()));
    QAction* clearAction=new QAction("textEdit clear action", 0);
    clearAction->setText("&Clear");
    clearAction->setShortcut(QKeySequence("CTRL+X"));
    clearAction->setToolTip("Clear textEdit");
    clearAction->setStatusTip("Clear textEdit");
    clearAction->setWhatsThis("Clear textEdit");
    clearAction->setIcon(QPixmap("1.jpg"));
    connect(clearAction,SIGNAL(triggered()),SLOT(slotClear()));
    //QMenu* pmnuFile=new QMenu("&File");
    //pmnuFile->addAction(pactOpen);
    //pmnuFile->addAction(pactSave);
    //pmnuFile->addAction(pactClear);
    //menuBar()->addMenu(pmnuFile);
    ui->mainToolBar->addAction(openAction);
    ui->mainToolBar->addAction(saveAction);
    ui->mainToolBar->addAction(clearAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}
