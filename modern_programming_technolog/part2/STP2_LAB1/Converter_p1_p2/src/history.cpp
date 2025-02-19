#include "history.h"

History::History(){ }

History::Record History::at(int _index){
    if(_index>=history.size()) throw std::invalid_argument("incorect index");

    return history[_index];
}

void History::addRecord(int _p1, int _p2, QString _number1, QString _number2){
    History::Record temp(_p1,_p2,_number1,_number2);
    history.push_back(temp);
}

void History::clear(){
    history.clear();
}

int History::count(){
    return history.size();
}
