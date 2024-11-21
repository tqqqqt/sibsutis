using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RomanNumbersCalculator.Models
{
    public class RomanNumber
    {
        private ushort number = 1;
        protected int romanNumber1, romanNumber2, result;
        public RomanNumber()
        {
            romanNumber1 = 0;
            romanNumber2 = 0;
            result = 0;
        }
        public void Add()
        {
            result = romanNumber1 + romanNumber2;
        }

        public void Sub()
        {
            result = romanNumber1 - romanNumber2;
        }

        public void Mul()
        {
            result = romanNumber1 * romanNumber2;
        }

        public void Div()
        {
            result = romanNumber1 / romanNumber2;
        }

        public string TooString()
        {
            string text = "";
            int tmp1 = result, tmp2 = 0, hod = 0;
            if (result > 0 && result < 4000)
            {
                while (tmp1 > 0)
                {
                    tmp1 /= 10;
                    hod += 1;
                }
                tmp1 = result;
                for (int i = hod - 1; i >= 0; i -= 1)
                {
                    if (i != 0) tmp2 = (int)(tmp1 / Math.Pow(10, i));
                    else if (i == 0) tmp2 = tmp1;
                    if (i == 3)
                    {
                        if (tmp2 == 1) text += "M";
                        else if (tmp2 == 2) text += "MM";
                        else if (tmp2 == 3) text += "MMM";
                    }
                    else if (i == 2)
                    {
                        if (tmp2 == 1) text += "C";
                        else if (tmp2 == 2) text += "CC";
                        else if (tmp2 == 3) text += "CCC";
                        else if (tmp2 == 4) text += "CD";
                        else if (tmp2 == 5) text += "D";
                        else if (tmp2 == 6) text += "DC";
                        else if (tmp2 == 7) text += "DCC";
                        else if (tmp2 == 8) text += "DCCC";
                        else if (tmp2 == 9) text += "CM";
                    }
                    else if (i == 1)
                    {
                        if (tmp2 == 1) text += "X";
                        else if (tmp2 == 2) text += "XX";
                        else if (tmp2 == 3) text += "XXX";
                        else if (tmp2 == 4) text += "XL";
                        else if (tmp2 == 5) text += "L";
                        else if (tmp2 == 6) text += "LX";
                        else if (tmp2 == 7) text += "LXX";
                        else if (tmp2 == 8) text += "LXXX";
                        else if (tmp2 == 9) text += "XC";
                    }
                    else if (i == 0)
                    {
                        if (tmp2 == 1) text += "I";
                        else if (tmp2 == 2) text += "II";
                        else if (tmp2 == 3) text += "III";
                        else if (tmp2 == 4) text += "IV";
                        else if (tmp2 == 5) text += "V";
                        else if (tmp2 == 6) text += "VI";
                        else if (tmp2 == 7) text += "VII";
                        else if (tmp2 == 8) text += "VIII";
                        else if (tmp2 == 9) text += "IX";
                    }
                    tmp1 = (int)(tmp1 % Math.Pow(10, i));
                }
                return text;
            }
            else
            {
                RomanNumberException obj = new RomanNumberException();
                text = obj.MesError();
                return text;
            }
        }
    }
}
