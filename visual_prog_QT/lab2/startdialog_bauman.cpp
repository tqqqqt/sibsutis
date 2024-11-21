#include "startdialog_bauman.h"

StartDialog_Bauman::StartDialog_Bauman(QWidget* pwgt): QPushButton("Нажми",pwgt){
    connect(this, SIGNAL(clicked()),SLOT(slotButtonClicked()));
}
