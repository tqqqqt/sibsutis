#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>

#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <set>
#include <utility>

namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraphWindow(QWidget *parent = nullptr);
    ~GraphWindow();

    void setData(std::vector<std::string>, std::vector<std::vector<std::string>>);
    void draw();

private:
    Ui::GraphWindow *ui;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> data;

    void drawArrow(QPainter&,int,int,int);
};

#endif // GRAPHWINDOW_H
