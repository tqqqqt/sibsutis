#ifndef OPTIONWINDOW_H
#define OPTIONWINDOW_H

#include <QDialog>

namespace Ui {
class OptionWindow;
}

class OptionWindow : public QDialog
{
    Q_OBJECT

public:
    OptionWindow(QWidget *parent = 0);
    OptionWindow(int tempTheme, bool helpWindow, QWidget *parent = 0);
    ~OptionWindow();

private:
    Ui::OptionWindow *ui;
    QString theme;
    bool help=true;
    int tempWindow=0;

signals:
    void AcceptSetings(QString, bool);
    void AcceptAlbumSetings(QString, bool);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void checkBox1();
    void checkBox2();
    void checkBox3();

public slots:
    void chendeWindow();
};

#endif // OPTIONWINDOW_H
