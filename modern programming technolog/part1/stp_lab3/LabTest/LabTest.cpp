#include "pch.h"
#include "CppUnitTest.h"
#include "../stp_lab3/MathLib.h"
#include "../stp_lab3/MathLib.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LabTest
{
	TEST_CLASS(LabTest)
	{
	public:
		
		TEST_METHOD(TestFindMax1)
		{
			//arrage
			int num_1=6, num_2=4, num_3=3;
			int result=0, wait_result=6;
			//act
			result=MathLib::LabLib3::findMax(num_1,num_2,num_3);
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestFindMax2) {
			//arrage
			int num_1=2, num_2=5, num_3=1;
			int result=0, wait_result=5;
			//act
			result=MathLib::LabLib3::findMax(num_1,num_2,num_3);
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestFindMax3) {
			//arrage
			int num_1=2, num_2=3, num_3=9;
			int result=0, wait_result=9;
			//act
			result=MathLib::LabLib3::findMax(num_1,num_2,num_3);
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestNumOnIndex1) {
			//arrage
			int num=-2;
			int result=0, wait_result=0;
			//act
			result=MathLib::LabLib3::createIndexNum(num);
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestNumOnIndex2) {
			//arrage
			int num = 2;
			int result = 0, wait_result = 0;
			//act
			result = MathLib::LabLib3::createIndexNum(num);
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestNumOnIndex3) {
			//arrage
			int num = -1357;
			int result = 0, wait_result = 73;
			//act
			result = MathLib::LabLib3::createIndexNum(num);
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestNumOnIndex4) {
			//arrage
			int num = -1357;
			int result = 0, wait_result = 73;
			//act
			result = MathLib::LabLib3::createIndexNum(num);
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestFindMinIndexNum1) {
			//arrage
			int num = -4526;
			int result = 0, wait_result = 2;
			//act
			result = MathLib::LabLib3::findMinIndex(num);
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestFindMinIndexNum2) {
			//arrage
			int num = 6583;
			int result = 0, wait_result = 3;
			//act
			result = MathLib::LabLib3::findMinIndex(num);
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestSumDiagonal1) {
			//arrage
			std::vector<std::vector<int>> mas = { {} };
			int result=0;
			//act
			try {
				result=MathLib::LabLib3::summUnderDiag(mas);
				Assert::Fail();
			}
			//assert
			catch (const char* error_mes) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestSumDiagonal2) {
			//arrage
			std::vector<std::vector<int>> mas = { {1,2,3}, {4,5,6}, {7,8,9} };
			int result = 0, wait_result=12;
			//act
			try {
				result = MathLib::LabLib3::summUnderDiag(mas);
			}
			//assert
			catch (const char* error_mes) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestSumDiagonal3) {
			//arrage
			std::vector<std::vector<int>> mas = { {1,1,1},{3,3,3},{5,5,5} };
			int result = 0, wait_result=0;
			//act
			try {
				result = MathLib::LabLib3::summUnderDiag(mas);
			}
			//assert
			catch (const char* error_mes) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_result,result);
		}
	};
}
