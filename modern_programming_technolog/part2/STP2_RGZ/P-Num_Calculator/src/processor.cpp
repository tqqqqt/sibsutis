#include "processor.h"

Processor::Processor(){
    last_operator=' ';
    last_operand=0;
}

void Processor::changeSystem(QVector<PNum>& arr, int old_system, int new_system){
    double temp=0;
    int size=arr.size();
    std::string temp_num="";
    for(int i=0;i<size;++i){
        if(arr[i].getType()!=PNum::Object_type::Num) continue;

        temp=converter.convertTo10(arr[i].getNum().toStdString(),old_system);
        if(round_mode==true) temp=std::round(temp);
        temp_num=converter.convertFrom10(temp,new_system,10);
        arr[i].setNum(temp_num);
    }
}

void Processor::execute(QVector<PNum>& arr, int system){
    double temp=0;

    // calculate all functions
    std::string temp_num="";
    for(int i=0;i<arr.size();){
        if(arr[i].getType()!=PNum::Object_type::Function){
            ++i;
            continue;
        }

        if(i<=0) throw std::invalid_argument("incorect execute");
        temp=converter.convertTo10(arr[i-1].getNum().toStdString(),system);
        if(round_mode==true) temp=std::round(temp);

        if(arr[i].getString()=="Sqr") temp*=temp;
        else if(arr[i].getString()=="Rev"){
            if(temp==0) throw std::invalid_argument("div 0");
            temp=1/temp;
        }

        temp_num=converter.convertFrom10(temp,system,10);
        arr[i-1].setNum(temp_num);

        arr.erase(arr.begin()+i);
        i-=1;
        if(i<0) i=0;
    }

    int size=arr.size();
    if(size==1 && last_operator!=' '){
        arr.push_back(PNum());
        arr.back().addOper(last_operator);
        arr.push_back(PNum());
        arr.back().setNum(converter.convertFrom10(last_operand,system,10));
        size+=2;
    }

    double result=converter.convertTo10(arr[0].getNum().toStdString(),system);
    char oper=' ';

    // calculate result
    for(int i=1;i<size;++i){
        if(arr[i].getType()==PNum::Object_type::Operator){
            oper=arr[i].getString().toStdString()[0];
            continue;
        }

        temp=converter.convertTo10(arr[i].getNum().toStdString(),system);

        if(oper=='+') result+=temp;
        else if(oper=='-') result-=temp;
        else if(oper=='*') result*=temp;
        else if(oper=='/'){
            if(temp==0) throw std::invalid_argument("div 0");
            result/=temp;
        }
    }
    if(round_mode==true) result=std::round(result);

    // save last oper and num
    if(oper!=' '){
        last_operator=oper;
        last_operand=temp;
    }

    arr.clear();
    arr.push_back(PNum());
    arr.back().setNum(converter.convertFrom10(result,system,10));
}

void Processor::setMode(bool _mode){
    round_mode=_mode;
}

void Processor::clear(){
    last_operator=' ';
    last_operand=0;
}
