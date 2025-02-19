#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QFile>

#include <fstream>
#include <vector>
#include <cmath>

#pragma pack(push,1)
struct file_header{
    unsigned short id;
    unsigned int f_size;
    unsigned short rez_1, rez_2;
    unsigned int bm_offset;
};

struct v3_header{
    unsigned int h_size;
    unsigned int width;
    unsigned int height;
    unsigned short planes, bit_per_pixel;
    unsigned int compression;
    unsigned int size_image;
    unsigned int h_res;
    unsigned int v_res;
    unsigned int clr_used;
    unsigned int clr_imp;
};

struct color_info{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char temp;

    color_info(){ }
    color_info(int b, int g, int r, int t){
        blue=b;
        green=g;
        red=r;
        temp=t;
    }
};
#pragma pack(pop)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void paintImage(std::vector<std::vector<color_info>>);

private slots:
    void mainFunc(std::string);
};

#endif // MAINWINDOW_H
