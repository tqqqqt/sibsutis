#include "numbermath.h"

int MaxNumber(std::string num1, std::string num2){
    size_t dot1P=num1.find(','), dot2P=num2.find(',');
    size_t rightPointNum1=dot1P==std::string::npos?num1.length():dot1P, rightPointNum2=dot2P==std::string::npos?num2.length():dot2P;
    if(rightPointNum1>rightPointNum2 || (num1[0]!='-' && num2[0]=='-')) return -1;
    if(rightPointNum1<rightPointNum2 || (num1[0]=='-' && num2[0]!='-')) return 1;
    for(size_t i=0;i<rightPointNum1;i++){
        if(num1[i]=='-' && num2[i]=='-') continue;
        if((num1[i]-'0')>(num2[i]-'0')) return -1;
        if((num1[i]-'0')<(num2[i]-'0')) return 1;
    }
    //if(dot1P==std::string::npos && dot2P==std::string::npos) return 0;
    for(size_t i=rightPointNum1+1;i<std::max(num1.length(),num2.length());i++){
        int tempNum1=0, tempNum2=0;
        if(i<num1.length()) tempNum1=num1[i]-'0';
        if(i<num2.length()) tempNum2=num2[i]-'0';
        if(tempNum1>tempNum2) return -1;
        if(tempNum1<tempNum2) return 1;
    }
    return 0;
}

int FindMultiplier(std::string num1, std::string num2){
    int result=1;
    for(int i=2;i<10;i++){
        if(MaxNumber(MathMul(num2,std::to_string(i)),num1)>=0) result=i;
        else break;
    }
    return result;
}

std::string MathSum(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-') return MathNeg(num2,num1.substr(1));
    if(num1[0]!='-' && num2[0]=='-') return MathNeg(num1,num2.substr(1));
    if(num1[0]=='-' && num2[0]=='-') return '-'+MathSum(num1.substr(1),num2.substr(1));
    size_t lenNum1=num1.length(), lenNum2=num2.length(), dot1P=num1.find(','), dot2P=num2.find(',');
    int carry=0, pointNum1=dot1P==std::string::npos?lenNum1-1:dot1P-1, pointNum2=dot2P==std::string::npos?lenNum2-1:dot2P-1;
    std::string result="";
    if(dot1P!=std::string::npos && dot2P!=std::string::npos){
        size_t tempPointNum1=lenNum1-1, tempPointNum2=lenNum2-1;
        while((tempPointNum1-dot1P)>=1 || (tempPointNum2-dot2P)>=1){
            if((tempPointNum1-dot1P)==(tempPointNum2-dot2P)) carry=carry+(num1[tempPointNum1--]-'0')+(num2[tempPointNum2--]-'0');
            else if((tempPointNum1-dot1P)>(tempPointNum2-dot2P)) carry=carry+(num1[tempPointNum1--]-'0');
            else if((tempPointNum1-dot1P)<(tempPointNum2-dot2P)) carry=carry+(num2[tempPointNum2--]-'0');
            result=std::to_string(carry%10)+result;
            carry/=10;
        }
        result=','+result;
    }
    else if(dot1P!=std::string::npos) result=','+num1.substr(dot1P+1);
    else if(dot2P!=std::string::npos) result=','+num2.substr(dot2P+1);
    while(pointNum1>=0 || pointNum2>=0){
        if(pointNum1>=0 && pointNum2>=0) carry=carry+(num1[pointNum1--]-'0')+(num2[pointNum2--]-'0');
        else if(pointNum1>=0) carry=carry+(num1[pointNum1--]-'0');
        else if(pointNum2>=0) carry=carry+(num2[pointNum2--]-'0');
        result=std::to_string(carry%10)+result;
        carry=carry/10;
    }
    if(carry) result=std::to_string(carry%10)+result;
    return result;
}

