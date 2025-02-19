#include "pch.h"
#include "CppUnitTest.h"

#include "../stp_lab6/TEditor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TEditorTest
{
	TEST_CLASS(TEditorTest)
	{
	public:
		
		TEST_METHOD(TestConstructor)
		{
			//arrange
			std::string wait_res_value="";
			//act
			TEditor editor=TEditor();
			//assert
			Assert::AreEqual(wait_res_value,editor.value());
		}

		TEST_METHOD(TestChangeMinus1) {
			//arrange
			TEditor editor=TEditor();
			std::string wait_res="-", result="";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestChangeMinus2) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			std::string wait_res="-8", result = "";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestChangeMinus3) {
			//arrange
			TEditor editor = TEditor();
			editor.changeMinus();
			editor.addNum(8);
			std::string wait_res = "8", result = "";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestChangeMinus4) {
			//arrange
			TEditor editor = TEditor();
			editor.value("8+i*4");
			std::string wait_res = "8-i*4", result = "";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestChangeMinus5) {
			//arrange
			TEditor editor = TEditor();
			editor.value("8-i*4");
			std::string wait_res = "8+i*4", result = "";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestChangeMinus6) {
			//arrange
			TEditor editor = TEditor();
			editor.value("i*4");
			std::string wait_res = "-i*4", result = "";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestChangeMinus7) {
			//arrange
			TEditor editor = TEditor();
			editor.value("-i*4");
			std::string wait_res = "i*4", result = "";
			//act
			try {
				result=editor.changeMinus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestAddPlus1) {
			//arrange
			TEditor editor = TEditor();
			editor.value("8+i*4");
			//act
			try {
				editor.addPlus();
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestAddPlus2) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			editor.addFloatPoint();
			//act
			try {
				editor.addPlus();
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestAddPlus3) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			std::string wait_res = "8+i*", result = "";
			//act
			try {
				result=editor.addPlus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestAddPlus4) {
			//arrange
			TEditor editor = TEditor();
			std::string wait_res = "i*", result = "";
			//act
			try {
				result=editor.addPlus();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestAddNum1) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.addNum(16);
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestAddNum2) {
			//arrange
			TEditor editor = TEditor();
			std::string wait_res = "4", result = "";
			//act
			try {
				result=editor.addNum(4);
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestAddNull) {
			//arrange
			TEditor editor = TEditor();
			std::string wait_res = "0", result = "";
			//act
			try {
				result=editor.addNull();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestAddFloatPoint1) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			editor.addFloatPoint();
			//act
			try {
				editor.addFloatPoint();
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestAddFloatPoint2) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			std::string wait_res = "8.", result = "";
			//act
			try {
				result=editor.addFloatPoint();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestDelSymbol1) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.delSymbol();
				Assert::Fail();
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestDelSymbol2) {
			//arrange
			TEditor editor = TEditor();
			editor.value("8+i*");
			std::string wait_res = "8", result = "";
			//act
			try {
				result=editor.delSymbol();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestDelSymbol3) {
			//arrange
			TEditor editor = TEditor();
			editor.addPlus();
			std::string wait_res = "", result = "";
			//act
			try {
				result=editor.delSymbol();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestDelSymbol4) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			editor.addFloatPoint();
			std::string wait_res = "8", result = "";
			//act
			try {
				result=editor.delSymbol();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestDelSymbol5) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			editor.addNum(3);
			editor.addNum(4);
			std::string wait_res = "83", result = "";
			//act
			try {
				result=editor.delSymbol();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestClear) {
			//arrange
			TEditor editor = TEditor();
			std::string wait_res = "0+i*0", result = "";
			//act
			try {
				result=editor.clear();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestValue) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			std::string wait_res = "8", result="";
			//act
			try {
				result=editor.value();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestValueStr1) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestValueStr2) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("i**");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestValueStr3) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("i*a");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestValueStr4) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("8+2");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestValueStr5) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("8.2.2");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestValueStr6) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("-8-4");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestValueStr7) {
			//arrange
			TEditor editor = TEditor();
			//act
			try {
				editor.value("8*");
			}
			//assert
			catch (...) {
				Assert::AreEqual(0, 0);
			}
		}

		TEST_METHOD(TestValueStr8) {
			//arrange
			TEditor editor = TEditor();
			std::string wait_res = "8+i*4", result = "";
			//act
			try {
				result=editor.value("8+i*4");
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestIsNull1) {
			//arrange
			TEditor editor = TEditor();
			editor.addNum(8);
			bool wait_res=false, result=false;
			//act
			try {
				result=editor.numIsNull();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res,result);
		}

		TEST_METHOD(TestIsNull2) {
			//arrange
			TEditor editor = TEditor();
			editor.clear();
			bool wait_res = true, result = false;
			//act
			try {
				result = editor.numIsNull();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}

		TEST_METHOD(TestIsNull3) {
			//arrange
			TEditor editor = TEditor();
			editor.addPlus();
			editor.addNum(0);
			bool wait_res = true, result = false;
			//act
			try {
				result = editor.numIsNull();
			}
			//assert
			catch (...) {
				Assert::Fail();
			}
			Assert::AreEqual(wait_res, result);
		}
	};
}
