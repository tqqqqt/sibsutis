#include "sdiprogrambauman.h"
#include <QApplication>
#include <QSplashScreen>
#include <QtWidgets>

void LoadModules(QSplashScreen *splashScreen){
    QTime time;
    time.start();
    for(int i=0;i<100;){
        if(time.elapsed()>40){
            time.start();
            i++;
        }
        splashScreen->showMessage("Loading modules: " + QString::number(i)+"%",Qt::AlignCenter|Qt::AlignCenter,Qt::black);
        qApp->processEvents();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen splashScreen(QPixmap("‪D:/raboti/QT/lab3/1.jpg"));
    splashScreen.show();
    SDIProgramBauman w;
    LoadModules(&splashScreen);
    splashScreen.finish(&w);
    w.show();

    return a.exec();
}
