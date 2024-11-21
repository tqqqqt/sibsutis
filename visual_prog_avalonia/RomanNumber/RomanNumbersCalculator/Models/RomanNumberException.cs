using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RomanNumbersCalculator.Models
{
    internal class RomanNumberException:Exception
    {
        private string text_of_error="";

        public RomanNumberException()
        {
            text_of_error = "#ERROR";
        }
        public string MesError()
        {
            return text_of_error;
        }
    }
}
