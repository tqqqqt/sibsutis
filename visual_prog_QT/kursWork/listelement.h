#ifndef LISTELEMENT_H
#define LISTELEMENT_H

#include <QWidget>
#include <QFileInfo>

namespace Ui {
class ListElement;
}

class ListElement{
public:
    QString fileName;
    QString filePath;
    ListElement(QString newFilePath){
        QFileInfo fileInfo(newFilePath);
        QString newFileName=fileInfo.fileName();
        fileName=newFileName;
        filePath=newFilePath;
    }
};

#endif // LISTELEMENT_H