std::string MathNeg(std::string num1, std::string num2){
    if(num1[0]!='-' && num2[0]=='-') return MathSum(num1,num2.substr(1));
    if(num1[0]=='-' && num2[0]!='-') return '-'+MathSum(num1.substr(1),num2);
    if(num1[0]=='-' && num2[0]=='-') return MathNeg(num2.substr(1),num1.substr(1));
    int minusFlg=MaxNumber(num1,num2);
    if(minusFlg==1) std::swap(num1,num2);
    else if(minusFlg==0) return "0";
    std::string result="";
    int carry=0, dot1P=num1.find(','), dot2P=num2.find(',');;
    if((dot1P!=std::string::npos && dot2P!=std::string::npos) || (dot1P==std::string::npos && dot2P!=std::string::npos)){
        int tempPointNum1=num1.length()-1, tempPointNum2=num2.length()-1;
        while((tempPointNum1-dot1P)>=1 && (tempPointNum2-dot2P)>=1){
            int tempNum1=0, tempNum2=0;
            if((tempPointNum1-dot1P)==(tempPointNum2-dot2P)){
                tempNum1=num1[tempPointNum1--]-'0';
                tempNum2=num2[tempPointNum2--]-'0';
            }
            else if(dot1P==std::string::npos) tempNum2=num2[tempPointNum2--]-'0';
            else if(dot2P==std::string::npos) tempNum1=num1[tempPointNum1--]-'0';
            else if((tempPointNum1-dot1P)>(tempPointNum2-dot2P)) tempNum1=num1[tempPointNum1--]-'0';
            else if((tempPointNum1-dot1P)<(tempPointNum2-dot2P)) tempNum2=num2[tempPointNum2--]-'0';
            if(carry){
                tempNum1--;
                carry=0;
            }
            if(tempNum1<tempNum2){
                result=std::to_string((tempNum1+10)-tempNum2)+result;
                carry=1;
            }
            else result=std::to_string(tempNum1-tempNum2)+result;
        }
        result=','+result;
    }
    else if(dot1P!=std::string::npos && dot2P==std::string::npos) result=','+num1.substr(dot1P+1);
    int pointNum1=dot1P==std::string::npos?num1.length()-1:dot1P-1, pointNum2=dot2P==std::string::npos?num2.length()-1:dot2P-1;
    while(pointNum1>=0 || pointNum2>=0){
        int tempNum1=0, tempNum2=0;
        if(pointNum1>=0) tempNum1=num1[pointNum1--]-'0';
        if(pointNum2>=0) tempNum2=num2[pointNum2--]-'0';
        if(carry){
            carry=0;
            tempNum1--;
        }
        if(tempNum1<tempNum2){
            result=std::to_string((tempNum1+10)-tempNum2)+result;
            carry=1;
        }
        else result=std::to_string(tempNum1-tempNum2)+result;
    }
    while(result.length() && result[0]=='0') result.erase(0,1);
    if(result=="") return "0";
    else if(result[0]==',') result='0'+result;
    if(minusFlg==1) result='-'+result;
    return result;
}

std::string MathMul(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]!='-') return '-'+MathMul(num1.substr(1),num2);
    if(num1[0]!='-' && num2[0]=='-') return '-'+MathMul(num1,num2.substr(1));
    if(num1[0]=='-' && num2[0]=='-'){
        num1=num1.substr(1);
        num2=num2.substr(1);
    }
    int countNumDot=0, lenNum1=num1.length(), lenNum2=num2.length();
    size_t dot1P=num1.find(','), dot2P=num2.find(',');
    if((num1[0]=='0' && dot1P==std::string::npos) || (num2[0]=='0' && dot2P==std::string::npos)) return "0";
    if(dot1P!=std::string::npos){
        countNumDot+=lenNum1-1-dot1P;
        num1.erase(dot1P,1);
        lenNum1--;
    }
    if(dot2P!=std::string::npos){
        countNumDot+=lenNum2-1-dot2P;
        num2.erase(dot2P,1);
        lenNum2--;
    }
    std::string result="";
    int carry=0;
    for(int i=lenNum2-1, index=0;i>=0;i--, index++){
        carry=0;
        for(int j=lenNum1-1, curIndex=index;j>=0;j--,curIndex++){
            if(curIndex>=result.length()){
                carry=(num1[j]-'0')*(num2[i]-'0')+carry;
                result+=std::to_string(carry%10);
            }
            else{
                carry=(num1[j]-'0')*(num2[i]-'0')+(result[curIndex]-'0')+carry;
                result[curIndex]='0'+(carry%10);
            }
            carry/=10;
        }
        if(carry) result+=std::to_string(carry);
    }
    std::reverse(result.begin(),result.end());
    if(countNumDot) result.insert(result.begin()+(result.length()-countNumDot),',');
    return result;
}

