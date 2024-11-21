#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

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
    QGraphicsScene *scene;
    QGraphicsPixmapItem* birdItem;
    QGraphicsPixmapItem* treeItem;
    QGraphicsItem* ItemCollidesWith(QGraphicsItem* item);

public slots:
    void BirdMove();
};

#endif // MAINWINDOW_H
