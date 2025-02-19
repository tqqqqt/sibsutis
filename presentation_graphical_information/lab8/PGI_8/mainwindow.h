#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPixmap>
#include <QPainter>


#include <fstream>
#include <vector>
#include <string>

#pragma pack(push,1)
struct PCX_header{
    unsigned char id;
    unsigned char version;
    unsigned char coding;
    unsigned char bit_per_pixel;
    unsigned short x_min;
    unsigned short y_min;
    unsigned short x_max;
    unsigned short y_max;
    unsigned short h_res;
    unsigned short v_res;
    unsigned char palette[48];
    unsigned char reserved;
    unsigned char planes;
    unsigned short byte_per_line;
    unsigned short pallete_info;
    unsigned short h_screen_size;
    unsigned short v_screen_size;
    unsigned char filler[54];
};

struct color_info{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    color_info(): red(0), green(0), blue(0){ }
    color_info(int r, int g, int b): red(r), green(g), blue(b){ }
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

private slots:
    void mainFunction(std::string);
    void paintImage(std::vector<std::vector<color_info>>);
};

#endif // MAINWINDOW_H
