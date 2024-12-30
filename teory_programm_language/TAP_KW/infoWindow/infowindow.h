#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

    void setText(int);
private:
    Ui::InfoWindow *ui;
    QString author_text, tema_text, rule_text;
};

#endif // INFOWINDOW_H
