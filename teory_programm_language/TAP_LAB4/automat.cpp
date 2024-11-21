#include "automat.h"

automat::automat()
{
    start_rule="";
}

void automat::getNames(std::string _rule, std::string *_cur_rule, std::string *_lent_symb, std::string *_stac_symb, std::string *_new_rule, std::string *_event){
    std::string rule="", lent_symb="", stac_symb="";
    if(_rule.length()==0 || _rule[0]!='(') throw std::invalid_argument("incorect rule. no bracket or len=0");
    size_t cur_p=1, len=_rule.length();
    while(cur_p<len && _rule[cur_p]!=','){
        rule+=_rule[cur_p];
        cur_p++;
    }
    if(rule=="" || cur_p>=len) throw std::invalid_argument("incorect rule. no name");
    cur_p++;
    while(cur_p<len && _rule[cur_p]!=','){
        lent_symb+=_rule[cur_p];
        cur_p++;
    }
    if(lent_symb.length()!=1 || cur_p>=len) throw std::invalid_argument("incorect rule. no lent symbol");
    cur_p++;
    while(cur_p<len && _rule[cur_p]!=')'){
        stac_symb+=_rule[cur_p];
        cur_p++;
    }
    if(stac_symb.length()!=1 || cur_p>=len) throw std::invalid_argument("incorect rule. no stac symbol");
    while(cur_p<len && _rule[cur_p]!='(') cur_p++;
    if(cur_p>=len) throw std::invalid_argument("incorect rule. no start second part");
    cur_p++;
    std::string new_rule="", event="";
    while(cur_p<len && _rule[cur_p]!=','){
        new_rule+=_rule[cur_p];
        cur_p++;
    }
    if(new_rule=="" || cur_p>=len) throw std::invalid_argument("incorect rule. no new rule");
    cur_p++;
    while(cur_p<len && _rule[cur_p]!=')'){
        event+=_rule[cur_p];
        cur_p++;
    }
    if(cur_p>=len || (event.length()==0 || event.length()>2)) throw std::invalid_argument("incorect rule. new event");
    *_cur_rule=rule;
    *_lent_symb=lent_symb;
    *_stac_symb=stac_symb;
    *_new_rule=new_rule;
    *_event=event;
}

void automat::addRule(std::string _rule){
    std::string rule="", lent_symb="", stac_symb="", new_rule="", event="";
    try{
        getNames(_rule,&rule,&lent_symb,&stac_symb,&new_rule,&event);
    }
    catch(...){
        throw;
    }
    if(rule[0]=='@'){
        rule=rule.substr(1);
        if(start_rule!="") throw std::invalid_argument("incorect rule. start rule exist");
        start_rule=rule;
    }
    else if(rule[0]=='^'){
        rule=rule.substr(1);
        end_rule.push_back(rule);
    }
    if(new_rule[0]=='^'){
        new_rule=new_rule.substr(1);
        end_rule.push_back(new_rule);
    }
    if(rules[rule][lent_symb[0]].find(stac_symb[0])!=rules[rule][lent_symb[0]].end()) throw std::invalid_argument("incorect rules. exist");
    rules[rule][lent_symb[0]][stac_symb[0]]=std::make_pair(new_rule,event);
}

void automat::deleteRule(std::string _rule){
    std::string rule="", lent_symb="", stac_symb="", new_rule="", event="";
    try{
        getNames(_rule,&rule,&lent_symb,&stac_symb,&new_rule,&event);
    }
    catch(...){
        throw;
    }
    if(rules[rule][lent_symb[0]].find(stac_symb[0])==rules[rule][lent_symb[0]].end()) throw std::invalid_argument("incorect delete. already delete");
    rules[rule][lent_symb[0]].erase(stac_symb[0]);
    if(rules[rule][lent_symb[0]].size()==0) rules[rule].erase(lent_symb[0]);
    if(rules[rule].size()==0) rules.erase(rule);
    start_rule.clear();
    end_rule.clear();
    for(auto x:rules){
        if(x.first[0]=='@') start_rule=x.first;
        else if(x.first[0]=='^') end_rule.push_back(x.first);
        for(auto xx:x.second){
            for(auto xxx:xx.second){
                if(xxx.second.second[0]=='^') end_rule.push_back(xxx.second.second);
            }
        }
    }
}

std::string automat::work(std::string _chain){
    std::string result="";
    size_t i=0, len=_chain.length()+1;
    if(start_rule.length()==0) throw "no start rule";
    std::string curent_rule=start_rule, stack="Z";
    _chain+=' ';
    while(1){
        if(i==0) result+='('+curent_rule+','+_chain.substr(i,_chain.length()-i-1)+','+stack+')';
        else result+="->("+curent_rule+','+_chain.substr(i,_chain.length()-i-1)+','+stack+')';
        if(_chain[i]==' ' && std::find(end_rule.begin(),end_rule.end(),curent_rule)!=end_rule.end()) return result;
        if(i>=len){
            if(std::find(end_rule.begin(),end_rule.end(),curent_rule)==end_rule.end()) result+=" | rule: "+curent_rule+" not a final rule.";
            return result;
        }
        if(rules[curent_rule].find(_chain[i])==rules[curent_rule].end()){
            result+=" | No rule for symbol ";
            return result;
        }
        if(rules[curent_rule][_chain[i]].find(stack[0])==rules[curent_rule][_chain[i]].end()){
            result+=" | No rule for combination symbol and stack symbol ";
            return result;
        }
        std::string new_rule=rules[curent_rule][_chain[i]][stack[0]].first;
        std::string event=rules[curent_rule][_chain[i]][stack[0]].second;
        if(event.length()==1 && event[0]!=stack[0]){
            result+=" | error symbol stack and event";
            return result;
        }
        if(event.length()!=1){
            if(event=="^E"){
                if(stack.length()==0) throw " | can't delete symbol in empty stack";
                stack=stack.substr(1);
            }
            else if(event[1]==stack[0]) stack=event[0]+stack;
        }
        curent_rule=new_rule;
        if(_chain[i]!=' ') i++;
    }
    return result;
}

void automat::clearAutomat(){
    rules.clear();
    start_rule="";
    end_rule.clear();
}
