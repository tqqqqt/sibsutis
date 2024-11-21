#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>

#include <fstream>

#include "automat.h"

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
    automat* my_automat;
    QVector<QString> rules;

    void showError(const char*);

private slots:
    void addRule();
    void deleteRule();
    void startCheck();
    void readFile();
    void clearProg();
};

#endif // MAINWINDOW_H
