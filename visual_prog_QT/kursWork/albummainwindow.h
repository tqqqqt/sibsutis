#ifndef ALBUMMAINWINDOW_H
#define ALBUMMAINWINDOW_H

#include <QWidget>
#include <QList>

#include "albumelement.h"
#include "helpwindow.h"

namespace Ui {
class AlbumMainWindow;
}

class AlbumMainWindow : public QWidget
{
    Q_OBJECT

public:
    AlbumMainWindow(QWidget *parent = 0);
    AlbumMainWindow(QString fileName, QWidget *parent = 0);
    ~AlbumMainWindow();

private:
    Ui::AlbumMainWindow *ui;
    QString pathBase, theme;
    int curentPage=0;
    int deleteMode=0;
    QList<AlbumElement> elementList;
    HelpWindow *helpWindow;
    bool eventFilter(QObject *watched, QEvent *event);
    void LoadBase(QString);

signals:
    void ClickLabel(QObject *object);
    void ChangePage();
    void SaveFile(QString);
    void NeedOption();

private slots:
    void ButtonBack();
    void ButtonNext();
    void SetPixLabel(QObject *object);
    void CheckNewPage();
    void ButtonSave();
    void ButtonSaveAs();
    void ButtonLoad();
    void ButtonChangeBackground();
    void ButtonDeleteBackground();
    void AutoSave();
    void ButtonDeletePix();
    void ButtonOption();

public slots:
    void ButtonHelp();
    void LoadTheme(QString);
};

#endif // ALBUMMAINWINDOW_H
