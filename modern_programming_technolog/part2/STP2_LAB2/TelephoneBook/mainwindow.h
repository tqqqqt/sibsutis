#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>
#include <vector>
#include <string>

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "info/infowindow.h"

#include "src/abonentlist.h"
#include "src/file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AbonentList abonent_list;
    File file;

private slots:
    void showError(const char*);

    void clearAll();
    void saveInFile();
    void loadFromFile();
    void deleteElem();
    void updateElem();

    void addElem();
    void findElem();

    void openInfo();

    void updateTable();
    void changeSelect();

signals:
    void needUpdateTable();
};

#endif // MAINWINDOW_H
