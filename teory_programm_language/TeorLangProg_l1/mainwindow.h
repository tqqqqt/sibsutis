#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QStringListModel>
#include <QMessageBox>

#include "./src/generator.h"
#include "./treeWindow/treewindow.h"

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
    generator *my_generator;
    QString inpute_rules="", input_start_rule="";
    QVector<QString> rules_mas;
    std::vector<std::tuple<std::string,std::string,std::vector<int>>> save_chain;
    int length_chain, curent_side;

    void showError(const char* error);

private slots:
    void addRule();
    void startGenerator();
    void deleteRule();
    void setDefault();
    void setMetod();
    void clearGenerator();
    void createTree();
};

#endif // MAINWINDOW_H
