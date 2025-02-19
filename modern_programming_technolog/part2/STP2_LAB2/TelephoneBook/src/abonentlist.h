#ifndef ABONENTLIST_H
#define ABONENTLIST_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <iterator>

class AbonentList
{
private:
    std::multimap<std::string, std::string> list;

public:
    AbonentList();

    void add(std::string, std::string);
    int findName(std::string);

    void clear();
    std::vector<std::string> getAll();
    void deleteElem(int);
    void updateElem(int, std::string, std::string);

    void getElem(int, std::string&, std::string&);
};

#endif // ABONENTLIST_H
