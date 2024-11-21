#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <Qtimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene;

    ui->graphicsView->setScene(scene);
    QPixmap* pixBird=new QPixmap(":/bird.png"), *pixTree=new QPixmap(":/tree.png");
    treeItem=scene->addPixmap(pixTree->scaled(160,160));
    birdItem=scene->addPixmap(pixBird->scaled(120,120));
    birdItem->setFlags(QGraphicsPixmapItem::ItemIsMovable);
    birdItem->setPos(300,100);
    birdItem->setData(0,"Bird");
    treeItem->setFlags(QGraphicsPixmapItem::ItemIsMovable);
    treeItem->setPos(70,298);
    treeItem->setData(0,"Tree");
    scene->addEllipse(QRectF(950,15,40,40),QPen(Qt::yellow,4),QBrush(Qt::yellow));
    QGraphicsLineItem* lineItem1=scene->addLine(QLineF(10,15,10,450),QPen(Qt::red,2));
    lineItem1->setData(0,"Wall");
    QGraphicsLineItem* lineItem2=scene->addLine(QLineF(15,10,995,10),QPen(Qt::red,2));
    lineItem2->setData(0,"Wall");
    QGraphicsLineItem* lineItem3=scene->addLine(QLineF(1000,15,1000,450),QPen(Qt::red,2));
    lineItem3->setData(0,"Wall");
    QGraphicsLineItem* lineItem4=scene->addLine(QLineF(15,460,995,460),QPen(Qt::red,2));
    lineItem4->setData(0,"Wall");

    QTimer* timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(BirdMove()));
    timer->start(100);
}

QGraphicsItem* MainWindow::ItemCollidesWith(QGraphicsItem *item){
    QList<QGraphicsItem*> collectionCollisions=scene->collidingItems(item);
    foreach(QGraphicsItem *it,collectionCollisions){
        if(it==item) continue;
        return it;
    }
    return NULL;
}

void MainWindow::BirdMove(){
    int moveNavig=1+rand()%4;
    QPointF newPoint;
    newPoint.setX(0);
    newPoint.setY(0);
    switch(moveNavig){
    case 1: newPoint.setX(-20); break;
    case 2: newPoint.setX(+20); break;
    case 3: newPoint.setY(-20); break;
    case 4: newPoint.setY(+20); break;
    }
    QTransform tran=birdItem->transform();
    tran=birdItem->transform();
    tran.translate(newPoint.x(),newPoint.y());
    birdItem->setTransform(tran);
    QGraphicsItem* obstacle=ItemCollidesWith(birdItem);
    tran=birdItem->transform();
    if(obstacle){
        if(obstacle->data(0)=="Wall" || obstacle->data(0)=="Tree"){
            tran.translate(-newPoint.x(),-newPoint.y());
            birdItem->setTransform(tran);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
