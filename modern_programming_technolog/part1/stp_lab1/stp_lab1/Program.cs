using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stp_lab1
{
    public class Program
    {
        static void Main(string[] args)
        {
            lab_functions obj_fun = new lab_functions();
            float[] mas_a = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f }, mas_b = { 1.9f, 2.8f, 3.7f, 4.6f, 5.5f, 6.4f, 7.3f, 8.2f, 9.1f };
            float[] res=obj_fun.summMass(mas_a,mas_b);
            Console.Write("Sum mas:\n");
            foreach (int i in res) Console.Write($"{i} ");
            Console.Write("\n \n");

            int move_step = 100;
            obj_fun.moveMasElement(ref res, move_step);
            Console.Write($"Move mas on {move_step}:\n");
            foreach (int i in res) Console.Write($"{i} ");
            Console.Write("\n \n");

            int[] seq = { 4, 5, 6 }, vec = { -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            Console.WriteLine($"findIndex = {obj_fun.findIndex(seq, vec)}\n");
            Console.ReadLine();
        }
    }
}
