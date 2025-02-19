#include "pch.h"
#include "CppUnitTest.h"
#include "../stp_lab5/TPNumber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TPNumberTest
{
	TEST_CLASS(TPNumberTest)
	{
	public:
		
		TEST_METHOD(TestFirstConstructor1)
		{
			//act
			try {
				TPNumber num=TPNumber(0,1,0);
				Assert::Fail();
			}
			//assert
			catch(...){
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestFirstConstructor2)
		{
			//act
			try {
				TPNumber num = TPNumber(0, 2, -1);
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestFirstConstructor3)
		{
			//act
			try {
				TPNumber num = TPNumber(0, 2, 2);
				Assert::AreEqual(0.0,num.value());
				Assert::AreEqual(2,num.system());
				Assert::AreEqual(2,num.accuracy());
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor1)
		{
			//act
			try {
				TPNumber num = TPNumber("", "0", "0");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor2)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "", "0");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor3)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "0", "");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor4)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "a", "0");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor5)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "0", "b");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor6)
		{
			//act
			try {
				TPNumber num = TPNumber("b", "0", "0");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor7)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "1", "0");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor8)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "2", "-1");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSecondConstructor9)
		{
			//act
			try {
				TPNumber num = TPNumber("0", "2", "2");
				Assert::AreEqual(0.0,num.value());
				Assert::AreEqual(2,num.system());
				Assert::AreEqual(2,num.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestPlus1)
		{
			//arrange
			TPNumber num = TPNumber(0, 2, 2), num_2 = TPNumber(0, 3, 2);
			//act
			try {
				TPNumber res=num+num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestPlus2)
		{
			//arrange
			TPNumber num = TPNumber(2, 2, 2), num_2 = TPNumber(0, 2, 3);
			//act
			try {
				TPNumber res = num + num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestPlus3)
		{
			//arrange
			TPNumber num = TPNumber(1, 2, 2), num_2 = TPNumber(2, 2, 2);
			//act
			try {
				TPNumber res = num + num_2;
				Assert::AreEqual(3.0,res.value());
				Assert::AreEqual(2,res.system());
				Assert::AreEqual(2,res.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestMul1)
		{
			//arrange
			TPNumber num = TPNumber(0, 2, 2), num_2 = TPNumber(0, 3, 2);
			//act
			try {
				TPNumber res = num * num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestMul2)
		{
			//arrange
			TPNumber num = TPNumber(2, 2, 2), num_2 = TPNumber(0, 2, 3);
			//act
			try {
				TPNumber res = num * num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestMul3)
		{
			//arrange
			TPNumber num = TPNumber(2, 2, 2), num_2 = TPNumber(3, 2, 2);
			//act
			try {
				TPNumber res = num * num_2;
				Assert::AreEqual(6.0, res.value());
				Assert::AreEqual(2, res.system());
				Assert::AreEqual(2, res.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestMinus1)
		{
			//arrange
			TPNumber num = TPNumber(0, 2, 2), num_2 = TPNumber(0, 3, 2);
			//act
			try {
				TPNumber res = num - num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestMinus2)
		{
			//arrange
			TPNumber num = TPNumber(2, 2, 2), num_2 = TPNumber(0, 2, 3);
			//act
			try {
				TPNumber res = num - num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestMinus3)
		{
			//arrange
			TPNumber num = TPNumber(6, 2, 2), num_2 = TPNumber(3, 2, 2);
			//act
			try {
				TPNumber res = num - num_2;
				Assert::AreEqual(3.0, res.value());
				Assert::AreEqual(2, res.system());
				Assert::AreEqual(2, res.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestDiv1)
		{
			//arrange
			TPNumber num = TPNumber(0, 2, 2), num_2 = TPNumber(0, 3, 2);
			//act
			try {
				TPNumber res = num / num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestDiv2)
		{
			//arrange
			TPNumber num = TPNumber(2, 2, 2), num_2 = TPNumber(0, 2, 3);
			//act
			try {
				TPNumber res = num / num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestDiv3)
		{
			//arrange
			TPNumber num = TPNumber(3, 2, 2), num_2 = TPNumber(0, 2, 2);
			//act
			try {
				TPNumber res = num / num_2;
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestDiv4)
		{
			//arrange
			TPNumber num = TPNumber(6, 2, 2), num_2 = TPNumber(3, 2, 2);
			//act
			try {
				TPNumber res = num / num_2;
				Assert::AreEqual(2.0, res.value());
				Assert::AreEqual(2, res.system());
				Assert::AreEqual(2, res.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestCopy) {
			//arrange
			TPNumber num=TPNumber(2,2,2);
			//act
			TPNumber result=num.copy();
			//assert
			Assert::AreEqual(num.value(), result.value());
			Assert::AreEqual(num.system(),result.system());
			Assert::AreEqual(num.accuracy(),result.accuracy());
		}

		TEST_METHOD(TestReverse1)
		{
			//arrange
			TPNumber num = TPNumber(0, 2, 2);
			//act
			try {
				TPNumber res = num.reverse();
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestReverse2)
		{
			//arrange
			TPNumber num = TPNumber(2, 2, 2);
			//act
			try {
				TPNumber res = num.reverse();
			//assert
				Assert::AreEqual(0.5, res.value());
				Assert::AreEqual(2, res.system());
				Assert::AreEqual(2, res.accuracy());
			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestSquare) {
			//arrange
			TPNumber num=TPNumber(2,2,2);
			//act
			try {
				TPNumber res=num.square();
			//assert
				Assert::AreEqual(4.0, res.value());
				Assert::AreEqual(2, res.system());
				Assert::AreEqual(2, res.accuracy());
			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestValueDouble) {
			//arrange
			TPNumber num=TPNumber(2,2,2);
			//act
			double result=num.value(), wait_result=2;
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestValueString1) {
			//arrange
			TPNumber num = TPNumber(2, 10, 2);
			//act
			std::string result = num.valueStr(), wait_result = "2.000000";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString2) {
			//arrange
			TPNumber num = TPNumber(0, 2, 0);
			//act
			std::string result = num.valueStr(), wait_result = "0";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString3) {
			//arrange
			TPNumber num = TPNumber(12, 13, 0);
			//act
			std::string result = num.valueStr(), wait_result = "c";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString4) {
			//arrange
			TPNumber num = TPNumber(1234, 13, 0);
			//act
			std::string result = num.valueStr(), wait_result = "73c";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString5) {
			//arrange
			TPNumber num = TPNumber(1804, 13, 0);
			//act
			std::string result = num.valueStr(), wait_result = "a8a";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString6) {
			//arrange
			TPNumber num = TPNumber(1234, 13, 2);
			//act
			std::string result = num.valueStr(), wait_result = "73c";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString7) {
			//arrange
			TPNumber num = TPNumber(1804.24, 13, 0);
			//act
			std::string result = num.valueStr(), wait_result = "a8a";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString8) {
			//arrange
			TPNumber num = TPNumber(1804.26, 13, 3);
			//act
			std::string result = num.valueStr(), wait_result = "a8a.34C";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestValueString9) {
			//arrange
			TPNumber num = TPNumber(1234.26, 13, 3);
			//act
			std::string result = num.valueStr(), wait_result = "73c.34C";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestSystemInt) {
			//arrange
			TPNumber num=TPNumber(4,3,2);
			//act
			int result=num.system(), wait_result=3;
			//assert
			Assert::AreEqual(wait_result,result);
		}

		TEST_METHOD(TestSystemString) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			std::string result = num.systemStr(), wait_result = "3";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestAccuracyInt) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			int result = num.accuracy(), wait_result = 2;
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestAccuracyString) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			std::string result = num.accuracyStr(), wait_result = "2";
			//assert
			Assert::AreEqual(wait_result, result);
		}

		TEST_METHOD(TestSetSystemInt1) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			try {
				num.setSystem(1);
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestSetSystemInt2) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			try {
				num.setSystem(2);
				Assert::AreEqual(2,num.system());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestSetSystemString1) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			try {
				num.setSystem("");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetSystemString2) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			try {
				num.setSystem("b");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetSystemString3) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			try {
				num.setSystem("1");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetSystemString4) {
			//arrange
			TPNumber num = TPNumber(4, 3, 2);
			//act
			try {
				num.setSystem("2");
				Assert::AreEqual(2,num.system());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestSetAccuracyInt1) {
			//arrange
			TPNumber num = TPNumber(4, 3, 3);
			//act
			try {
				num.setAccuracy(-1);
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetAccuracyInt2) {
			//arrange
			TPNumber num = TPNumber(4, 3, 3);
			//act
			try {
				num.setAccuracy(2);
				Assert::AreEqual(2,num.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestSetAccuracyString1) {
			//arrange
			TPNumber num = TPNumber(4, 3, 3);
			//act
			try {
				num.setAccuracy("");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetAccuracyString2) {
			//arrange
			TPNumber num = TPNumber(4, 3, 3);
			//act
			try {
				num.setAccuracy("b");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetAccuracyString3) {
			//arrange
			TPNumber num = TPNumber(4, 3, 3);
			//act
			try {
				num.setAccuracy("-1");
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestSetAccuracyString4) {
			//arrange
			TPNumber num = TPNumber(4, 3, 3);
			//act
			try {
				num.setAccuracy("2");
				Assert::AreEqual(2,num.accuracy());
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
		}
	};
}
