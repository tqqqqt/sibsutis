#ifndef SDIPROGRAMBAUMAN_H
#define SDIPROGRAMBAUMAN_H

#include <QMainWindow>

namespace Ui {
class SDIProgramBauman;
}

class SDIProgramBauman : public QMainWindow
{
    Q_OBJECT

public:
    explicit SDIProgramBauman(QWidget *parent = 0);
    ~SDIProgramBauman();

private:
    Ui::SDIProgramBauman *ui;
public slots:
    void SlotChangeWindowTitle(const QString&);
};

#endif // SDIPROGRAMBAUMAN_H
