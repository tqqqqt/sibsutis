#include "pnum.h"

PNum::PNum()
{
    type=Object_type::None;
    count_dot=0;
    length=0;
    text="";
}

void PNum::addNum(char _num){
    if(type!=Object_type::None && type!=Object_type::Num) throw std::invalid_argument("incorect object");

    type=Object_type::Num;
    if(length==1 && text[0]=='0'){
        text[0]=_num;
        return;
    }
    if(length!=0 && text.back()==')'){
        text.pop_back();
        text+=_num;
        text+=')';
    }
    else text+=_num;

    length+=1;
}

void PNum::addOper(char _oper){
    if(type!=Object_type::None) throw std::invalid_argument("incorect object");

    type=Object_type::Operator;
    text+=_oper;
    length=1;
}

void PNum::addFunc(QString _function){
    if(type!=Object_type::None) throw std::invalid_argument("incorect object");

    type=Object_type::Function;
    text=_function.toStdString();
    length=text.length();
}

void PNum::changeZnak(){
    if(type!=Object_type::Num) throw std::invalid_argument("incorect object");

    if(length>0 && text[0]=='(' && text.back()==')'){
        text=text.substr(2);
        text.pop_back();
    }
    else text="(-"+text+')';

    length=text.length();
}

void PNum::addDot(){
    if(count_dot!=0 || type!=Object_type::Num) return;

    if(length>0 && text[0]=='('){
        text.pop_back();
        text+='.';
        text+=')';
    }
    else text+='.';

    length+=1;
    count_dot++;
}

void PNum::delLast(){
    if(type==Object_type::None) return;

    if(type==Object_type::Function || type==Object_type::Operator) text.clear();
    else{
        int close_bracket=0;
        if(length!=0 && text.back()==')'){
            close_bracket=1;
            text.pop_back();
        }

        if(length!=0 && text.back()=='.') count_dot--;
        text.pop_back();

        if(close_bracket==1) text+=')';
    }

    length=text.length();
    if(length==0 || (length==3 && text[0]=='(')) clear();
}

void PNum::clear(){
    type=Object_type::None;
    count_dot=0;
    length=0;
    text.clear();
}

QString PNum::getString(){
    return QString::fromStdString(text);
}

QString PNum::getNum(){
    if(type!=Object_type::Num || length<=0) throw std::invalid_argument("incorect object");

    if(text[0]!='(') return QString::fromStdString(text);
    return QString::fromStdString(text.substr(1,length-2));
}

void PNum::setNum(std::string _num){
    int find_dot=0, len=_num.length(), minus_flg=0;

    if(len>0 && _num[0]=='-'){
        minus_flg=1;
        _num=_num.substr(1);
        len-=1;
    }

    for(int i=0;i<len;++i){
        if(_num[i]!='.' && !(_num[i]>='0' && _num[i]<='9') && !(_num[i]>='A' && _num[i]<='F')) throw std::invalid_argument("incorect num");
        if(_num[i]=='.') find_dot++;
    }
    if(find_dot>1) throw std::invalid_argument("incorect num");

    clear();
    if(find_dot!=0) count_dot=1;
    text=_num;
    length=len;
    type=Object_type::Num;
    if(minus_flg==1) changeZnak();
}

Num* PNum::clone() const{
    return new PNum(*this);
}
