#include "pnum_processor.h"

PNum_Processor::PNum_Processor()
{
    last_operator=' ';
    last_operand=0;
    curent_system=10;
}

void PNum_Processor::changeSystem(QVector<Num*>& arr, int old_system, int new_system){
    double temp=0;
    int size=arr.size();
    std::string temp_num="";
    PNum *num;
    for(int i=0;i<size;++i){
        if(arr[i]->getType()!=PNum::Object_type::Num) continue;

        num=static_cast<PNum*>(arr[i]);

        temp=converter.convertTo10(num->getNum().toStdString(),old_system);
        temp_num=converter.convertFrom10(temp,new_system,10);
        num->setNum(temp_num);
    }
}

void PNum_Processor::execute(QVector<Num*>& arr){
    double temp=0;

    // calculate all functions
    std::string temp_num="";
    PNum* num;
    for(int i=0;i<arr.size();){
        if(arr[i]->getType()!=PNum::Object_type::Function){
            ++i;
            continue;
        }

        if(i<=0) throw std::invalid_argument("incorect execute");

        num=static_cast<PNum*>(arr[i-1]);
        temp=converter.convertTo10(num->getNum().toStdString(),curent_system);

        if(arr[i]->getString()=="Sqr") temp*=temp;
        else if(arr[i]->getString()=="Rev"){
            if(temp==0) throw std::invalid_argument("div 0");
            temp=1/temp;
        }

        temp_num=converter.convertFrom10(temp,curent_system,10);
        num->setNum(temp_num);

        arr.erase(arr.begin()+i);
        i-=1;
        if(i<0) i=0;
    }

    int size=arr.size();
    if(size==1 && last_operator!=' '){
        arr.push_back(new PNum());
        arr.back()->addOper(last_operator);
        arr.push_back(new PNum());
        num=static_cast<PNum*>(arr.back());
        num->setNum(converter.convertFrom10(last_operand,curent_system,10));
        size+=2;
    }

    num=static_cast<PNum*>(arr[0]);
    double result=converter.convertTo10(num->getNum().toStdString(),curent_system);
    char oper=' ';

    // calculate result
    for(int i=1;i<size;++i){
        if(arr[i]->getType()==PNum::Object_type::Operator){
            oper=arr[i]->getString().toStdString()[0];
            continue;
        }

        num=static_cast<PNum*>(arr[i]);
        temp=converter.convertTo10(num->getNum().toStdString(),curent_system);

        if(oper=='+') result+=temp;
        else if(oper=='-') result-=temp;
        else if(oper=='*') result*=temp;
        else if(oper=='/'){
            if(temp==0) throw std::invalid_argument("div 0");
            result/=temp;
        }
    }

    // save last oper and num
    if(oper!=' '){
        last_operator=oper;
        last_operand=temp;
    }

    arr.clear();
    arr.push_back(new PNum());
    num=static_cast<PNum*>(arr.back());
    num->setNum(converter.convertFrom10(result,curent_system,10));
}

void PNum_Processor::setSystem(int _system){
    curent_system=_system;
}

void PNum_Processor::clear(){
    last_operator=' ';
    last_operand=0;
}
