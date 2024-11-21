#ifndef AUTH_H
#define AUTH_H

#include <QDialog>

namespace Ui {
class auth;
}

class auth : public QDialog
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = 0);
    ~auth();

private:
    Ui::auth *ui;
};

#endif // AUTH_H
