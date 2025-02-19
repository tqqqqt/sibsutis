#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>

#include "src/converter.h"
#include "src/history.h"
#include "src/info.h"

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
    QString number;
    size_t count_dot;

    Converter *converter;
    History *history;
    Info *info;

private slots:
    void showError(const char*);
    // buttons
    void addMinus();
    void addDot();
    void addDigit(int);
    void addSymbol(char);
    void del();
    void clear();
    void updateText();
    void execut();

    // change curent systems
    void upNumChange(int);
    void upSliderChange(int);
    void downNumChange(int);
    void downSliderChange(int);

    // change buttons avalible
    void disableAllButtons();
    void enableSystemButtons(int);

    // change curent tab
    void updateTab(int);

signals:
    void needUpdateText();
};

#endif // MAINWINDOW_H
