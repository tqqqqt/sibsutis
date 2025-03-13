#include "dnum_processor.h"

DNum_Processor::DNum_Processor()
{
    last_operator=' ';
    last_operand_first=0;
    last_operand_second=0;
}

void DNum_Processor::execute(QVector<Num*>& arr){
    int temp_first=0, temp_second=0, count_fun=0;

    // calculate all functions
    DNum *num;
    for(int i=0;i<arr.size();){
        if(arr[i]->getType()!=DNum::Object_type::Function){
            ++i;
            continue;
        }

        if(i<=0) throw std::invalid_argument("incorect execute");

        num=static_cast<DNum*>(arr[i-1]);
        temp_first=num->getFirstNum();
        temp_second=num->getSecondNum();

        if(arr[i]->getString()=="Sqr"){
            temp_first*=temp_first;
            temp_second*=temp_second;
        }
        else if(arr[i]->getString()=="Rev") std::swap(temp_first,temp_second);

        num->setNum(std::to_string(temp_first),std::to_string(temp_second));

        arr.erase(arr.begin()+i);
        i-=1;
        if(i<0) i=0;
        count_fun+=1;
    }

    int size=arr.size();
    if(size==1 && count_fun==0 && last_operator!=' '){
        arr.push_back(new DNum);
        arr.back()->addOper(last_operator);
        arr.push_back(new DNum);
        num=static_cast<DNum*>(arr.back());
        num->setNum(std::to_string(last_operand_first),std::to_string(last_operand_second));
        size+=2;
    }

    num=static_cast<DNum*>(arr[0]);
    int result_1=num->getFirstNum(), result_2=num->getSecondNum();
    char oper=' ';

    // calculate result
    for(int i=1;i<size;++i){
        if(arr[i]->getType()==DNum::Object_type::Operator){
            oper=arr[i]->getString().toStdString()[0];
            continue;
        }

        num=static_cast<DNum*>(arr[i]);
        temp_first=num->getFirstNum();
        temp_second=num->getSecondNum();

        if(oper=='+'){
            result_1=(result_1*temp_second)+(temp_first*result_2);
            result_2=(result_2*temp_second);
        }
        else if(oper=='-'){
            result_1=(result_1*temp_second)-(temp_first*result_2);
            result_2=(result_2*temp_second);
        }
        else if(oper=='*'){
            result_1*=temp_first;
            result_2*=temp_second;
        }
        else if(oper=='/'){
            result_1*=temp_second;
            result_2*=temp_first;
        }
    }

    // save last oper and num
    if(oper!=' '){
        last_operator=oper;
        last_operand_first=temp_first;
        last_operand_second=temp_second;
    }

    arr.clear();
    arr.push_back(new DNum);
    num=static_cast<DNum*>(arr.back());
    num->setNum(std::to_string(result_1),std::to_string(result_2));
    num->simplifyNum();
}

void DNum_Processor::clear(){
    last_operator=' ';
    last_operand_first=0;
    last_operand_second=0;
}
