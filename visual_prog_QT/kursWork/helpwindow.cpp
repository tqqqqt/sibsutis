#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Help window");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(HideWindow()));
    connect(ui->textBrowser,SIGNAL(anchorClicked(QUrl)),this,SLOT(on_textBrowser_anchorClicked(QUrl)));
    connect(ui->pushButton_2, SIGNAL(clicked()), ui->textBrowser, SLOT(forward()));
    connect(ui->pushButton_3, SIGNAL(clicked()), ui->textBrowser, SLOT(backward()));
    connect(ui->pushButton_4, SIGNAL(clicked()), ui->textBrowser, SLOT(home()));
    connect(ui->textBrowser, SIGNAL(forwardAvailable(bool)), ui->pushButton_2, SLOT(setEnabled(bool)));
    connect(ui->textBrowser, SIGNAL(backwardAvailable(bool)), ui->pushButton_3, SLOT(setEnabled(bool)));
    ui->textBrowser->setSource(QUrl::fromLocalFile(":/index.html"));
}

void HelpWindow::HideWindow(){
    this->hide();
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
