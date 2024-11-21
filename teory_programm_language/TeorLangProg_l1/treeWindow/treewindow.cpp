#include "treewindow.h"
#include "ui_treewindow.h"

TreeWindow::TreeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TreeWindow)
{
    ui->setupUi(this);
    QMessageBox message_box;
    message_box.critical(this,"Error","No data in constructor.");
    message_box.setFixedSize(500,200);
    this->close();
}

TreeWindow::TreeWindow(QString new_start_symbol, std::vector<int> history_rules, class generator* my_generator, int side, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::TreeWindow)
{
    ui->setupUi(this);
    generator=my_generator;
    rules_mas=my_generator->getRules();
    rules_history=history_rules;
    curent_index=0;
    curent_side=side;
    start_symbol=new_start_symbol.toStdString();

    connect(ui->action,SIGNAL(triggered()),this,SLOT(reDrawTree()));

    int height=QApplication::activeWindow()->height(), width=QApplication::activeWindow()->width();

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black,2));
    drawTree(painter,width/2,10,new_start_symbol.toStdString());

    ui->label->setPixmap(pixmap);
}

TreeWindow::~TreeWindow()
{
    delete ui;
}

void TreeWindow::drawTree(QPainter& painter, int x, int y, std::string curent_symb){
    if(curent_symb=="") return;
    bool is_not_rules=rules_mas.find(curent_symb)==rules_mas.end();
    if(!is_not_rules) painter.setBrush(QBrush(Qt::transparent));
    else painter.setBrush(QBrush(Qt::green));
    painter.drawEllipse(x,y,25,25);
    painter.setBrush(QBrush(Qt::black));
    painter.drawText(x+8,y+14,QString::fromStdString(curent_symb));
    if(is_not_rules) return;
    int curent_symbol_index=rules_history[curent_index++], len_rule_str=rules_mas[curent_symb][curent_symbol_index].length();
    if(curent_side==1){
        for(int i=0;i<len_rule_str;i++){
            drawTree(painter,(x-(30*len_rule_str))+(40*(i+1)),y+50,std::string(1,rules_mas[curent_symb][curent_symbol_index][i]));
            painter.drawLine(x+14,y+25,((x-(30*len_rule_str))+(40*(i+1)))+14,y+50);
        }
    }
    else if(curent_side==2){
        for(int i=len_rule_str-1;i>=0;i--){
            drawTree(painter,(x+(30*len_rule_str))-(40*(len_rule_str-i)),y+50,std::string(1,rules_mas[curent_symb][curent_symbol_index][i]));
            painter.drawLine(x+14,y+25,((x+(30*len_rule_str))-(40*(len_rule_str-i)))+14,y+50);
        }
    }
}

void TreeWindow::reDrawTree(){
    curent_index=0;
    int height=QApplication::activeWindow()->height()-30, width=QApplication::activeWindow()->width()-30;

    QPixmap pixmap(width,height);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black,2));
    drawTree(painter,width/2,10,start_symbol);

    ui->label->setPixmap(pixmap);
}
