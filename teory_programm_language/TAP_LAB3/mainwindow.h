#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>
#include <QString>

#include <string>
#include <fstream>

#include "src/avtomat.h"

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
    avtomat *my_avtomat;
    QVector<QString> rules_mas;
    QString curent_alphabet;

    void showError(const char*);

private slots:
    void addRule();
    void startCheck();
    void deleteRule();
    void setDefault();
    void readFile();
    void clearAvtomat();

};

#endif // MAINWINDOW_H
