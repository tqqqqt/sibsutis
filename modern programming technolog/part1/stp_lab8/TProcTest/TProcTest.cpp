#include "pch.h"
#include "CppUnitTest.h"
#include "../stp_lab8/TProc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TProcTest
{
	TEST_CLASS(TProcTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			//arrange
			TProc<int> object;
			int wait_result=0, result=-1;
			//act
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestClearProc) {
			//arrange
			TProc<int> object;
			object.writeLeftOper(2);
			object.writeOperation(TOprtn::Add);
			int wait_res=0, result=0, wait_res_oper=1, result_oper=0;
			//act
			object.clearProc();
			result=object.readLeftOper();
			result_oper=TOprtn::None==object.readOperation();
			//assert
			Assert::AreEqual(wait_res,result);
			Assert::AreEqual(wait_res_oper,result_oper);
		}

		TEST_METHOD(TestClearOper) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Add);
			int wait_res=1, result=0;
			//act
			object.clearOper();
			result=TOprtn::None==object.readOperation();
			//assert
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestExecuteOper1) {
			//arrange
			TProc<int> object;
			object.writeLeftOper(4);
			object.writeRightOper(4);
			int wait_res=4, result=0;
			//act
			object.executeOper();
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestExecuteOper2) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Add);
			object.writeLeftOper(1);
			object.writeRightOper(2);
			int wait_res = 3, result = 0;
			//act
			object.executeOper();
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestExecuteOper3) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Sub);
			object.writeLeftOper(4);
			object.writeRightOper(3);
			int wait_res = 1, result = 0;
			//act
			object.executeOper();
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestExecuteOper4) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Dvd);
			object.writeLeftOper(1);
			object.writeRightOper(0);
			//act
			try {
				object.executeOper();
				object.readLeftOper();
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(1,1);
			}
		}

		TEST_METHOD(TestExecuteOper5) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Dvd);
			object.writeLeftOper(4);
			object.writeRightOper(2);
			int wait_res = 2, result = 0;
			//act
			object.executeOper();
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestExecuteOper6) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Mul);
			object.writeLeftOper(2);
			object.writeRightOper(2);
			int wait_res = 4, result = 0;
			//act
			object.executeOper();
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestExecuteFunc1) {
			//arrange
			TProc<int> object;
			object.writeRightOper(0);
			int wait_res=0, result=0;
			//act
			object.executeFunc(TFunc::Rev);
			result=object.readRightOper();
			//assert
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestExecuteFunc2) {
			//arrange
			TProc<double> object;
			object.writeRightOper(6);
			double wait_res = 1/(double)6, result = 0;
			//act
			object.executeFunc(TFunc::Rev);
			result = object.readRightOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestExecuteFunc3) {
			//arrange
			TProc<double> object;
			object.writeRightOper(8);
			double wait_res = 64, result = 0;
			//act
			object.executeFunc(TFunc::Sqr);
			result = object.readRightOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestReadLeft) {
			//arrange
			TProc<int> object;
			object.writeLeftOper(2);
			int wait_res=2, result=0;
			//act
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestWriteLeft) {
			//arrange
			TProc<int> object;
			int wait_res=4, result=0;
			//act
			object.writeLeftOper(4);
			result=object.readLeftOper();
			//assert
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestReadRight) {
			//arrange
			TProc<int> object;
			object.writeRightOper(3);
			int wait_res = 3, result = 0;
			//act
			result = object.readRightOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestWriteRight) {
			//arrange
			TProc<int> object;
			int wait_res = 6, result = 0;
			//act
			object.writeRightOper(6);
			result = object.readRightOper();
			//assert
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestReadOper) {
			//arrange
			TProc<int> object;
			int wait_res=1, result=0;
			//act
			result=TOprtn::None==object.readOperation();
			//assert
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestWireOper) {
			//arrange
			TProc<int> object;
			object.writeOperation(TOprtn::Add);
			int wait_res=1, result=0;
			//act
			result=TOprtn::Add==object.readOperation();
			//assert
			Assert::AreEqual(wait_res,result);
		}
	};
}
