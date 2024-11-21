#include "docwindowbauman.h"

#include<QFileDialog>
#include<QTextStream>
#include<QMessageBox>
#include<QColorDialog>

DocWindowBauman::DocWindowBauman(QWidget* pwgt) : QTextEdit(pwgt)
{

}

void DocWindowBauman::SlotLoad(){
    QString str=QFileDialog::getOpenFileName();
    if(str.isEmpty()){
        return;
    }
    QFile file(str);
    QFileInfo fileInfo(file.fileName());
    str=fileInfo.fileName();
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        setPlainText(stream.readAll());
        file.close();
        fileName=str;
        emit ChangeWindowTitle(fileName);
    }
}

void DocWindowBauman::SlotSave(){
    if(fileName.isEmpty()){
        SlotSaveAs();
        return;
    }
    QFile file(fileName);
    QFileInfo fileInfo(file.fileName());
    QString newFileName=fileInfo.fileName();
    fileName=newFileName;
    if(file.open(QIODevice::WriteOnly)){
        QTextStream(&file)<<toPlainText();
    }
    file.close();
    emit ChangeWindowTitle(fileName);
}

void DocWindowBauman::SlotSaveAs(){
    QString str=QFileDialog::getSaveFileName(0,fileName);
    if(!str.isEmpty()){
        fileName=str;
        SlotSave();
    }
}

void DocWindowBauman::SlotAbout(){
    QMessageBox::about(this,"Application","Bauman /nSergey /nIP-111");
}

void DocWindowBauman::SlotColor(){
    QColor newColor=QColorDialog::getColor(Qt::black,this);
    setTextColor(newColor);
}
