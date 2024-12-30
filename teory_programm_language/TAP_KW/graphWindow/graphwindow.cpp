#include "graphwindow.h"
#include "ui_graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
}

GraphWindow::~GraphWindow()
{
    delete ui;
}

void GraphWindow::setData(std::vector<std::string> _headers, std::vector<std::vector<std::string>> _data){
    headers=_headers;
    data=_data;
}

void GraphWindow::draw(){
    int height=QApplication::activeWindow()->height(), width=QApplication::activeWindow()->width();
    QPixmap pixmap(width,height);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black,2));
    std::unordered_map<std::string,int> data_pos;
    std::unordered_map<std::string,std::unordered_map<std::string,std::string>> data_mem;
    int cur_x=50, cur_y=90;
    for(size_t i=0;i<data.size();i++){
        if(i==(data.size()-1)) painter.setBrush(QBrush(Qt::green));
        else painter.setBrush(QBrush(Qt::transparent));
        painter.drawEllipse(cur_x,cur_y,30,30);
        painter.setBrush(QBrush(Qt::black));
        painter.drawText(cur_x+6,cur_y+14,QString::fromStdString(data[i][0]));
        data_pos[data[i][0]]=cur_x;
        for(size_t j=1;j<data[i].size();j++){
            if(data[i][j]=="-") continue;
            if(data_mem[data[i][0]][data[i][j]].length()==0) data_mem[data[i][0]][data[i][j]]+=headers[j];
            else data_mem[data[i][0]][data[i][j]]+=','+headers[j];
        }
        cur_x+=75;
    }
    std::set<std::pair<std::string,std::string>> mem_line;
    int main_y=cur_y, down_arc_y=cur_y+30+50;
    for(auto cur_state:data_mem){
        cur_x=data_pos[cur_state.first];
        cur_y=main_y;
        down_arc_y=cur_y+30+50;
        size_t cur_num=std::stoul(cur_state.first.substr(1)), next_num=0;
        for(auto next_state:cur_state.second){
            next_num=std::stoul(next_state.first.substr(1));
            if(cur_state.first==next_state.first){
                painter.drawArc(cur_x+8,main_y-26,10,100,30*16,120*16);
                painter.drawText(cur_x+6,main_y-30,QString::fromStdString(next_state.second));
            }
            else if(std::abs((int)(cur_num-next_num))==1){
                if(mem_line.count({cur_state.first,next_state.first}) || mem_line.count({next_state.first,cur_state.first})) cur_y+=10;
                if(cur_num>next_num){
                    painter.drawLine(cur_x,cur_y,data_pos[next_state.first]+30,cur_y);
                    drawArrow(painter,data_pos[next_state.first]+30,cur_y,-1);
                    painter.drawText(cur_x-((cur_x-(data_pos[next_state.first]+30))*0.6),cur_y-2,QString::fromStdString(next_state.second));
                }
                else{
                    painter.drawLine(cur_x+30,cur_y,data_pos[next_state.first],cur_y);
                    drawArrow(painter,data_pos[next_state.first],cur_y,1);
                    painter.drawText((cur_x+30)+((data_pos[next_state.first]-(cur_x+30))/3),cur_y-2,QString::fromStdString(next_state.second));
                }
                mem_line.insert({cur_state.first,next_state.first});
                cur_y+=10;
            }
            else{
                if(cur_num>next_num){
                    int center_x=(cur_x+15)-((cur_x+15)-(data_pos[next_state.first]+15))/2;
                    painter.drawLine(cur_x+5,main_y+30,center_x,down_arc_y);
                    painter.drawLine(center_x,down_arc_y,data_pos[next_state.first]+25,main_y+30);
                    drawArrow(painter,data_pos[next_state.first]+25,main_y+30,-2);
                    painter.drawText(center_x,down_arc_y+8,QString::fromStdString(next_state.second));
                }
                else{
                    int center_x=(data_pos[next_state.first]+15)-((data_pos[next_state.first]+15)-(cur_x+15))/2;
                    painter.drawLine(cur_x+5,main_y+30,center_x,down_arc_y);
                    painter.drawLine(center_x,down_arc_y,data_pos[next_state.first]+25,main_y+30);
                    drawArrow(painter,data_pos[next_state.first]+15,main_y+30,2);
                    painter.drawText(center_x,down_arc_y+8,QString::fromStdString(next_state.second));
                }
                down_arc_y+=10;
            }
        }
    }
    ui->label->setPixmap(pixmap);
}

void GraphWindow::drawArrow(QPainter& painter, int end_x, int end_y, int mode){
    switch(mode){
    case 1:
        painter.drawLine(end_x,end_y,end_x-10,end_y-10);
        painter.drawLine(end_x,end_y,end_x-10,end_y+10);
        break;
    case 2:
        painter.drawLine(end_x,end_y,end_x-5,end_y+5);
        painter.drawLine(end_x,end_y,end_x+5,end_y+5);
        break;
    case -1:
        painter.drawLine(end_x,end_y,end_x+10,end_y-10);
        painter.drawLine(end_x,end_y,end_x+10,end_y+10);
        break;
    case -2:
        painter.drawLine(end_x,end_y,end_x-5,end_y+5);
        painter.drawLine(end_x,end_y,end_x+5,end_y+5);
        break;
    }
}
