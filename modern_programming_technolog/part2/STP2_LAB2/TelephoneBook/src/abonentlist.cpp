#include "abonentlist.h"

AbonentList::AbonentList(){ }

void AbonentList::add(std::string _name, std::string _telephone){
    list.emplace(_name, _telephone);
}

int AbonentList::findName(std::string _name){
    std::multimap<std::string,std::string>::iterator iter=list.find(_name);
    if(iter==list.end()) return -1;
    return std::distance(list.begin(),iter);
}

void AbonentList::clear(){
    list.clear();
}

std::vector<std::string> AbonentList::getAll(){
    std::vector<std::string> result;
    for(auto x:list){
        result.push_back(x.first);
        result.push_back(x.second);
    }
    return result;
}

void AbonentList::getElem(int index, std::string& _name, std::string& _phone){
    if(index>=list.size()) throw std::invalid_argument("incorect index");

    std::multimap<std::string,std::string>::iterator iter=list.begin();
    std::advance(iter,index);
    _name=iter->first;
    _phone=iter->second;
}

void AbonentList::deleteElem(int index){
    if(index>=list.size()) throw std::invalid_argument("incorect index");

    std::multimap<std::string,std::string>::iterator iter=list.begin();
    std::advance(iter,index);
    list.erase(iter);
}

void AbonentList::updateElem(int index, std::string _name, std::string _phone){
    if(index>=list.size()) throw std::invalid_argument("incorect index");

    std::multimap<std::string,std::string>::iterator iter=list.begin();
    std::advance(iter,index);
    list.erase(iter);
    list.emplace(_name,_phone);
}
