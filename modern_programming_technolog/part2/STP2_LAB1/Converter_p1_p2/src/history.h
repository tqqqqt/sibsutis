#ifndef HISTORY_H
#define HISTORY_H

#include <QString>
#include <QVector>

class History
{
private:
    struct Record{
        int p_1;
        int p_2;
        QString number_1;
        QString number_2;

        Record() : p_1(10), p_2(10), number_1(""), number_2(""){ }
        Record(int _p1, int _p2, QString _number1, QString _number2) : p_1(_p1), p_2(_p2){
            number_1=_number1;
            number_2=_number2;
        }

        QString toString(){
            std::string result="s: "+std::to_string(p_1)+"->"+std::to_string(p_2)+" | n: ";
            return QString::fromStdString(result)+number_1+"->"+number_2;
        }
    };

    QVector<Record> history;

public:
    History();

    Record at(int);
    void addRecord(int, int, QString, QString);
    void clear();
    int count();
};

#endif // HISTORY_H
