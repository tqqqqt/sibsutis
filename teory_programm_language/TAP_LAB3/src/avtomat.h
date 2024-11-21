#ifndef AVTOMAT_H
#define AVTOMAT_H

#include <string>
#include <unordered_map>
#include <set>
#include <utility>
#include <vector>

class avtomat
{
private:
    std::unordered_map<std::string,std::unordered_map<char,std::string>> rules;
    std::string start_rules;
    std::set<std::string> final_rules;
    std::set<char> alphabet;

public:
    avtomat();
    void addRule(std::string);
    void deleteRule(std::string);
    void clearRule();
    std::string getAlphabet();
    std::string work(std::string);

};

#endif // AVTOMAT_H
