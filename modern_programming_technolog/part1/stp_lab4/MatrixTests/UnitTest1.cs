using Microsoft.VisualStudio.TestTools.UnitTesting;
using stp_lab4;
using System;

namespace MatrixTests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestConstructor1()
        {
            //act
            Matrix mas_a = new Matrix(0, 0);
        }

        [TestMethod]
        public void TestConstructor2()
        {
            //arrage
            Matrix mas_a = null;
            //act
            try
            {
                mas_a = new Matrix(2, 2);
            }
            //assert
            catch(Exception exp)
            {
                Assert.Fail();
            }
            if (mas_a.rows() != 2 || mas_a.cols() != 2) Assert.Fail();
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestConstructorMas1()
        {
            //arrage
            int[,] temp = new int[1, 1];
            //act
            Matrix mas = new Matrix(0, 0, temp);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestConstructorMas2()
        {
            //arrage
            int[,] temp = new int[0, 0];
            //act
            Matrix mas = new Matrix(2, 2, temp);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void TestConstructorMas3()
        {
            //arrage
            int[,] temp = new int[2, 2];
            //act
            Matrix mas = new Matrix(3, 3, temp);
        }

        [TestMethod]
        public void TestConstructorMas4()
        {
            //arrage
            int[,] temp = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            //act
            Matrix mas = new Matrix(3, 3, temp);
            //assert
            if (mas.rows() != 3) Assert.Fail();
            for(int i = 0; i < mas.rows(); i++)
            {
                for(int j = 0; j < mas.cols(); j++)
                {
                    if (mas[i, j] != temp[i, j]) Assert.Fail();
                }
            }
        }

        [TestMethod]
        public void TestGetRows()
        {
            //arrage
            Matrix mas = new Matrix(3, 2);
            int wait_res = 3, result = 0;
            //act
            result = mas.rows();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestGetCols()
        {
            //arrage
            Matrix mas = new Matrix(2, 3);
            int wait_res = 3, result = 0;
            //act
            result = mas.cols();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        [ExpectedException(typeof(IndexOutOfRangeException))]
        public void TestGetOnIndex1()
        {
            //arrage
            Matrix mas = new Matrix(2, 3);
            int temp = 0;
            //act
            temp = mas[6, 6];
        }

        [TestMethod]
        public void TestGetOnIndex2()
        {
            //arrage
            int[,] temp = { { 1, 2 }, { 3, 4 } };
            Matrix mas = new Matrix(2, 2, temp);
            int wait_res = 2, result = 0;
            //act
            try
            {
                result = mas[0, 1];
            }
            //assert
            catch(Exception exp)
            {
                Assert.Fail();
            }
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        [ExpectedException(typeof(IndexOutOfRangeException))]
        public void TestSetOnIndex1()
        {
            //arrage
            Matrix mas = new Matrix(2, 2);
            int temp = 2;
            //act
            mas[6, 6] = temp;
        }

        [TestMethod]
        public void TestSetOnIndex2()
        {
            //arrage
            Matrix mas = new Matrix(2, 2);
            int wait_res = 4, result = 0, temp = 4;
            //act
            try
            {
                mas[0, 1] = temp;
                result = mas[0, 1];
            }
            //assert
            catch (Exception exp)
            {
                Assert.Fail();
            }
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestSum1()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 3), mas_b = new Matrix(3, 3);
            //act
            mas_a = mas_a + mas_b;
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestSum2()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 3), mas_b = new Matrix(2, 2);
            //act
            mas_a = mas_a + mas_b;
        }

        [TestMethod]
        public void TestSum3()
        {
            //arrage
            int[,] temp_fill = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Matrix mas_a = new Matrix(3, 3,temp_fill), mas_b = new Matrix(3, 3,temp_fill);
            int[,] wait_res={ { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
            Matrix result = new Matrix(3, 3);
            //act
            try
            {
                result = mas_a + mas_b;
            }
            //assert
            catch(Exception exp)
            {
                Assert.Fail();
            }
            for(int i = 0; i < wait_res.GetLength(0); i++)
            {
                for(int j = 0; j < wait_res.GetLength(1); j++)
                {
                    if (result[i, j] != wait_res[i, j]) Assert.Fail();
                }
            }
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestMinus1()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 3), mas_b = new Matrix(3, 3);
            //act
            mas_a = mas_a - mas_b;
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestMinus2()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 3), mas_b = new Matrix(2, 2);
            //act
            mas_a = mas_a - mas_b;
        }

        [TestMethod]
        public void TestMinus3()
        {
            //arrage
            int[,] temp_fill = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Matrix mas_a = new Matrix(3, 3, temp_fill), mas_b = new Matrix(3, 3, temp_fill);
            int[,] wait_res ={ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
            Matrix result = new Matrix(3, 3);
            //act
            try
            {
                result = mas_a - mas_b;
            }
            //assert
            catch (Exception exp)
            {
                Assert.Fail();
            }
            for (int i = 0; i < wait_res.GetLength(0); i++)
            {
                for (int j = 0; j < wait_res.GetLength(1); j++)
                {
                    if (result[i, j] != wait_res[i, j]) Assert.Fail();
                }
            }
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestMull1()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 2), mas_b = new Matrix(3, 3);
            //act
            mas_a = mas_a * mas_b;
        }

        [TestMethod]
        public void TestMull2()
        {
            //arrage
            int[,] temp_fill = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Matrix mas_a = new Matrix(3, 3, temp_fill), mas_b = new Matrix(3, 3, temp_fill);
            int[,] wait_res = { { 30, 36, 42 }, { 66, 81, 96 }, { 102, 126, 150 } };
            Matrix result = new Matrix(3, 3);
            //act
            try
            {
                result = mas_a * mas_b;
            }
            //assert
            catch (Exception exp)
            {
                Assert.Fail();
            }
            for (int i = 0; i < wait_res.GetLength(0); i++)
            {
                for (int j = 0; j < wait_res.GetLength(1); j++)
                {
                    if (result[i, j] != wait_res[i, j]) Assert.Fail();
                }
            }
        }

        [TestMethod]
        public void TestEqual1()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 3), mas_b = new Matrix(3, 3);
            bool wait_res = false, result = false;
            //act
            result = mas_a == mas_b;
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestEqual2()
        {
            //arrage
            Matrix mas_a = new Matrix(2, 2), mas_b = new Matrix(2, 3);
            bool wait_res = false, result = false;
            //act
            result = mas_a == mas_b;
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestEqual3()
        {
            //arrage
            int[,] temp_fill_1 = { { 1, 2 }, { 3, 4 } };
            int[,] temp_fill_2 = { { 1, 1 }, { 3, 4 } };
            Matrix mas_a = new Matrix(2, 2, temp_fill_1), mas_b = new Matrix(2, 2, temp_fill_2);
            bool wait_res = false, result = false;
            //act
            result = mas_a == mas_b;
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestEqual4()
        {
            //arrage
            int[,] temp_fill = { { 1, 2 }, { 3, 4 } };
            Matrix mas_a = new Matrix(2, 2, temp_fill), mas_b = new Matrix(2, 2, temp_fill);
            bool wait_res = true, result = false;
            //act
            result = mas_a == mas_b;
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestNoEqual()
        {
            //arrage
            int[,] temp_fill_1 = { { 1, 2 }, { 3, 4 } };
            int[,] temp_fill_2 = { { 1, 1 }, { 3, 4 } };
            Matrix mas_a = new Matrix(2, 2, temp_fill_1), mas_b = new Matrix(2, 2, temp_fill_2);
            bool wait_res = true, result = false;
            //act
            result = mas_a != mas_b;
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestTransp1()
        {
            //arrage
            Matrix mas = new Matrix(2, 3);
            //act
            mas = mas.transp();
        }

        [TestMethod]
        public void TestTransp2()
        {
            //arrage
            int[,] temp_fill = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Matrix mas = new Matrix(3, 3, temp_fill);
            int[,] wait_res = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 } };
            Matrix result = new Matrix(3, 3);
            //act
            try
            {
                result = mas.transp();
            }
            catch(Exception exp)
            {
                Assert.Fail();
            }
            for(int i = 0; i < wait_res.GetLength(0); i++)
            {
                for(int j = 0; j < wait_res.GetLength(1); j++)
                {
                    if (result[i, j] != wait_res[i, j]) Assert.Fail();
                }
            }
        }

        [TestMethod]
        public void TestMinElement1()
        {
            //arrage
            int[,] temp_fill = { { 9, 8, 7 }, { 6, 5, 4 }, { 3, 2, 1 } };
            Matrix mas = new Matrix(3, 3, temp_fill);
            int wait_res = 1, result = 0;
            //act
            result = mas.minElement();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestMinElement2()
        {
            //arrage
            int[,] temp_fill = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Matrix mas = new Matrix(3, 3, temp_fill);
            int wait_res = 1, result = 0;
            //act
            result = mas.minElement();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestToString1()
        {
            //arrage
            int[,] temp_fill = { { 1 } };
            Matrix mas = new Matrix(1, 1, temp_fill);
            string wait_res = "{ {1} }", result = "";
            //act
            result = mas.toString();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestToString2()
        {
            //arrage
            int[,] temp_fill = { { 1, 2 } };
            Matrix mas = new Matrix(1, 2, temp_fill);
            string wait_res = "{ {1, 2} }", result = "";
            //act
            result = mas.toString();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestToString3()
        {
            //arrage
            int[,] temp_fill = { { 1 }, { 2 } };
            Matrix mas = new Matrix(2, 1, temp_fill);
            string wait_res = "{ {1}, {2} }", result = "";
            //act
            result = mas.toString();
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestToString4()
        {
            //arrage
            int[,] temp_fill = { { 1, 2 }, { 3, 4 } };
            Matrix mas = new Matrix(2, 2, temp_fill);
            string wait_res = "{ {1, 2}, {3, 4} }", result = "";
            //act
            result = mas.toString();
            //assert
            Assert.AreEqual(wait_res, result);
        }
    }
}
