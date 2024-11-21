#include "startdialog_bauman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog_Bauman startDialog;
    startDialog.show();

    return a.exec();
}
