#include "dnum.h"

DNum::DNum()
{
    type=Object_type::None;
    first_num="";
    second_num="";
    drob_space=false;
    minus_flag=1;
    length_first=0;
    length_second=0;
}

void DNum::addNum(char _num){
    if(type!=Object_type::None && type!=Object_type::Num) throw std::invalid_argument("incorect object");

    type=Object_type::Num;
    if(drob_space==false){
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

void DNum::addOper(char _oper){
    if(type!=Object_type::None) throw std::invalid_argument("incorect object");

    type=Object_type::Operator;
    first_num+=_oper;
    length_first=1;
}

void DNum::addFunc(QString _function){
    if(type!=Object_type::None) throw std::invalid_argument("incorect object");

    type=Object_type::Function;
    first_num+=_function.toStdString();
    length_first=first_num.length();
}

void DNum::setSpace(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    drob_space=true;
}

void DNum::delLast(){
    if(type==Object_type::None) return;

    if(type==Object_type::Function || type==Object_type::Operator) clear();
    else{
        if(length_second!=0) second_num.pop_back();
        else if(drob_space==true) drob_space=false;
        else if(length_first!=0) first_num.pop_back();
    }

    length_first=first_num.length();
    length_second=second_num.length();

    if(length_first==0) clear();
}

void DNum::changeZnak(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    minus_flag*=-1;
}

void DNum::clear(){
    type=Object_type::None;
    first_num="";
    second_num="";
    drob_space=false;
    minus_flag=1;
    length_first=0;
    length_second=0;
}

QString DNum::getString(){
    if(length_first==0) return "";

    QString result="";
    result+=QString::fromStdString(first_num);
    if(drob_space==true) result+='|';
    if(length_second!=0) result+=QString::fromStdString(second_num);

    if(minus_flag==-1) result="(-"+result+')';
    return result;
}

int DNum::getFirstNum(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    return std::stoi(first_num)*minus_flag;
}
int DNum::getSecondNum(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    if(length_second==0) return 1;
    return std::stoi(second_num);
}

void DNum::setNum(std::string _first, std::string _second){
    int len_1=_first.length(), len_2=_second.length(), minus_flg=0;

    if(len_1>0 && _first[0]=='0'){
        clear();
        addNum('0');
        return;
    }
    if(len_2>0 && _second[0]=='0') throw std::invalid_argument("div 0");

    if((len_1>0 && _first[0]=='-') && (len_2>0 && _second[0]=='-')){
        _first=_first.substr(1);
        len_1-=1;
        _second=_second.substr(1);
        len_2-=1;
    }
    else if(len_1>0 && _first[0]=='-'){
        minus_flg=1;
        _first=_first.substr(1);
        len_1-=1;
    }
    else if(len_2>0 && _second[0]=='-'){
        minus_flg=1;
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
    if(length_second!=0) drob_space=true;
    type=Object_type::Num;
    if(minus_flg==1) changeZnak();
}

int DNum::gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}

void DNum::simplifyNum(){
    if(length_first==0 || length_second==0) return;

    int num_1=std::stoi(first_num), num_2=std::stoi(second_num);
    int gcd_num=gcd(num_1,num_2);

    if(gcd_num==1) return;

    num_1/=gcd_num;
    num_2/=gcd_num;

    first_num=std::to_string(num_1);
    second_num=std::to_string(num_2);
}

Num* DNum::clone() const{
    return new DNum(*this);
}
