#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QStringList>

namespace Ui {
class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    TableWindow(QWidget *parent = nullptr);
    ~TableWindow();

    void createTable(QVector<QString>, QVector<QVector<QString>>);

private:
    Ui::TableWindow *ui;
};

#endif // TABLEWINDOW_H
