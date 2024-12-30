#ifndef DKAUTOMAT_H
#define DKAUTOMAT_H

#include <string>
#include <vector>
#include <set>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <fstream>

class DKAutomat
{
private:
    std::set<char> alphabet;
    std::string start_chain, end_chain;
    std::string start_state, end_state;
    std::vector<std::vector<std::string>> rules;

public:
    DKAutomat();

    void setAlphabet(std::string);
    void checkQuestChain(std::string, std::string);
    void generateDKA();
    bool isDKAGenerate();
    void saveDKAInFile(std::string);
    std::vector<std::string> getHaders();
    std::vector<std::vector<std::string>> getRules();
    std::string checkChain(std::string);
    void clear();
};

#endif // DKAUTOMAT_H
