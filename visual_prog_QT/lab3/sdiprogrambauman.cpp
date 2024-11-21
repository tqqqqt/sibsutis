#include "sdiprogrambauman.h"
#include "ui_sdiprogrambauman.h"

#include<docwindowbauman.h>

void SDIProgramBauman::SlotChangeWindowTitle(const QString& newWindowTitle){
    setWindowTitle(newWindowTitle);
}

SDIProgramBauman::SDIProgramBauman(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SDIProgramBauman)
{
    ui->setupUi(this);
    QMenu* menuFile=new QMenu("&File");
    QMenu* menuHelp=new QMenu("&Help");
    DocWindowBauman* textEditWindow=new DocWindowBauman;

    menuFile->addAction("&Open file",textEditWindow,SLOT(SlotLoad()),QKeySequence("CTRL+O"));
    menuFile->addAction("&Save file",textEditWindow,SLOT(SlotSave()),QKeySequence("CTRL+S"));
    menuFile->addAction("&Save as",textEditWindow,SLOT(SlotSaveAs()),QKeySequence("CTRL+E"));
    menuFile->addSeparator();
    menuFile->addAction("&Color",textEditWindow,SLOT(SlotColor()),QKeySequence("CTRL+C"));
    menuFile->addSeparator();
    menuFile->addAction("&Exit",qApp,SLOT(quit()),QKeySequence("CTRL+Q"));

    menuHelp->addAction("&About",textEditWindow,SLOT(SlotAbout()),Qt::Key_F1);

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuHelp);

    setCentralWidget(textEditWindow);

    connect(textEditWindow,SIGNAL(ChangeWindowTitle(const QString&)),SLOT(SlotChangeWindowTitle(const QString&)));
    statusBar()->showMessage("Ready",2000);
}

SDIProgramBauman::~SDIProgramBauman()
{
    delete ui;
}
