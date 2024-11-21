using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stp_lab13
{
    internal class Program
    {

        static void calculateResult(int n_2, int n_2k_star, int n, int v)
        {
            double k = (double)(n_2 / (double)8);
            Console.WriteLine($"k = {k}");
            double i = (double)(Math.Truncate((Math.Log(n_2)) / (double)3) + 1);
            Console.WriteLine($"i = {i}");
            double K = 1;
            for (int j = 1; j < i; j++) K += (double)(n_2 / Math.Pow(8, j));
            Console.WriteLine($"K = {K}");
            double n_2k = (double)(n_2k_star * Math.Log(n_2k_star,2));
            double Nk = (double)(2 * n_2k * Math.Log(n_2k));
            Console.WriteLine($"Nk = {Nk}");
            double N = (double)(K * Nk);
            Console.WriteLine($"N = {N}");
            double V = (double)(K * Nk * Math.Log(2 * n_2k));
            Console.WriteLine($"V = {V}");
            double P = (double)((3 / (double)8) * N);
            Console.WriteLine($"P = {P}");
            double Tk = (double)(P / (double)(n * v));
            Console.WriteLine($"Tk = {Tk}");
            double B0 = (double)(V / 3000.0);
            Console.WriteLine($"B0 = {B0}");
            double tn = (double)((0.5 * Tk) / (double)Math.Log(B0));
            Console.WriteLine($"tn = {tn}");
        }

        static void Main(string[] args)
        {
            Console.WriteLine("n*2=300");
            calculateResult(300, 8, 5, 20);
            Console.Write("\n");

            Console.WriteLine("n*2=400");
            calculateResult(400, 8, 5, 20);
            Console.Write("\n");

            Console.WriteLine("n*2=512");
            calculateResult(512, 8, 5, 20);
            Console.Write("\n");
        }
    }
}
