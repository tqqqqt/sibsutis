#ifndef AUTOMAT_H
#define AUTOMAT_H

#include <exception>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>

class automat
{
private:
    std::unordered_map</*status*/std::string,std::unordered_map</*lent symbol*/char,std::unordered_map</*stack symbol*/char,std::pair<std::string,std::string>>>> rules;
    std::vector<std::string> end_rule;
    std::string start_rule;

    void getNames(std::string,std::string*,std::string*,std::string*,std::string*,std::string*);

public:
    automat();
    void addRule(std::string);
    void deleteRule(std::string);
    std::string work(std::string);
    void clearAutomat();
};

#endif // AUTOMAT_H
