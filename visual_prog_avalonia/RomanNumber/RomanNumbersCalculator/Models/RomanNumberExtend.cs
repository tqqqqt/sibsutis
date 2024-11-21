using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RomanNumbersCalculator.Models
{
    internal class RomanNumberExtend:RomanNumber
    {
        private int oper;
        private string text = "";
        public RomanNumberExtend(string numberepresent)
        {
            oper = 0;
            int flag = 1;
            for(int i = 0; i < numberepresent.Length; i += 1)
            {
                if (i == numberepresent.Length-1)
                {
                    if (numberepresent[i] == 'I')
                    {
                        if (flag == 1) romanNumber1 += 1;
                        else romanNumber2 += 1;
                    }
                    else if (numberepresent[i] == 'V')
                    {
                        if (flag == 1) romanNumber1 += 5;
                        else romanNumber2 += 5;
                    }
                    else if (numberepresent[i] == 'X')
                    {
                        if (flag == 1) romanNumber1 += 10;
                        else romanNumber2 += 10;
                    }
                    else if (numberepresent[i] == 'C')
                    {
                        if (flag == 1) romanNumber1 += 100;
                        else romanNumber2 += 100;
                    }
                    else if (numberepresent[i] == 'D')
                    {
                        if (flag == 1) romanNumber1 += 500;
                        else romanNumber2 += 500;
                    }
                    else if (numberepresent[i] == 'M')
                    {
                        if (flag == 1) romanNumber1 += 1000;
                        else romanNumber2 += 1000;
                    }
                }
                else if (numberepresent[i] == 'I'){
                    if (numberepresent[i + 1] != 'V' && numberepresent[i + 1] != 'X')
                    {
                        if (flag == 1) romanNumber1 += 1;
                        else romanNumber2 += 1;
                    }
                    else if (numberepresent[i + 1] == 'V')
                    {
                        if (flag == 1) romanNumber1 += 4;
                        else romanNumber2 += 4;
                        i += 1;
                    }
                    else if (numberepresent[i + 1] == 'X')
                    {
                        if (flag == 1) romanNumber1 += 9;
                        else romanNumber2 += 9;
                        i += 1;
                    }
                }
                else if (numberepresent[i] == 'V')
                {
                    if (flag == 1) romanNumber1 += 5;
                    else romanNumber2 += 5;
                }
                else if (numberepresent[i] == 'X')
                {
                    if (numberepresent[i+1]!='L' && numberepresent[i+1] != 'C')
                    {
                        if (flag == 1) romanNumber1 += 10;
                        else romanNumber2 += 10;
                    }
                    else if (numberepresent[i + 1] == 'L')
                    {
                        if (flag == 1) romanNumber1 += 40;
                        else romanNumber2 += 40;
                        i += 1;
                    }
                    else if (numberepresent[i + 1] == 'C')
                    {
                        if (flag == 1) romanNumber1 += 90;
                        else romanNumber2 += 90;
                        i += 1;
                    }
                }
                else if (numberepresent[i] == 'L')
                {
                    if (flag == 1) romanNumber1 += 50;
                    else romanNumber2 += 50;
                }
                else if (numberepresent[i] == 'C')
                {
                    if (numberepresent[i+1]!='D' && numberepresent[i + 1] != 'M')
                    {
                        if (flag == 1) romanNumber1 += 100;
                        else romanNumber2 += 100;
                    }
                    else if (numberepresent[i + 1] == 'D')
                    {
                        if (flag == 1) romanNumber1 += 400;
                        else romanNumber2 += 400;
                        i += 1;
                    }
                    else if (numberepresent[i + 1] == 'M')
                    {
                        if (flag == 1) romanNumber1 += 900;
                        else romanNumber2 += 900;
                        i += 1;
                    }
                }
                else if (numberepresent[i] == 'D')
                {
                    if (flag == 1) romanNumber1 += 500;
                    else romanNumber2 += 500;
                }
                else if (numberepresent[i] == 'M')
                {
                    if (flag == 1) romanNumber1 += 1000;
                    else romanNumber2 += 1000;
                }
                else
                {
                    if (numberepresent[i] == '+')
                    {
                        oper = 1;
                        flag = 2;
                    }
                    else if (numberepresent[i] == '-')
                    {
                        oper = 2;
                        flag = 2;
                    }
                    else if (numberepresent[i] == '*')
                    {
                        oper = 3;
                        flag = 2;
                    }
                    else if (numberepresent[i] == '/')
                    {
                        oper = 4;
                        flag = 2;
                    }
                }
            }
            if((romanNumber1<0 || romanNumber1>3999) || (romanNumber2<0 || romanNumber2 > 3999))
            {
                oper = -1;
            }
        }

        public void chooseOp()
        {
            if (oper == -1) ;
            else if (oper == 1) Add();
            else if (oper == 2) Sub();
            else if (oper == 3) Mul();
            else if (oper == 4) Div();
        }

        public string ReturnResult()
        {
            if (oper > 0) text = TooString();
            else
            {
                RomanNumberException obj = new RomanNumberException();
                text = obj.MesError();
            }
            return text;
        }
    }
}
