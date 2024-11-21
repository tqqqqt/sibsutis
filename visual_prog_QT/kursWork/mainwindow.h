#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QSettings>

#include "albummainwindow.h"
#include "listelement.h"
#include "optionwindow.h"

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
    AlbumMainWindow *albumWindow;
    OptionWindow *optionWindow;
    QList<ListElement> listElements;
    QSettings *settings;
    QString theme;
    bool helpWindow=true;
    void LoadHistory();
    void SaveSettings();
    void LoadSettings();

public slots:
    void UpButtonOpen();
    void UpButtonExit();
    void LowButtonOpen();
    void ButtonCreate();
    void HistorySave(QString);
    void ButtonAvail();
    void ButtonOption();
    void ButtonAlbumOption();
    void loadNewSettings(QString,bool);
    void loadAlbumNewSettings(QString,bool);

signals:
    void OpenFile(QString);
};

#endif // MAINWINDOW_H
