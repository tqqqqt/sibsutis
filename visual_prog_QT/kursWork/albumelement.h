#ifndef ALBUMELEMENT_H
#define ALBUMELEMENT_H

#include <QWidget>

namespace Ui {
class AlbumElement;
}

class AlbumElement{
public:
    int page;
    int numPhoto;
    QString imagePath;
    AlbumElement(int newNumber, int newPage, QString newImagePath){
        page=newPage;
        numPhoto=newNumber;
        imagePath=newImagePath;
    }
};

#endif // ALBUMELEMENT_H
