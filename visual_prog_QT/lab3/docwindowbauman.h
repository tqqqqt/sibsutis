#ifndef DOCWINDOWBAUMAN_H
#define DOCWINDOWBAUMAN_H

#include<QTextEdit>

class DocWindowBauman : public QTextEdit
{
    Q_OBJECT

private:
    QString fileName;
public:
    DocWindowBauman(QWidget* pwgt=0);
signals:
    void ChangeWindowTitle(const QString&);
public slots:
    void SlotLoad();
    void SlotSave();
    void SlotSaveAs();
    void SlotAbout();
    void SlotColor();
};

#endif // DOCWINDOWBAUMAN_H
