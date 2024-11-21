#include <iostream>
#include <string>

#include "TEditor.h"

bool checkInput(std::string _input) {
    if(_input.length()!=1) return false;
    if(!(_input[0]-'0'>=1 && _input[0]-'0'<=9)) return false;
    return true;
}

int main()
{
    std::string input="";
    TEditor editor=TEditor();
    while (1) {
        input="";
        std::cout<<"\nValue complex = "<<editor.value() << '\n';
        std::cout<<"Menu:\n1-add num\n2-add null\n3-change minus\n4-add '+i*'\n5-add '.'\n6-del last symbol\n7-clear\n8-set value\n9-exit\n";
        while (!checkInput(input)) {
            std::cout << "->";
            std::cin >> input;
        }
        if(input[0]=='9') break;
        try {
            editor.redact(std::stoi(input));
        }
        catch (std::exception &exp) {
            std::cout<<"Error: "<<exp.what()<<'\n';
        }
    }
    return 0;
}
