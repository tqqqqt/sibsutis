using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using lab_lib;

namespace stp_lab2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            float temp = Class1.findMax(2.009f, 2.008f);
            Console.WriteLine($"Max value () = {temp}");

            float[,] mas_a = new float[3, 3] { { 0f, 1f, 2f}, { 3f, 4f, 5f }, { 6f, 7f, 8f } };

            float sum_index = Class1.sumOnIndex(mas_a);
            Console.WriteLine($" Sum on index = {sum_index}");

            float min_value = Class1.minSecondDiag(mas_a);
            Console.WriteLine($" Min value diag = {min_value}");

            Console.Read();
        }
    }
}
