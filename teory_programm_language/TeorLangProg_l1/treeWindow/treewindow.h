#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <QMessageBox>

#include <string>
#include <vector>
#include <unordered_map>

#include "../src/generator.h"

namespace Ui {
class TreeWindow;
}

class TreeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TreeWindow(QWidget *parent = nullptr);
    TreeWindow(QString start_symbol, std::vector<int> rules_history, generator* my_generator, int side, QWidget *parent=nullptr);
    ~TreeWindow();

private:
    Ui::TreeWindow *ui;
    generator *generator;
    std::unordered_map<std::string,std::vector<std::string>> rules_mas;
    std::vector<int> rules_history;
    std::string start_symbol;
    int curent_index, curent_side;

    void drawTree(QPainter& painter, int x, int y, std::string curent_symb);

private slots:
    void reDrawTree();
};

#endif // TREEWINDOW_H
