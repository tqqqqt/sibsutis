#include "avtomat.h"

avtomat::avtomat()
{
    start_rules="";
}

void avtomat::addRule(std::string _rule){
    std::string name="";
    bool final=false, start=false;
    int i=0, length=_rule.length();
    while(i<length && _rule[i]!='='){
        if(_rule[i]=='^'){
            final=true;
            i++;
            continue;
        }
        if(_rule[i]=='@'){
            start=true;
            i++;
            continue;
        }
        name+=_rule[i++];
    }
    if(name=="") throw std::invalid_argument("No rule name.");
    if(rules.find(name)!=rules.end()) throw std::invalid_argument("Rules already exist.");
    if(final==true && start==true) throw std::invalid_argument("Rule can't be start and finish rule.");
    if(final) final_rules.insert(name);
    if(start) start_rules=name;
    std::string temp_value="", temp_rule="";
    std::vector<char> temp_alphabet;
    std::unordered_map<char,std::string> temp_mas_rule;
    int start_bracket=0;
    for(i;i<length;i++){
        if(_rule[i]=='^' || _rule[i]=='@') throw std::invalid_argument("Incorect use '@' or '^'.");
        if(_rule[i]==' ' || _rule[i]==',') continue;
        if(_rule[i]=='('){
            if(start_bracket==1) throw std::invalid_argument("Incorect use '(' in rule.");
            start_bracket=1;
            continue;
        }
        if(_rule[i]==':'){
            if(start_bracket!=1) throw std::invalid_argument("Incorect use ':' in rule.");
            start_bracket=2;
            continue;
        }
        if(_rule[i]==')'){
            if(start_bracket!=2) throw std::invalid_argument("Incorect use ')' in rule.");
            if(temp_value.length()!=1) throw std::invalid_argument("Incorect value for rule.");
            start_bracket=0;
            temp_mas_rule[temp_value[0]]=temp_rule;
            temp_alphabet.push_back(temp_value[0]);
            temp_value="";
            temp_rule="";
            continue;
        }
        if(start_bracket==1){
            temp_value+=_rule[i];
            continue;
        }
        if(start_bracket==2){
            temp_rule+=_rule[i];
            continue;
        }
    }
    if(temp_value!="" || temp_value!="" || start_bracket!=0) throw std::invalid_argument("Incorect rule form.");
    rules[name]=temp_mas_rule;
    for(int i=0;i<temp_alphabet.size();i++) alphabet.insert(temp_alphabet[i]);
}

void avtomat::deleteRule(std::string _rule){
    std::string temp_name="";
    int i=0, length=_rule.length();
    bool start=false, final=false;
    while(i<length && _rule[i]!='='){
        if(_rule[i]=='^'){
            final=true;
            i++;
            continue;
        }
        if(_rule[i]=='@'){
            start=true;
            i++;
            continue;
        }
        temp_name+=_rule[i++];
    }
    if(temp_name=="") throw std::invalid_argument("No rules name.");
    if(rules.find(temp_name)==rules.end()) throw std::invalid_argument("Rules not exist.");
    rules.erase(temp_name);
    if(start) start_rules="";
    if(final) final_rules.erase(temp_name);
    alphabet.clear();
    for(auto x:rules){
        for(auto y:x.second) alphabet.insert(y.first);
    }
}

std::string avtomat::getAlphabet(){
    std::string result="{";
    for(char x : alphabet){
        if(result.length()==1) result+=x;
        else result+=", "+std::string(1,x);
    }
    result+='}';
    return result;
}

std::string avtomat::work(std::string _chain){
    if(start_rules=="") throw std::invalid_argument("No start nule.");
    if(final_rules.size()==0) throw std::invalid_argument("No final rules.");
    int curent_index=0, max_len=_chain.length();
    std::string curent_rule=start_rules, history="", temp="", result="";
    while(1){
        if(history.length()==0) temp='('+curent_rule+','+_chain.substr(curent_index)+')';
        else temp="->("+curent_rule+','+_chain.substr(curent_index)+')';
        if(curent_index>=max_len){
            if(final_rules.count(curent_rule)){
                result=history+temp;
                break;
            }
            else{
                temp+=" | No final rule: "+curent_rule;
                result=history+temp;
                break;
            }
        }
        if(rules.find(curent_rule)==rules.end()){
            temp+=" | No rule: "+curent_rule;
            result=history+temp;
            break;
        }
        if(rules[curent_rule].find(_chain[curent_index])==rules[curent_rule].end()){
            temp+=" | No rule for symbol '"+std::string(1,_chain[curent_index])+"' in rule "+curent_rule;
            result=history+temp;
            break;
        }
        curent_rule=rules[curent_rule][_chain[curent_index]];
        curent_index++;
        history+=temp;
    }
    return result;
}

void avtomat::clearRule(){
    rules.clear();
    start_rules="";
    final_rules.clear();
    alphabet.clear();
}
