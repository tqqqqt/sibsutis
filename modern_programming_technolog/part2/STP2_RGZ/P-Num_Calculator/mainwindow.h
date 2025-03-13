#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>

#include "RefWindow/refwindow.h"

#include "src/memory.h"
#include "src/pnum.h"
#include "src/processor.h"

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
    int last_system, dot_enable;
    PNum object;
    QVector<PNum> all_objects;

    Memory *memory;
    Processor *processor;

private slots:
    // error window
    void showError(const char*);

    // str buttons
    void addNum(char);
    void addOper(char);
    void addFunc(QString);
    void changeZnak();
    void addDot();
    void execute();

    // str clear
    void delLast();
    void clearNull();
    void clear();

    // react to new system
    void disableAllButtons();
    void enableSystemButtons(int);

    // memory work
    void memoryClear();
    void memorySave();
    void memoryCopy();
    void memoryAdd();

    // signals functions
    void sliderValueChange(int);
    void textUpdate();
    void memoryUpdate();

    // actions
    void changeDotStatus(int);
    void openRef();

signals:
    void needUpdateText();
    void needCheckMemory();
};

#endif // MAINWINDOW_H
