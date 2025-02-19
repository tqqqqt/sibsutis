#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->pushButton,&QPushButton::clicked,[this]{ mainFunc("../CAR.bmp"); });
    this->connect(ui->pushButton_2,&QPushButton::clicked,[this]{ mainFunc("../CAT16.BMP"); });
    this->connect(ui->pushButton_3,&QPushButton::clicked,[this]{ mainFunc("../CAT256.BMP"); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintImage(std::vector<std::vector<color_info>> image_src){
    QPixmap pixmap(image_src[0].size(),image_src.size());
    QPainter painter(&pixmap);
    QColor color;

    for(size_t i=0;i<image_src.size();++i){
        for(size_t j=0;j<image_src[i].size();++j){
            color.setRgb((int)image_src[i][j].red,(int)image_src[i][j].green,(int)image_src[i][j].blue,255);
            painter.setPen(color);
            painter.drawPoint(j,i);
        }
    }

    ui->label->setPixmap(pixmap);
}

void MainWindow::mainFunc(std::string file_name){
    std::ifstream file_in(file_name,std::ios::binary);

    file_header header_of_file;
    v3_header header_v3_of_file;
    file_in.read(reinterpret_cast<char*>(&header_of_file),sizeof(file_header));
    file_in.read(reinterpret_cast<char*>(&header_v3_of_file),sizeof(v3_header));

    std::vector<std::vector<color_info>> image_src;

    if(header_v3_of_file.bit_per_pixel==8){
        color_info color_table[256];
        int bytes_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4, read_count=0;

        file_in.read(reinterpret_cast<char*>(color_table),256*sizeof(color_info));
        file_in.seekg(header_of_file.bm_offset,std::ios::beg);
        std::vector<std::vector<unsigned char>> old_rows;
        std::vector<unsigned char> buffer(bytes_row);
        while(1){
            file_in.read(reinterpret_cast<char*>(buffer.data()),bytes_row);
            read_count=file_in.gcount();
            if(read_count>0) old_rows.push_back(buffer);
            else break;
        }

        for(int i=old_rows.size()-1;i>=0;--i){
            image_src.push_back(std::vector<color_info>());
            for(int j=0;j<old_rows[i].size();++j){
                image_src.back().push_back(color_table[old_rows[i][j]]);
            }
        }
    }
    else if(header_v3_of_file.bit_per_pixel==4){
        color_info color_table[16];
        int bytes_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4, read_count=0;

        file_in.read(reinterpret_cast<char*>(color_table),16*sizeof(color_info));
        file_in.seekg(header_of_file.bm_offset,std::ios::beg);
        std::vector<std::vector<unsigned char>> old_rows;
        std::vector<unsigned char> buffer(bytes_row);
        while(1){
            file_in.read(reinterpret_cast<char*>(buffer.data()),bytes_row);
            read_count=file_in.gcount();
            if(read_count>0) old_rows.push_back(buffer);
            else break;
        }

        for(int i=old_rows.size()-1;i>=0;--i){
            image_src.push_back(std::vector<color_info>());
            for(int j=0;j<old_rows[i].size();++j){
                image_src.back().push_back(color_table[(old_rows[i][j]>>4)&0x0F]);
                image_src.back().push_back(color_table[old_rows[i][j]&0x0F]);
            }
        }
    }
    else if(header_v3_of_file.bit_per_pixel==24){
        int bytes_row=std::floor((header_v3_of_file.bit_per_pixel*header_v3_of_file.width+31)/32)*4, read_count=0;

        std::vector<std::vector<unsigned char>> rows;
        std::vector<unsigned char> buffer(bytes_row);
        while(1){
            file_in.read(reinterpret_cast<char*>(buffer.data()),bytes_row);
            read_count=file_in.gcount();
            if(read_count>0) rows.push_back(buffer);
            else break;
        }

        for(int i=rows.size()-1;i>=0;--i){
            image_src.push_back(std::vector<color_info>());
            for(size_t j=0;j<rows[0].size();j+=3){
                image_src.back().push_back(color_info(rows[i][j],rows[i][j+1],rows[i][j+2],0));
            }
        }
    }

    paintImage(image_src);
    file_in.close();
}
