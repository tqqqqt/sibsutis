using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stp_lab4
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Matrix mas_a = new Matrix(3, 3);
                int[,] temp = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
                Matrix mas_b=new Matrix(3, 3, temp);
                for(int i = 0; i < mas_a.rows(); i++)
                {
                    for(int j = 0; j < mas_a.cols(); j++)
                    {
                        mas_a[i, j] = i * 2 + j;
                    }
                }

                Console.WriteLine($"matrix a = {mas_a.toString()}");
                Console.WriteLine($"matrix b = {mas_b.toString()}");
                Matrix mas_c = mas_a + mas_b;
                Console.WriteLine($"\n sum matrix = {mas_c.toString()}");
                mas_c = mas_a - mas_b;
                Console.WriteLine($"\n neg matrix = {mas_c.toString()}");
                mas_c = mas_a * mas_b;
                Console.WriteLine($"\n mull matrix = {mas_c.toString()}");
                mas_c = mas_b.transp();
                Console.WriteLine($"\n transp b = {mas_c.toString()}");
                Console.WriteLine($"\n matrix a == matrix b -> {mas_a == mas_b}\n matrix a != matrix b -> {mas_a != mas_b}");
                Console.WriteLine($"\n min element in a = {mas_a.minElement()}\n min element in b = {mas_b.minElement()}");
            }
            catch(Exception exp)
            {
                Console.WriteLine(exp.Message);
            }
        }
    }
}
