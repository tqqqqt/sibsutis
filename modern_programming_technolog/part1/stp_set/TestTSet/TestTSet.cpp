#include "pch.h"
#include "CppUnitTest.h"

#include "../stp_set/TSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestTSet
{
	TEST_CLASS(TestTSet)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			//arrange
			int wait_res=0;
			//act
			TSet<int> set;
			//assert
			Assert::AreEqual(wait_res,set.count());
		}

		TEST_METHOD(TestConstructorSet) {
			//arrange
			TSet<int> set1;
			set1.add(2);
			int wait_res=1;
			//act
			TSet<int> set2(set1);
			//assert
			Assert::AreEqual(wait_res,set2.count());
		}

		TEST_METHOD(TestClear) {
			//arrange
			TSet<int> set;
			set.add(1);
			set.add(2);
			int wait_res=0;
			//act
			set.clear();
			//assert
			Assert::AreEqual(wait_res,set.count());
		}

		TEST_METHOD(TestAdd1) {
			//arrange
			TSet<int> set;
			set.add(1);
			set.add(2);
			int wait_res=2, res=0;
			//act
			set.add(1);
			res=set.count();
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestAdd2) {
			//arrange
			TSet<int> set;
			set.add(1);
			set.add(3);
			int wait_res = 3, res = 0;
			//act
			set.add(2);
			res = set.count();
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestAdd3) {
			//arrange
			TSet<int> set;
			set.add(1);
			set.add(2);
			int wait_res = 3, res = 0;
			//act
			set.add(4);
			res = set.count();
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestDel) {
			//arrange
			TSet<int> set;
			set.add(1);
			set.add(3);
			set.add(5);
			int wait_res=2, res=0;
			//act
			set.del(3);
			res=set.count();
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestEmpty) {
			//arrange
			TSet<int> set;
			bool wait_res=true, res=false;
			//act
			res=set.isEmpty();
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestIn1) {
			//arrange
			TSet<int> set;
			set.add(2);
			bool wait_res=true, res=false;
			//act
			res=set.isIn(2);
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestIn2) {
			//arrange
			TSet<int> set;
			bool wait_res = false, res = false;
			//act
			res = set.isIn(2);
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestAppend) {
			//arrange
			TSet<int> set1, set2;
			set1.add(1); set1.add(2); set1.add(3);
			set2.add(4); set2.add(5); set2.add(6);
			int wait_res=6, res=0;
			//act
			set1=set1.append(set2);
			res=set1.count();
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestSub) {
			//arrange
			TSet<int> set1, set2;
			set1.add(1); set1.add(2); set1.add(3); set1.add(4);
			set2.add(2); set2.add(3);
			int wait_res = 2, res = 0;
			//act
			set1 = set1.sub(set2);
			res = set1.count();
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestMul) {
			//arrange
			TSet<int> set1, set2;
			set1.add(1); set1.add(2); set1.add(3); set1.add(4);
			set2.add(2); set2.add(3);
			int wait_res = 2, res = 0;
			//act
			set1 = set1.mull(set2);
			res = set1.count();
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestCount) {
			//arrange
			TSet<int> set;
			set.add(1); set.add(2); set.add(3); set.add(4);
			int wait_res = 4, res = 0;
			//act
			res = set.count();
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestElement1) {
			//arrange
			TSet<int> set;
			set.add(1); set.add(2); set.add(3);
			int res=0;
			//act
			try {
				res = set.element(100);
				Assert::Fail();
			}
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestElement2) {
			//arrange
			TSet<int> set;
			set.add(1); set.add(2); set.add(3);
			int wait_res=2, res=0;
			//act
			try {
				res=set.element(1);
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,res);
		}
	};
}
