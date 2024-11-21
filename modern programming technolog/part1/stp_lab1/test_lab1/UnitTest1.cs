using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using stp_lab1;

namespace test_lab1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestSumMas1()
        {
            float[] mas_a = { 1.0f, 2.0f }, mas_b = { 1.0f };
            lab_functions obj_fun = new lab_functions();
            float[] result, wait_res = { };

            result = obj_fun.summMass(mas_a, mas_b);

            CollectionAssert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestSumMas2()
        {
            float[] mas_a = { 1.0f, 2.0f, 3.0f }, mas_b = { 1.0f, 2.0f, 3.0f };
            lab_functions obj_fun = new lab_functions();
            float[] result, wait_res = { 2.0f, 4.0f, 6.0f };

            result = obj_fun.summMass(mas_a, mas_b);

            CollectionAssert.AreEqual(wait_res, result);
        }

        [TestMethod]
        public void TestMoveMas()
        {
            float[] mas_a = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
            lab_functions obj_fun = new lab_functions();
            float[] wait_res = { 3.0f, 4.0f, 5.0f, 6.0f, 1.0f, 2.0f };
            
            obj_fun.moveMasElement(ref mas_a, 2);

            CollectionAssert.AreEqual(wait_res, mas_a);
        }

        [TestMethod]
        public void TestFind1()
        {
            int[] seq = { }, mas_a = { 1, 2, 3 };
            lab_functions obj_fun = new lab_functions();
            int wait_res = -1, res = 0;

            res = obj_fun.findIndex(seq, mas_a);

            Assert.AreEqual(wait_res, res);
        }

        [TestMethod]
        public void TestFind2()
        {
            int[] seq = { 2, 3, 4, 5 }, mas_a = { 1, 2, 3 };
            lab_functions obj_fun = new lab_functions();
            int wait_res = -2, res = 0;

            res = obj_fun.findIndex(seq, mas_a);

            Assert.AreEqual(wait_res, res);
        }

        [TestMethod]
        public void TestFind3()
        {
            int[] seq = { 2, 3, 4 }, mas_a = { 1, 2, 3, 4, 5};
            lab_functions obj_fun = new lab_functions();
            int wait_res = 1, res = 0;

            res = obj_fun.findIndex(seq, mas_a);

            Assert.AreEqual(wait_res, res);
        }

        [TestMethod]
        public void TestFind4()
        {
            int[] seq = { 2, 4, 6 }, mas_a = { 1, 2, 3, 4, 5, 6 };
            lab_functions obj_fun = new lab_functions();
            int wait_res = -3, res = 0;

            res = obj_fun.findIndex(seq, mas_a);

            Assert.AreEqual(wait_res, res);
        }
    }
}
