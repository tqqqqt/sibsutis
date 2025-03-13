#include "cnum_processor.h"

CNum_Processor::CNum_Processor()
{
    last_operator=' ';
    last_operand_first=0;
    last_operand_second=0;
}

void CNum_Processor::execute(QVector<Num*>& arr){
    int temp_first=0, temp_second=0, count_fun=0;

    // calculate all functions
    CNum *num;
    for(int i=0;i<arr.size();){
        if(arr[i]->getType()!=CNum::Object_type::Function){
            ++i;
            continue;
        }

        if(i<=0) throw std::invalid_argument("incorect execute");

        num=static_cast<CNum*>(arr[i-1]);
        temp_first=num->getFirstNum();
        temp_second=num->getSecondNum();

        if(arr[i]->getString()=="Sqr"){
            int n_1=temp_first;
            temp_first=(temp_first*temp_first)-(temp_second*temp_second);
            temp_second=2*n_1*temp_second;
        }
        else if(arr[i]->getString()=="Rev"){
            if(temp_first==0 && temp_second==0) throw std::invalid_argument("div 0");

            int n_1=temp_first, n_2=temp_second;
            temp_first=n_1/(n_1*n_1+n_2*n_2);
            temp_second=-1*n_2/(n_1*n_1+n_2*n_2);
        }

        num->setNum(std::to_string(temp_first),std::to_string(temp_second));

        arr.erase(arr.begin()+i);
        i-=1;
        if(i<0) i=0;
        count_fun+=1;
    }

    int size=arr.size();
    if(size==1 && count_fun==0 && last_operator!=' '){
        arr.push_back(new CNum);
        arr.back()->addOper(last_operator);
        arr.push_back(new CNum);
        num=static_cast<CNum*>(arr.back());
        num->setNum(std::to_string(last_operand_first),std::to_string(last_operand_second));
        size+=2;
    }

    num=static_cast<CNum*>(arr[0]);
    int result_1=num->getFirstNum(), result_2=num->getSecondNum();
    char oper=' ';

    // calculate result
    for(int i=1;i<size;++i){
        if(arr[i]->getType()==CNum::Object_type::Operator){
            oper=arr[i]->getString().toStdString()[0];
            continue;
        }

        num=static_cast<CNum*>(arr[i]);
        temp_first=num->getFirstNum();
        temp_second=num->getSecondNum();

        if(oper=='+'){
            result_1+=temp_first;
            result_2+=temp_second;
        }
        else if(oper=='-'){
            result_1-=temp_first;
            result_2-=temp_second;
        }
        else if(oper=='*'){
            int n_1=0, n_2=0, n_3=0, n_4=0;
            n_1=result_1*temp_first;
            n_2=result_1*temp_second;
            n_3=result_2*temp_first;
            n_4=result_2*temp_second;
            result_1=n_1-n_4;
            result_2=n_2+n_3;
        }
        else if(oper=='/'){
            if(temp_first==0 && temp_second==0) throw std::invalid_argument("div 0");

            int n_1=result_1, n_2=result_2;
            result_1=(n_1*temp_first+n_2*temp_second)/(temp_first*temp_first+temp_second*temp_second);
            result_2=(n_2*temp_first-n_1*temp_second)/(temp_first*temp_first+temp_second*temp_second);
        }
    }

    // save last oper and num
    if(oper!=' '){
        last_operator=oper;
        last_operand_first=temp_first;
        last_operand_second=temp_second;
    }

    arr.clear();
    arr.push_back(new CNum);
    num=static_cast<CNum*>(arr.back());
    num->setNum(std::to_string(result_1),std::to_string(result_2));
}

void CNum_Processor::clear(){
    last_operator=' ';
    last_operand_first=0;
    last_operand_second=0;
}
