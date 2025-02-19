#include "pch.h"
#include "CppUnitTest.h"

#include "../stp_lab7/TMemory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TMemoryTest
{
	TEST_CLASS(TMemoryTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			//act
			try {
				TMemory<int> memory;
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(0,0);
		}

		TEST_METHOD(TestConstructorValue) {
			//arrange
			int value=1;
			int wait_res=1, result=0;
			//act
			try {
				TMemory<int> memory(value);
				result=memory.readNum();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestWrite) {
			//arrange
			int value=2;
			int wait_res=2, result=0;
			//act
			try {
				TMemory<int> memory;
				memory.write(value);
				result=memory.readNum();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestGet) {
			//arrange
			int value=4;
			int wait_res=4, result=0;
			//act
			try {
				TMemory<int> memory(value);
				result=memory.get();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestAdd) {
			//arrange
			int constructor_value=2, add_value=2;
			int wait_res=4, result=0;
			//act
			try {
				TMemory<int> memory(constructor_value);
				memory.add(add_value);
				result=memory.get();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestClear) {
			//arrange
			int value=2;
			int wait_res=0, result=-1;
			//act
			try {
				TMemory<int> memory(value);
				memory.clear();
				result=memory.readNum();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestReadState1) {
			//arrange
			std::string wait_res="Off", result="";
			//act
			try {
				TMemory<int> memory;
				result=memory.readState();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestReadState2) {
			//arrange
			int value = 2;
			std::string wait_res = "On", result = "";
			//act
			try {
				TMemory<int> memory(value);
				result = memory.readState();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestReadNum) {
			//arrange
			int value=6;
			int wait_res=6, result=0;
			//act
			try {
				TMemory<int> memory(value);
				result=memory.readNum();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}
	};
}
