using lab_lib;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace lab_tests
{
    [TestClass]
    public class UnitTest
    {
        [TestMethod]
        public void TestFindMax1()
        {
            //arrage
            float num_1 = 2f, num_2 = 4f;
            float wait_res = 4f;
            //act
            float result = Class1.findMax(num_1, num_2);
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestFindMax2()
        {
            //arrage
            float num_1 = 6f, num_2 = 3f;
            float wait_res = 6f;
            //act
            float result = Class1.findMax(num_1, num_2);
            //assert
            Assert.AreEqual(wait_res, result);
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestSumIndex1()
        {
            //arrage
            float[,] mas = new float[0, 0] { };
            //act
            float result = Class1.sumOnIndex(mas);
            //assert
        }

        [TestMethod]
        public void TestSumIndex2()
        {
            //arrage
            float[,] mas = new float[3, 3] { { 0f, 1f, 2f }, { 3f, 4f, 5f }, { 6f, 7f, 8f } };
            float res = 0f, wait_res = 12f;
            //act
            try
            {
                res = Class1.sumOnIndex(mas);
            }
            //assert
            catch(Exception exp)
            {
                Assert.Fail();
            }
            Assert.AreEqual(wait_res, res);
        }

        [TestMethod]
        [ExpectedException(typeof(FormatException))]
        public void TestMinNum1()
        {
            //arrage
            float[,] mas = new float[0, 0] { };
            //act
            float res = Class1.minSecondDiag(mas);
            //assert
        }

        [TestMethod]
        public void TestMinNum2()
        {
            //arrage
            float[,] mas = new float[3, 3] { { 0f, 1f, 2f }, { 3f, 4f, 5f }, { 6f, 7f, 8f } };
            float wait_res = 0, result = 0;
            //act
            try
            {
                result = Class1.minSecondDiag(mas);
            }
            //assert
            catch(Exception exp)
            {
                Assert.Fail();
            }
            Assert.AreEqual(wait_res, result);
        }
    }
}
