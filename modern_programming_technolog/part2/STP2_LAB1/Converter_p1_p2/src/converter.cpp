#include "converter.h"

Converter::Converter(){ }

std::string Converter::convertFrom10(double num, int p, int c){
    std::string result="";
    if(num<0){
        result+='-';
        num=std::abs(num);
    }
    double flt_part=0, int_part=0;
    flt_part=std::modf(num,&int_part);

    if(int_part>=INT_MAX || int_part<=INT_MIN) throw std::invalid_argument("out of range");

    result+=intToP(static_cast<int>(int_part),p);
    if(flt_part>0){
        result+='.';
        result+=fltToP(flt_part,p,c);
    }

    return result;
}

double Converter::convertTo10(std::string p_num, int p){
    double result=0;
    short minus_flg=1;
    if(p_num[0]=='-'){
        minus_flg=-1;
        p_num=p_num.substr(1);
    }

    size_t dot_position=p_num.find('.');
    if(dot_position!=std::string::npos){
        std::string float_part=p_num.substr(dot_position+1);
        result=strToFlt(float_part,p,static_cast<int>(float_part.length())*-1);
        p_num=p_num.substr(0,dot_position);
    }
    result+=strToFlt(p_num,p,0);

    return result*minus_flg;
}


// convert from 10
char Converter::intToChar(int num){
    if(num>=0 && num<=9) return ('0'+num);
    num-=10;
    return ('A'+num);
}

std::string Converter::intToP(int num, int p){
    if(num==0) return "0";

    std::string result="";

    int temp_num=0, div_res=0;
    while(num>=p){
        div_res=num/p;
        temp_num=num-(div_res*p);
        result+=intToChar(temp_num);
        num=div_res;
    }
    result+=intToChar(num);

    std::reverse(result.begin(),result.end());
    return result;
}

std::string Converter::fltToP(double num, int p, int c){
    std::string result="";

    double temp_int=0;
    while(c--){
        num*=p;
        num=std::modf(num,&temp_int);
        result+=intToChar(static_cast<int>(temp_int));
        if(std::ceil(num)==0) break;
    }

    return result;
}

// convert to 10
int Converter::charToInt(char num){
    if(num>='0' && num<='9') return (num-'0');
    return 10+(num-'A');
}

double Converter::strToFlt(std::string num, int p, double width){
    double result=0;
    int temp_num=0;
    size_t length=num.length();

    for(int i=length-1;i>=0;--i){
        temp_num=charToInt(num[i]);
        result+=temp_num*std::pow(p,width);
        width++;
    }

    return result;
}
