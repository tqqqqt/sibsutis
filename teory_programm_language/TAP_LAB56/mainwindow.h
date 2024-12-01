#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QVector>

#include <fstream>

#include "translator.h"

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
    translator* my_translator;
    QVector<QString> rules;

    void showError(const char*);

private slots:
    void addRule();
    void deleteRule();
    void translateChain();
    void loadFile();
    void clearAll();

};

#endif // MAINWINDOW_H
