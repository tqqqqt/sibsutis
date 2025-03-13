#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>

#include "RefWindow/refwindow.h"

#include "src/num.h"
#include "src/memory.h"
#include "src/processor.h"


#include "src/pnum.h"
#include "src/pnum_processor.h"

#include "src/dnum.h"
#include "src/dnum_processor.h"

#include "src/cnum.h"
#include "src/cnum_processor.h"

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
    enum class Calculator_mode{ PNum=1, DNum=2, CNum=3 };

    Ui::MainWindow *ui;
    int last_system, dot_enable;
    Calculator_mode curent_mode;
    Num *object;
    QVector<Num*> all_objects;

    Memory memory;

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
    void addObjectSpace();
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
    void modeUpdate();

    // actions
    void openRef();
    void changeMode(int);

signals:
    void needUpdateText();
    void needCheckMemory();
    void needUpdateMode();
};

#endif // MAINWINDOW_H
