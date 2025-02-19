using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stp_lab12
{
    class Program
    {
        static void findMinElement(int[] arr,ref int value,ref int index)
        {
            if (arr.Length == 0) return;
            value = arr[0];
            index = 0;
            for(int i = 1; i < arr.Length; i++)
            {
                if (arr[i] >= value) continue;
                value = arr[i];
                index = i;
            }
        }

        static void bubleSort(ref int[] arr)
        {
            int temp = 0;
            for(int i = 0; i < arr.Length; i++)
            {
                for(int j = arr.Length - 1; j > i; j--)
                {
                    if (arr[j] < arr[j - 1])
                    {
                        temp = arr[j];
                        arr[j] = arr[j - 1];
                        arr[j - 1] = temp;
                    }
                }
            }
        }

        static int findElement(int[] arr, int value)
        {
            int l = 0, r = arr.Length - 1;
            while (l < r)
            {
                int mid = (int)Math.Floor((double)((l + r) / 2));
                if (arr[mid] == value) return mid;
                else if (arr[mid] < value) l = mid + 1;
                else r = mid - 1;
            }
            return -1;
        }

        static void findMinInToSize(int[][] arr, ref int value, ref int rows, ref int cols)
        {
            if (arr.GetLength(0) == 0) return;
            for(int i = 0; i < arr.GetLength(0); i++)
            {
                for(int j = 0; j < arr[i].Length; j++)
                {
                    if (value <= arr[i][j]) continue;
                    value = arr[i][j];
                    rows = i;
                    cols = j;
                }
            }
        }

        static void reverseMas(ref int[] arr)
        {
            int l = 0, r = arr.Length - 1, temp=0;
            while (l < r)
            {
                temp = arr[l];
                arr[l] = arr[r];
                arr[r] = temp;
                l++;
                r--;
            }
        }

        static void moveMas(ref int[]arr, int value)
        {
            int[] temp = new int[arr.Length];
            for(int i = 0; i < temp.Length; i++)
            {
                temp[i] = arr[(i + value) % arr.Length];
            }
            arr = temp;
        }

        static void findAndChangeValue(ref int[] arr, int key, int value)
        {
            for(int i = 0; i < arr.Length; i++)
            {
                if (arr[i] == key) arr[i] = value;
            }
        }

        static void Main(string[] args)
        {
            int[] arr = { 2, 2, 6, 6, 8, 8, 9, 9, 4, 4, 5, 5, 0, 1, 7 };
            int value=0, index = 0;

            findMinElement(arr,ref value,ref index);
            Console.WriteLine($"{value} {index}");

            bubleSort(ref arr);
            for (int i = 0; i < arr.Length; i++) Console.Write($"{arr[i]} ");
            Console.Write("\n");

            int res = findElement(arr, 4);
            if (res == -1) Console.WriteLine("No find\n");
            else Console.WriteLine($"Find in {res}");

            int[][] ttemp = new int[3][];
            ttemp[0]=new int[]{ 9, 8, 7 };
            ttemp[1] = new int[] { 6, 5, 4 };
            ttemp[2]=new int[]{ 3, 2, 1 };
            int second_index = 0;
            value = 99;

            findMinInToSize(ttemp, ref value, ref index, ref second_index);
            Console.WriteLine($"{value} {index} {second_index}");

            reverseMas(ref arr);
            for (int i = 0; i < arr.Length; i++) Console.Write($"{arr[i]} ");
            Console.Write("\n");

            moveMas(ref arr, 5);
            for (int i = 0; i < arr.Length; i++) Console.Write($"{arr[i]} ");
            Console.Write("\n");

            findAndChangeValue(ref arr, 4, 3);
            for (int i = 0; i < arr.Length; i++) Console.Write($"{arr[i]} ");
            Console.Write("\n");
        }
    }
}
