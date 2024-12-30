#include "dkautomat.h"

DKAutomat::DKAutomat()
{
    start_state="";
    end_state="";
    start_chain="";
    end_chain="";
}

void DKAutomat::setAlphabet(std::string _alphabet){
    std::string temp="";
    for(size_t i=0;i<_alphabet.size();i++){
        if(_alphabet[i]==' ') continue;
        if(temp.length()>1) throw std::invalid_argument("incorect alphabet. symbol length > 1");
        if(_alphabet[i]==',' && temp.length()==1){
            alphabet.insert(temp[0]);
            temp="";
            continue;
        }
        temp+=_alphabet[i];
    }
    if(temp.length()>1) throw std::invalid_argument("incorect alphabet. symbol length > 1");
    if(temp.length()==1) alphabet.insert(temp[0]);
    if(alphabet.size()==0) throw std::invalid_argument("incorect alphabet. size = 0");
}

void DKAutomat::checkQuestChain(std::string _quest_chain, std::string _chain_name){
    if(_quest_chain=="") return;
    if(_chain_name!="start" && _chain_name!="end") throw std::invalid_argument("incorect quest chain. not start or end");
    for(size_t i=0;i<_quest_chain.length();i++){
        if(alphabet.count(_quest_chain[i])==0) throw std::invalid_argument("incorect "+_chain_name+" chain. symbol not in alphabet");
    }
    if(_chain_name=="start") start_chain=_quest_chain;
    else end_chain=_quest_chain;
}

void DKAutomat::generateDKA(){
    size_t alpabet_size=alphabet.size();
    size_t curent_num=0, curent_row=0;
    std::string curent_state='q'+std::to_string(curent_num), next_state='q'+std::to_string(curent_num+1);
    start_state=curent_state;
    for(size_t i=0;i<start_chain.length();i++){
        rules.push_back(std::vector<std::string>(alpabet_size+1,"?"));
        rules[curent_row][0]=curent_state;
        size_t index=1;
        for(auto x:alphabet){
            if(start_chain[i]==x) rules[curent_row][index]=next_state;
            else rules[curent_row][index]="-";
            index++;
        }
        curent_num++;
        curent_row++;
        curent_state='q'+std::to_string(curent_num);
        next_state='q'+std::to_string(curent_num+1);
    }
    std::string last_start_state=curent_state, first_end_state=next_state;
    char last_symb='a';
    size_t count_different_symbol=0;
    for(size_t i=0;i<end_chain.length();i++){
        rules.push_back(std::vector<std::string>(alpabet_size+1,"?"));
        rules[curent_row][0]=curent_state;
        size_t index=1;
        for(auto x:alphabet){
            if(end_chain[i]==x) rules[curent_row][index]=next_state;
            else if(i==0 && end_chain[i]!=x) rules[curent_row][index]=curent_state;
            else if(i==1 && end_chain[i-1]==x && end_chain[i]!=x) rules[curent_row][index]=curent_state;
            else if(i>1 && count_different_symbol==0 && x==end_chain[i-1]) rules[curent_row][index]=curent_state;
            else if(i>1 && x==end_chain[0]) rules[curent_row][index]=first_end_state;
            else rules[curent_row][index]=last_start_state;
            index++;
        }
        if(i==0) last_symb=end_chain[i];
        else{
            if(last_symb!=end_chain[i]) count_different_symbol++;
            last_symb=end_chain[i];
        }
        curent_num++;
        curent_row++;
        curent_state='q'+std::to_string(curent_num);
        next_state='q'+std::to_string(curent_num+1);
    }
    rules.push_back(std::vector<std::string>(alpabet_size+1,"?"));
    rules[curent_row][0]=curent_state;
    for(size_t i=1;i<rules[curent_row].size();i++){
        size_t index=1;
        for(auto x:alphabet){
            if(x==end_chain[0]) rules[curent_row][index]=first_end_state;
            else rules[curent_row][index]=last_start_state;
            index++;
        }
    }
    end_state=curent_state;
}

std::vector<std::string> DKAutomat::getHaders(){
    std::vector<std::string> result;
    result.push_back("State");
    std::string temp="";
    for(auto x:alphabet){
        temp+=x;
        result.push_back(temp);
        temp.pop_back();
    }
    return result;
}

std::vector<std::vector<std::string>> DKAutomat::getRules(){
    std::vector<std::vector<std::string>> result=rules;
    return result;
}

std::string DKAutomat::checkChain(std::string _chain){
    std::string curent_state=start_state, result="";
    size_t len=_chain.length(), i=0;
    for(i=0;i<len;i++){
        if(i==0) result+='('+curent_state+','+_chain.substr(i)+')';
        else result+="->("+curent_state+','+_chain.substr(i)+')';
        if(alphabet.count(_chain[i])==0){
            result+=" | no symbol in alphabet";
            return result;
        }
        std::string new_state="?";
        size_t curent_row=0, curent_col=1;
        for(size_t j=0;j<rules.size();j++){
            if(rules[j][0]!=curent_state) continue;
            curent_row=j;
            break;
        }
        for(auto symbol:alphabet){
            if(symbol==_chain[i]) break;
            curent_col++;
        }
        new_state=rules[curent_row][curent_col];
        if(new_state=="-"){
            result+=" | no state to symbol";
            return result;
        }
        curent_state=new_state;
    }
    if(i==len) result+="->("+curent_state+','+_chain.substr(i)+')';
    if(curent_state!=end_state) result+=" | curent state not a final state";
    return result;
}

void DKAutomat::clear(){
    start_chain="";
    end_chain="";
    start_state="";
    end_state="";
    alphabet.clear();
    rules.clear();
}

bool DKAutomat::isDKAGenerate(){
    return rules.size()>0;
}

void DKAutomat::saveDKAInFile(std::string _file_name){
    try{
        std::ofstream file_out(_file_name);
        for(auto row:rules){
            size_t index=1;
            for(auto symbol:alphabet){
                file_out<<('('+row[0]+','+symbol+")=("+row[index++]+")\n");
            }
        }
        file_out.close();
    }
    catch(std::exception){
        throw;
    }
    catch(...){
        return;
    }
}
