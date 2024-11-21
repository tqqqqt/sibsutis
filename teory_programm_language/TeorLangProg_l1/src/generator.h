#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>
#include <tuple>

class generator
{
private:
    std::unordered_map<std::string,std::vector<std::string>> rules;
    std::vector<std::string> alphabet;
    std::string start_rule;
    int min_length_chain, max_lenght_chain;
    std::set<std::string> temp_alphabet, temp_rules_name;

public:
    generator();
    void setRule(std::string new_rule);
    std::vector<std::tuple<std::string,std::string,std::vector<int>>> startWork(int chain_len_left, int chain_len_right, std::string start_point, int side);
    std::string getAlphabet();
    std::string getRulesNames();
    void createChain(std::vector<std::tuple<std::string,std::string,std::vector<int>>>& result_mas, std::string curent_str, std::string history_str, std::vector<int> history_rule, int side);
    void deleteRule(std::string delete_rule);
    std::unordered_map<std::string,std::vector<std::string>> getRules();
    void clearAllData();

};

#endif // GENERATOR_H
