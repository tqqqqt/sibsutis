#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form_bauman.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    form_bauman *myForm;

signals:
    void SendData(QString str);

private slots:
    void OnButtonSend();
    void LoadImageClick();
    void AvalibleButton();
};

#endif // MAINWINDOW_H
