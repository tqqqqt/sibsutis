#include "generator.h"

generator::generator()
{
    alphabet=std::vector<std::string>();
    start_rule="";
    max_lenght_chain=1;
    min_length_chain=1;
}

void generator::setRule(std::string new_rule){
    if(new_rule.find("->")==std::string::npos) throw "Wrong rule format. NO '->' find.";
    std::string rule_name="", temp="";
    size_t point=0, rule_len=new_rule.length();
    while(point<rule_len && new_rule[point]!='-'){
        if(new_rule[point]==' '){
            point++;
            continue;
        }
        temp+=new_rule[point++];
    }
    rule_name=temp;
    if(new_rule.substr(point+2).find("->")!=std::string::npos) throw "Wrong rile. Find second '->'.";
    if(rules.find(rule_name)!=rules.end()) throw "Wrong rule. This rule name exist.";
    temp_rules_name.insert(rule_name);
    temp="";
    int find_option=0, find_stolb=0;
    for(point=point+2;point<rule_len;point++){
        if(new_rule[point]==' ') continue;
        if(new_rule[point]!='|'){
            temp+=new_rule[point];
            continue;
        }
        for(size_t i=0;i<temp.length();i++){
            if(temp[i]>='A' && temp[i]<='Z') temp_rules_name.insert(std::string(1,temp[i]));
            else temp_alphabet.insert(std::string(1,temp[i]));
        }
        rules[rule_name].push_back(temp);
        find_option++;
        find_stolb++;
        temp="";
    }
    if(temp!=""){
        for(size_t i=0;i<temp.length();i++){
            if(temp[i]>='A' && temp[i]<='Z') temp_rules_name.insert(std::string(1,temp[i]));
            else temp_alphabet.insert(std::string(1,temp[i]));
        }
        rules[rule_name].push_back(temp);
        find_option++;
    }
    if(rules[rule_name].size()<(find_stolb+1)) rules[rule_name].push_back(" ");
    if(find_option==0) throw "Wrong rule format. No option find.";
}

std::string generator::getAlphabet(){
    alphabet.clear();
    for(std::string elem:temp_alphabet){
        alphabet.push_back(elem);
    }
    std::string result="{";
    for(size_t i=0;i<alphabet.size();i++){
        if(i==0) result+=alphabet[i];
        else result+=", "+alphabet[i];
    }
    return result+"}";
}

std::string generator::getRulesNames(){
    for(std::string elem:temp_rules_name){
        if(rules.find(elem)==rules.end()) throw "Generator have rules name, but don't have rules.";
    }
    for(auto x:rules){
        if(x.second.size()==0) rules.erase(x.first);
    }
    std::string result="{";
    int count_rules=0;
    for(std::unordered_map<std::string,std::vector<std::string>>::iterator pp=rules.begin();pp!=rules.end();pp++){
        if(count_rules==0) result+=pp->first;
        else result+=", "+pp->first;
        count_rules++;
    }
    return result+"}";
}

std::vector<std::tuple<std::string,std::string,std::vector<int>>> generator::startWork(int chain_len_left, int chain_len_right, std::string start_point, int side){
    if(rules.find(start_point)==rules.end()) throw "No start point in rules";
    min_length_chain=chain_len_left;
    max_lenght_chain=chain_len_right;
    std::vector<std::tuple<std::string,std::string,std::vector<int>>> result;
    createChain(result,start_point,start_point,{},side);
    return result;
}

void generator::createChain(std::vector<std::tuple<std::string,std::string,std::vector<int>>>& result_mas, std::string curent_str, std::string history_str, std::vector<int> history_rule, int side){
    if(curent_str.length()>max_lenght_chain && history_rule.size()>0) return;
    if(curent_str.length()>=min_length_chain && curent_str.length()<=max_lenght_chain){
        int fl=1;
        for(size_t i=0;i<curent_str.length();i++){
            if(curent_str[i]>='A' && curent_str[i]<='Z'){
                fl=0;
                break;
            }
        }
        if(fl){
            result_mas.push_back(std::make_tuple(curent_str,history_str,history_rule));
            return;
        }
    }
    int point=side==1?INT_MAX:INT_MIN;
    /*if(side==1) while(point<curent_str.length() && !(curent_str[point]>='A' && curent_str[point]<='Z')) point++;
    else if(side==2){
        point=curent_str.length()-1;
        while(point>=0 && !(curent_str[point]>='A' && curent_str[point]<='Z')) point--;
    }
    if(point<0 || point>=curent_str.length() || !(curent_str[point]>='A' && curent_str[point]<='Z')) return;
    std::string rules_name=std::string(1,curent_str[point]);
    int p_start=point;
    while(point+1<curent_str.length() && rules.find(rules_name)==rules.end()){
        point++;
        rules_name+=curent_str[point];
    }
    if(rules.find(rules_name)==rules.end()) return;*/
    std::string rules_name="";
    for(const auto& x:rules){
        int temp_point=curent_str.find(x.first);
        if(temp_point!=std::string::npos){
            if(side==1 && point>temp_point){
                point=temp_point;
                rules_name=x.first;
            }
            else if(side==2 && point<temp_point){
                point=temp_point;
                rules_name=x.first;
            }
        }
    }
    if(rules_name=="") return;
    std::string temp="";
    for(size_t j=0;j<rules[rules_name].size();j++){
        history_rule.push_back((int)j);
        temp=curent_str.substr(0,point)+rules[rules_name][j]+curent_str.substr(point+rules_name.length());
        createChain(result_mas,temp,history_str+"->"+temp,history_rule,side);
        history_rule.pop_back();
    }
}

void generator::deleteRule(std::string delete_rule){
    std::string rule_name="";
    int point=0, len_rule=delete_rule.length();
    while(point<len_rule && delete_rule[point]!='-'){
        if(delete_rule[point]==' '){
            point++;
            continue;
        }
        rule_name+=delete_rule[point++];
    }
    if(rules.find(rule_name)==rules.end()) throw "I don't know how but rules not exist.";
    rules.erase(rule_name);
    temp_alphabet.clear();
    temp_rules_name.clear();
    for(std::unordered_map<std::string,std::vector<std::string>>::iterator iter=rules.begin();iter!=rules.end();iter++){
        temp_rules_name.insert(iter->first);
        for(int i=0;i<iter->second.size();i++){
            for(int j=0;j<iter->second[i].length();j++){
                if(iter->second[i][j]>='A' && iter->second[i][j]<='Z') temp_rules_name.insert(std::string(1,iter->second[i][j]));
                else if(iter->second[i][j]!=' ') temp_alphabet.insert(std::string(1,iter->second[i][j]));
            }
        }
    }
}

void generator::clearAllData(){
    rules.clear();
    temp_alphabet.clear();
    temp_rules_name.clear();
    alphabet.clear();
    start_rule="";
    max_lenght_chain=1;
}

std::unordered_map<std::string,std::vector<std::string>> generator::getRules(){
    return rules;
}
