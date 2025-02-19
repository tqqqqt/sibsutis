using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stp_lab1
{
    public class lab_functions
    {
        public float[] summMass(float[] mas_a, float[] mas_b)
        {
            if (mas_a.Length != mas_b.Length)
            {
                return new float[0];
            }
            float[] result = new float[mas_a.Length];
            for(int i = 0; i < mas_a.Length; i++)
            {
                result[i] = mas_a[i] + mas_b[i];
            }
            return result;
        }

        public void moveMasElement(ref float[] mas, int move)
        {
            float[] result = new float[mas.Length];
            for (int i = mas.Length - 1; i >= 0; i--)
            {
                if (i - (move%mas.Length) >= 0)
                {
                    result[i - (move % mas.Length)] = mas[i];
                }
                else result[mas.Length - ((move % mas.Length)-i)] = mas[i];
            }
            mas = result;
        }

        public int findIndex(int[] seq, int[] vec)
        {
            if (seq.Length == 0)
            {
                return -1;
            }
            if (seq.Length > vec.Length)
            {
                return -2;
            }
            for(int i = 0; i < vec.Length; i++)
            {
                if (seq[0] != vec[i]) continue;
                int flg = 1; //7
                for(int j = 0; j < seq.Length; j++)
                {
                    if ((i + j) >= vec.Length || seq[j] != vec[i + j])
                    {
                        flg = 0;
                        break;
                    }
                }
                if (flg==1) return i;
            }
            return -3;
        }
    }
}
