using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using lab_lib;

namespace lab_lib
{
    public class Class1
    {
        public static float findMax(float num1, float num2)
        {
            float temp = num1 - num2;
            if (temp <= 0) return num2;
            return num1;
        }

        public static float sumOnIndex(float[,] mas)
        {
            if (mas.GetLength(0) < 1 || mas.GetLength(1) < 1) throw new FormatException();
            int max_index_coll = mas.GetLength(1) - 1;
            float result = 0.0f;
            for(int i = 0; i < mas.GetLength(0) && (max_index_coll-i)>=0; i++)
            {
                result += mas[i, max_index_coll - i];
            }
            return result;
        }

        public static float minSecondDiag(float[,] mas)
        {
            if (mas.GetLength(0) < 1 || mas.GetLength(1) < 1) throw new FormatException();
            float result = float.MaxValue;
            for(int i = 0; i < mas.GetLength(0); i++)
            {
                for (int j = 0; j < mas.GetLength(1) - i; j++)
                {
                    if (result > mas[i, j]) result = mas[i, j];
                }
            }
            return result;
        }
    }
}
