#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QFileDialog>

#include <string>
#include <vector>
#include <fstream>

#include "./src/dkautomat.h"

#include "./tableWindow/tablewindow.h"
#include "./infoWindow/infowindow.h"
#include "./graphWindow/graphwindow.h"

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
    DKAutomat *automat;

    void showError(const char*);

private slots:
    void generateDKA();
    void showTable();
    void showGraph();
    void checkChain();

    void saveDKA();
    void saveCheck();

    void loadFile();
    void clearAll();

    void showInfo(int);
};

#endif // MAINWINDOW_H
