#include "tablewindow.h"
#include "ui_tablewindow.h"

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
}

void TableWindow::createTable(QVector<QString> _headers, QVector<QVector<QString> > _data){
    ui->tableWidget->setColumnCount(_headers.size());
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList::fromVector(_headers));
    for(int i=0;i<_data.size();i++){
        ui->tableWidget->insertRow(i);
        for(int j=0;j<_data[i].size();j++){
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(_data[i][j]));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

TableWindow::~TableWindow()
{
    delete ui;
}