std::string MathDiv(std::string num1, std::string num2){
    if(num2.length()==1 && num2[0]=='0') return "Error div 0";
    size_t lenNum1=num1.length(), lenNum2=num2.length();
    size_t dot1P=num1.find(','), dot2P=num2.find(',');
    if(dot1P!=std::string::npos){
        for(int i=0;i<(lenNum1-1-dot1P);i++) num2+='0';
        num1.erase(dot1P,1);
        while(num1.length() && num1[0]=='0') num1.erase(0,1);
        if(num1=="") return "0";
    }
    if(dot2P!=std::string::npos){
        for(int i=0;i<(lenNum2-1-dot2P);i++) num1+='0';
        num2.erase(dot2P,1);
        while(num2.length() && num2[0]=='0') num2.erase(0,1);
        if(num2=="") return "Error div 0";
    }
    std::string curentNum="";
    std::vector<char> tempResult;
    size_t index=0;
    for(const char& x:num1){
        curentNum+=x;
        while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
        if(MaxNumber(curentNum,num2)==1){
            if(index) index++;
            continue;
        }
        if(index==0){
            size_t temp=curentNum.length();
            tempResult=std::vector<char>((1+(num1.length()-temp)),'0');
        }
        int carry=FindMultiplier(curentNum,num2);
        tempResult[index++]='0'+carry;
        curentNum=MathNeg(curentNum,MathMul(num2,std::to_string(carry)));
    }
    if(index==0) tempResult.push_back('0');
    while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
    if(curentNum!=""){
        tempResult.push_back(',');
        std::string tempNum="";
        int countNums=11;
        while(countNums){
            curentNum+='0';
            while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
            if(curentNum=="") break;
            if(MaxNumber(curentNum,num2)==1){
                if(countNums>1) tempResult.push_back('0');
                else tempNum+=('0');
                countNums--;
                continue;
            }
            int carry=FindMultiplier(curentNum,num2);
            if(countNums>1) tempResult.push_back('0'+carry);
            else tempNum+=('0'+carry);
            curentNum=MathNeg(curentNum,MathMul(num2,std::to_string(carry)));
            countNums--;
        }
        if(curentNum!=""){
            if((tempNum[0]-'0')>4){
                int point=tempResult.size()-1;
                while(point){
                    int carry=(tempResult[point]-'0')+1;
                    tempResult[point--]='0'+(carry%10);
                    carry/=10;
                    if(carry==0) break;
                }
            }
        }
    }
    curentNum="";
    for(const char& x:tempResult) curentNum+=x;
    if(curentNum.length()==0 || (curentNum.length()>2 && curentNum[0]=='0' && curentNum[1]!=',')) return "0";
    return curentNum;
}

std::string MathDivOld(std::string num1, std::string num2){
    if(num1[0]=='0') return "0";
    if(num2[0]=='0') return "Error div 0";
    if(num1[0]=='-' && num2[0]!='-') return '-'+MathDivOld(num1.substr(1),num2);
    if(num1[0]!='-' && num2[0]=='-') return '-'+MathDivOld(num1,num2.substr(1));
    if(num1[0]=='-' && num2[0]=='-'){
        num1=num1.substr(1);
        num2=num2.substr(1);
    }
    size_t lenNum2=num2.length();
    if(num1.length()<lenNum2) return "0";
    std::string curentNum="";
    std::vector<int> tempResult;
    size_t index=0;
    for(const char& x:num1){
        curentNum+=x;
        while(curentNum.length() && curentNum[0]=='0') curentNum.erase(0,1);
        if(MaxNumber(curentNum,num2)==1){
            if(index) index++;
            continue;
        }
        if(index==0){
            size_t temp=curentNum.length();
            tempResult=std::vector<int>((1+(num1.length()-temp)),0);
        }
        int carry=FindMultiplier(curentNum,num2);
        tempResult[index++]=carry;
        curentNum=MathNeg(curentNum,MathMul(num2,std::to_string(carry)));
    }
    curentNum="";
    for(const int& x:tempResult) curentNum+=('0'+x);
    if(curentNum.length()==0 || (curentNum.length() && curentNum[0]=='0')) return "0";
    return curentNum;
}


std::string MathModDiv(std::string num1, std::string num2){
    if(num1[0]=='-' && num2[0]=='-'){
        std::string temp=MathModDiv(num1.substr(1),num2.substr(1));
        if(temp=="0") return temp;
        return "-"+temp;
    }
    else if(num1[0]=='-'){
        std::string temp=MathModDiv(num1.substr(1),num2);
        if(temp=="0") return temp;
        return "-"+temp;
    }
    else if(num2[0]=='-'){
        std::string temp=MathModDiv(num1,num2.substr(1));
        if(temp=="0") return temp;
        return "-"+temp;
    }
    if(MaxNumber(num1,num2)==1) return num1;
    if(MaxNumber(num1,num2)==0) return "0";
    return MathNeg(num1,MathMul(num2,MathDivOld(num1,num2)));
}

std::string MathPow(std::string num1, std::string num2){
    std::string temp_num="1", mul_num=num1;
    while(MaxNumber(temp_num,num2)!=0){
        num1=MathMul(num1,mul_num);
        temp_num=MathSum(temp_num,"1");
    }
    return num1;
}
