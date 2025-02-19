#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->pushButton_cat,&QPushButton::clicked,[this]{ mainFunction("../CAT256.PCX");});
    this->connect(ui->pushButton_num,&QPushButton::clicked,[this]{ mainFunction("../200001.PCX");});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainFunction(std::string file_name){
    std::ifstream file_in(file_name,std::ios::binary);
    PCX_header header;
    file_in.read(reinterpret_cast<char*>(&header),sizeof(PCX_header));

    int width=header.x_max-header.x_min+1, height=header.y_max-header.y_min+1;
    int bytes=header.planes*header.byte_per_line;

    std::vector<unsigned char> decode_rows;
    unsigned char buffer;

    for(int j=0;j<height;++j){
        for(int i=0;i<bytes;){
            file_in.read(reinterpret_cast<char*>(&buffer),1);
            if(buffer>=192){
                int len=buffer-192;
                file_in.read(reinterpret_cast<char*>(&buffer),1);
                while(len--){
                    decode_rows.push_back(buffer);
                    ++i;
                }
            }
            else{
                decode_rows.push_back(buffer);
                ++i;
            }
        }
        if(width%2!=0) decode_rows.pop_back();
    }

    file_in.seekg(-768,std::ios::end);
    color_info color_table[256];
    file_in.read(reinterpret_cast<char*>(color_table),256*sizeof(color_info));

    std::vector<std::vector<color_info>> color_src(height,std::vector<color_info>(width));
    int point=0;
    for(int i=0;i<height;++i){
        for(int j=0;j<width;++j){
            color_src[i][j]=color_table[decode_rows[point]];
            ++point;
        }
    }

    file_in.close();
    paintImage(color_src);
}

void MainWindow::paintImage(std::vector<std::vector<color_info>> src){
    int x=src[0].size(), y=src.size();
    QPixmap pixmap(x,y);
    QPainter painter(&pixmap);

    QColor color;
    for(int i=0;i<y;++i){
        for(int j=0;j<x;++j){
            color.setRgb((int)src[i][j].red,(int)src[i][j].green,(int)src[i][j].blue,255);
            painter.setPen(color);
            painter.drawPoint(j,i);
        }
    }

    ui->label->setPixmap(pixmap);
}
