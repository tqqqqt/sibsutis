using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace stp_lab4
{
    public class Matrix
    {
        private int count_rows;
        private int count_cols;
        private int[,] arr;

        public Matrix(int new_rows, int new_cols)
        {
            if (new_rows == 0 || new_cols == 0) throw new FormatException();
            count_rows = new_rows;
            count_cols = new_cols;
            arr = new int[count_rows, count_cols];
        }

        public Matrix(int new_rows, int new_cols, int[,] data)
        {
            if (new_rows == 0 || new_cols == 0) throw new FormatException();
            if (data.GetLength(0) == 0 || data.GetLength(1) == 0) throw new ArgumentException();
            if (new_rows != data.GetLength(0) || new_cols != data.GetLength(1)) throw new ArgumentException();
            count_rows = new_rows;
            count_cols = new_cols;
            arr = new int[count_rows, count_cols];
            arr = data;
        }

        public int rows()
        {
            return count_rows;
        }

        public int cols()
        {
            return count_cols;
        }

        public int this[int i, int j]{
            get
            {
                if (i < 0 || i >= rows() || j < 0 || j >= cols()) throw new IndexOutOfRangeException();
                return arr[i, j];
            }
            set
            {
                if (i < 0 || i >= rows() || j < 0 || j >= cols()) throw new IndexOutOfRangeException();
                arr[i,j] = value;
            }
        }

        public static Matrix operator+(Matrix first_matrix, Matrix second_matrix)
        {
            if (first_matrix.rows() != second_matrix.rows()) throw new FormatException();
            if (first_matrix.cols() != second_matrix.cols()) throw new FormatException();
            Matrix result = new Matrix(first_matrix.rows(), first_matrix.cols());
            for(int i = 0; i < first_matrix.rows(); i++)
            {
                for(int j = 0; j < first_matrix.cols(); j++)
                {
                    result[i, j] = first_matrix[i, j] + second_matrix[i, j];
                }
            }
            return result;
        }

        public static Matrix operator -(Matrix first_matrix, Matrix second_matrix)
        {
            if (first_matrix.rows() != second_matrix.rows()) throw new FormatException();
            if (first_matrix.cols() != second_matrix.cols()) throw new FormatException();
            Matrix result = new Matrix(first_matrix.rows(), first_matrix.cols());
            for (int i = 0; i < first_matrix.rows(); i++)
            {
                for (int j = 0; j < first_matrix.cols(); j++)
                {
                    result[i, j] = first_matrix[i, j] - second_matrix[i, j];
                }
            }
            return result;
        }

        public static Matrix operator *(Matrix first_matrix, Matrix second_matrix)
        {
            if (first_matrix.cols() != second_matrix.rows()) throw new FormatException(); 
            Matrix result = new Matrix(first_matrix.rows(), first_matrix.cols());
            for (int i = 0; i < first_matrix.rows(); i++)//4 5
            {
                for (int j = 0; j < first_matrix.cols(); j++)//6 7
                {
                    int temp = 0;
                    for(int k = 0; k < first_matrix.cols(); k++)//9 10
                    {
                        temp += first_matrix[i, k] * second_matrix[k, j];
                    }
                    result[i, j] = temp;
                }
            }
            return result;
        }

        public static bool operator==(Matrix first_matrix, Matrix second_matrix)
        {
            if (first_matrix.cols() != second_matrix.cols()) return false;
            if (first_matrix.rows() != second_matrix.rows()) return false;
            for (int i = 0; i < first_matrix.rows(); i++)
            {
                for (int j = 0; j < first_matrix.cols(); j++)
                {
                    if (first_matrix[i, j] != second_matrix[i, j]) return false;
                }
            }
            return true;
        }

        public static bool operator !=(Matrix first_matrix, Matrix second_matrix)
        {
            return !(first_matrix == second_matrix);
        }

        public Matrix transp()
        {
            if (cols() != rows()) throw new FormatException();
            Matrix result = new Matrix(this.cols(), this.rows());
            for(int i = 0; i < rows(); i++)
            {
                for(int j = 0; j < cols(); j++)
                {
                    result[i, j] = this[j, i];
                }
            }
            return result;
        }

        public int minElement()
        {
            int result = this[0,0];
            for(int i = 0; i < rows(); i++)
            {
                for(int j = 0; j < cols(); j++)
                {
                    if (result > this[i, j]) result = this[i, j];
                }
            }
            return result;
        }

        public string toString()
        {
            string result = "{ ";
            for(int i = 0; i < rows(); i++)
            {
                if (i == 0) result += "{";
                else result += ", {";
                for(int j = 0; j < cols(); j++)
                {
                    if (j == 0) result += this[i, j].ToString();
                    else result += ", " + this[i, j].ToString();
                }
                result += "}";
            }
            return result + " }";
        }
    }
}
