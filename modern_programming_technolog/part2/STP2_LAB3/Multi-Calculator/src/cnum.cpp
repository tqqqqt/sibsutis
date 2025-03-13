#include "cnum.h"

CNum::CNum()
{
    type=Object_type::None;
    first_num="";
    second_num="";
    complex_space=false;
    minus_flag_1=1;
    minus_flag_2=1;
    length_first=0;
    length_second=0;
}

void CNum::addNum(char _num){
    if(type!=Object_type::None && type!=Object_type::Num) throw std::invalid_argument("incorect object");

    type=Object_type::Num;
    if(complex_space==false){
        if(length_first==1 && first_num[0]=='0'){
            first_num[0]=_num;
            return;
        }
        first_num+=_num;
        length_first+=1;
    }
    else{
        if(length_second==1 && second_num[0]=='0'){
            second_num[0]=_num;
            return;
        }
        second_num+=_num;
        length_second+=1;
    }
}

void CNum::addOper(char _oper){
    if(type!=Object_type::None) throw std::invalid_argument("incorect object");

    type=Object_type::Operator;
    first_num+=_oper;
    length_first=1;
}

void CNum::addFunc(QString _function){
    if(type!=Object_type::None) throw std::invalid_argument("incorect object");

    type=Object_type::Function;
    first_num+=_function.toStdString();
    length_first=first_num.length();
}

void CNum::setSpace(){
    if(type==Object_type::Operator || type==Object_type::Function) throw std::invalid_argument("incorect object");

    complex_space=true;
    if(type==Object_type::None) type=Object_type::Num;
}

void CNum::delLast(){
    if(type==Object_type::None) return;

    if(type==Object_type::Function || type==Object_type::Operator) clear();
    else{
        if(length_second!=0) second_num.pop_back();
        else if(complex_space==true) complex_space=false;
        else if(length_first!=0) first_num.pop_back();
    }

    length_first=first_num.length();
    length_second=second_num.length();

    if(length_first==0 && length_second==0 && complex_space==false) clear();
}

void CNum::changeZnak(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    if(complex_space==false) minus_flag_1*=-1;
    else minus_flag_2*=-1;
}

void CNum::clear(){
    type=Object_type::None;
    first_num="";
    second_num="";
    complex_space=false;
    minus_flag_1=1;
    minus_flag_2=1;
    length_first=0;
    length_second=0;
}

QString CNum::getString(){
    QString result="";

    if(length_first!=0) result+=QString::fromStdString(first_num);
    if(length_first!=0 && minus_flag_1==-1) result="(-"+result+')';

    if(length_first!=0 && complex_space==true && length_second==0) result+="+i*";
    if(length_first==0 && length_second==0 && complex_space==true) result+="i*";
    else if(length_first!=0 && length_second!=0) result+='+';

    if(length_second!=0 && minus_flag_2==1) result+="i*"+QString::fromStdString(second_num);
    else if(length_second!=0 && minus_flag_2==-1) result+="(-i*"+QString::fromStdString(second_num)+')';

    return result;
}

int CNum::getFirstNum(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    if(length_first==0) return 0;
    return std::stoi(first_num)*minus_flag_1;
}

int CNum::getSecondNum(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    if(length_second==0) return 0;
    return std::stoi(second_num)*minus_flag_2;
}

void CNum::setNum(std::string _first, std::string _second){
    int len_1=_first.length(), len_2=_second.length(), minus_flg_1=1, minus_flg_2=1;

    if(len_1>0 && _first[0]=='-'){
        minus_flg_1=-1;
        _first=_first.substr(1);
        len_1-=1;
    }
    if(len_2>0 && _second[0]=='-'){
        minus_flg_2=-1;
        _second=_second.substr(1);
        len_2-=1;
    }

    for(int i=0;i<len_1;++i){
        if(!(_first[i]>='0' && _first[i]<='9')) throw std::invalid_argument("incorect first num");
    }
    for(int i=0;i<len_2;++i){
        if(!(_second[i]>='0' && _second[i]<='9')) throw std::invalid_argument("incorect second num");
    }

    clear();
    first_num=_first;
    second_num=_second;
    length_first=len_1;
    length_second=len_2;
    if(length_second!=0) complex_space=true;
    type=Object_type::Num;
    minus_flag_1=minus_flg_1;
    minus_flag_2=minus_flg_2;
}

Num* CNum::clone() const{
    return new CNum(*this);
}
