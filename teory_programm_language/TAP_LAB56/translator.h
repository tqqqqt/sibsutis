#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <tuple>
#include <unordered_map>
#include <set>
#include <vector>

class translator
{
private:
    std::unordered_map</*state*/std::string,std::unordered_map</*symbol lent*/char,std::unordered_map</*stack symb*/char,std::tuple<std::string,std::string,std::string>>>> rules;
    std::string start_rule;
    std::set<std::string> end_rule;
    std::vector<std::string> start_history, end_history;

    void getNames(std::string,std::string*,std::string*,std::string*,std::string*,std::string*,std::string*);
public:
    translator();

    void addRule(std::string);
    void deleteRule(std::string);
    std::string translateChain(std::string);
    void clearTranslator();
};

#endif // TRANSLATOR_H
