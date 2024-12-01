#include "translator.h"

translator::translator()
{

}

void translator::getNames(std::string _rule, std::string* _state, std::string* _lent_symb, std::string* _stack_symb, std::string* _new_state, std::string* _stack_event, std::string* _translate_event){
    std::string state="", lent_symb="", stac_symb="";
    if(_rule.length()==0 || _rule[0]!='(') throw std::invalid_argument("incorent rule. no start bracket");
    size_t p=1, len=_rule.length();
    while(p<len && _rule[p]!=',') state+=_rule[p++];
    if(state=="" || p>=len) throw std::invalid_argument("incorect rule. no curent state");
    p++;
    while(p<len && _rule[p]!=',') lent_symb+=_rule[p++];
    if(lent_symb.length()!=1 || p>=len) throw std::invalid_argument("incorect rule. no curent symbol lent");
    p++;
    while(p<len && _rule[p]!=')') stac_symb+=_rule[p++];
    if(stac_symb.length()!=1 || p>=len) throw std::invalid_argument("incorect rule. no curent stac symbol");
    while(p<len && _rule[p]!='(') p++;
    if(p>=len) throw std::invalid_argument("incorect rule. no start second part");
    p++;
    std::string new_state="", event_stack="", event_trans="";
    while(p<len && _rule[p]!=',') new_state+=_rule[p++];
    if(new_state=="" || p>=len) throw std::invalid_argument("incorect rule. no new state");
    p++;
    while(p<len && _rule[p]!=',') event_stack+=_rule[p++];
    if(event_stack=="" || p>=len) throw std::invalid_argument("incorect rule. no stack event");
    p++;
    while(p<len && _rule[p]!=')') event_trans+=_rule[p++];
    if(event_trans=="" || _rule[p]!=')') throw std::invalid_argument("incorect rule. no translate event");
    while(event_trans.length() && event_trans[0]==' ') event_trans=event_trans.substr(1);
    if(p!=(len-1)) throw std::invalid_argument("incorect rule. incorect symbol after close bracket");
    *_state=state;
    *_lent_symb=lent_symb;
    *_stack_symb=stac_symb;
    *_new_state=new_state;
    *_stack_event=event_stack;
    *_translate_event=event_trans;
}

void translator::addRule(std::string _new_rule){
    std::string state="", lent_symb="", stac_symb="";
    std::string new_state="", stac_event="", translate_event="";
    try {
        getNames(_new_rule,&state,&lent_symb,&stac_symb,&new_state,&stac_event,&translate_event);
    }
    catch (...) {
        throw;
    }
    if(state[0]=='@'){
        start_history.push_back(state);
        state=state.substr(1);
        if(state=="") throw std::invalid_argument("incorect rule. incorect use start symbol");
        if(start_rule!="") throw std::invalid_argument("incorect rule. start rule exist");
        start_rule=state;
    }
    if(new_state[0]=='^'){
        end_history.push_back(new_state);
        new_state=new_state.substr(1);
        if(new_state=="") throw std::invalid_argument("incorect rule. incorect use end symbol");
        end_rule.insert(new_state);
    }
    if(rules[state][lent_symb[0]].find(stac_symb[0])!=rules[state][lent_symb[0]].end()) throw std::invalid_argument("incorect rule. rule exist");
    rules[state][lent_symb[0]][stac_symb[0]]=std::make_tuple(new_state,stac_event,translate_event);
}

void translator::deleteRule(std::string _delete_rule){
    std::string state="", lent_symb="", stac_symb="";
    std::string new_state="", stac_event="", translate_event="";
    try {
        getNames(_delete_rule,&state,&lent_symb,&stac_symb,&new_state,&stac_event,&translate_event);
    }
    catch (...) {
        throw;
    }
    if(state[0]=='@') state=state.substr(1);
    if(new_state[0]=='^') new_state=new_state.substr(1);
    if(rules[state][lent_symb[0]].find(stac_symb[0])==rules[state][lent_symb[0]].end()) throw std::invalid_argument("incorect delete. already delete");
    rules[state][lent_symb[0]].erase(stac_symb[0]);
    if(rules[state][lent_symb[0]].size()==0) rules[state].erase(lent_symb[0]);
    if(rules[state].size()==0) rules.erase(state);
    start_rule.clear();
    end_rule.clear();
    for(size_t i=0;i<start_history.size();){
        int count=0;
        for(auto x:rules){
            if(x.first==start_history[i].substr(1)){
                count++;
                start_rule=x.first;
                break;
            }
        }
        if(count==0) start_history.erase(start_history.begin(),start_history.begin()+(i+1));
        else i++;
    }
    for(size_t i=0;i<end_history.size();){
        int count=0;
        for(auto x:rules){
            for(auto xx:x.second){
                for(auto xxx:xx.second){
                    if(std::get<0>(xxx.second)==end_history[i].substr(1)){
                        count++;
                        end_rule.insert(std::get<0>(xxx.second));
                    }
                }
            }
        }
        if(count==0) end_history.erase(end_history.begin(),end_history.begin()+(i+1));
        else i++;
    }
}

std::string translator::translateChain(std::string _chain){
    std::string result="";
    size_t i=0, len=_chain.length()+1;
    if(start_rule.length()==0) throw std::invalid_argument("no start rule");
    if(end_rule.size()==0) throw std::invalid_argument("no end rule");
    std::string curent_rule=start_rule, stack="Z", translate="";
    _chain+=' ';
    while(1){
        if(i==0) result+='('+curent_rule+','+_chain.substr(i,_chain.length()-i-1)+','+stack+','+translate+')';
        else result+="->("+curent_rule+','+_chain.substr(i,_chain.length()-i-1)+','+stack+','+translate+')';
        if(_chain[i]==' ' && end_rule.count(curent_rule)) break;
        if(i>=len){
            if(end_rule.count(curent_rule)==0) result+=" | curent rule not a final";
            break;
        }
        if(rules[curent_rule].find(_chain[i])==rules[curent_rule].end()){
            result+=" | No rule for symbol ";
            break;
        }
        if(rules[curent_rule][_chain[i]].find(stack[0])==rules[curent_rule][_chain[i]].end()){
            result+=" | no rule for coombination symbol and stack symbol";
            break;
        }
        std::string new_state=std::get<0>(rules[curent_rule][_chain[i]][stack[0]]);
        std::string event_stack=std::get<1>(rules[curent_rule][_chain[i]][stack[0]]);
        std::string event_translate=std::get<2>(rules[curent_rule][_chain[i]][stack[0]]);
        if(event_stack.length()==1 && event_stack[0]!=stack[0]){
            result+=" | error not add symbol in stack. stack symbol != event symbol";
            break;
        }
        if(event_stack.length()!=1){
            if(event_stack=="^E"){
                if(stack.length()==0){
                    result+=" | cant delete symbol, stack empty";
                    break;
                }
                stack=stack.substr(1);
            }
            else if(event_stack[1]==stack[0]) stack=event_stack[0]+stack;
            else if(event_stack[1]!=stack[0]){
                result+=" | cant add in stack, symbol != stack symbol";
                break;
            }
        }
        translate+=event_translate;
        curent_rule=new_state;
        if(_chain[i]!=' ') i++;
    }
    return result;
}

void translator::clearTranslator(){
    rules.clear();
    start_rule="";
    end_rule.clear();
}
