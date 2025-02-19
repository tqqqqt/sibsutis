#include "pch.h"
#include "CppUnitTest.h"

#include "../stp_polynom/TPoly.h"
#include "../stp_polynom/TMember.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TPolyTest
{
	TEST_CLASS(TPolyTest)
	{
	public:
		
		TEST_METHOD(TestConstructor1)
		{
			//arrange
			//act
			TPoly poly(0,0);
			//assert
			try {
				int res = poly[0].coeff();
				Assert::Fail();
			}
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestConstructor2) {
			//arrange
			int coef=2, degre=3;
			//act
			TPoly poly(2,3);
			//assert
			Assert::AreEqual(coef, poly[0].coeff());
			Assert::AreEqual(degre, poly[0].degree());
		}

		TEST_METHOD(TestConstructorMember) {
			//arrange
			TMember member(2,3);
			int coef=2, degre=3;
			//act
			TPoly poly(member);
			//assert
			Assert::AreEqual(coef, poly[0].coeff());
			Assert::AreEqual(degre, poly[0].degree());
		}

		TEST_METHOD(TestDegre) {
			//arrange
			TPoly poly(2,2);
			poly=poly+TMember(3,4);
			int wait_result=4, res=0;
			//act
			res=poly.degree();
			//assert
			Assert::AreEqual(wait_result,res);
		}

		TEST_METHOD(TestCoef) {
			//arrange
			TPoly poly(2,3);
			poly=poly+TMember(3,2);
			int wait_res=3, res=0;
			//act
			res=poly.coeff(2);
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestClear) {
			//arrange
			TPoly poly(2,2);
			//act
			poly.clear();
			//assert
			try {
				poly[0].coeff();
				Assert::Fail();
			}
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestPop) {
			//arrange
			TPoly poly(2,2);
			//act
			poly.popBack();
			//assert
			try {
				poly[0].coeff();
				Assert::Fail();
			}
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestSumMember1) {
			//arrange
			TPoly poly;
			std::string res="-2x^3";
			//act
			poly=poly+TMember(-2,3);
			//assert
			Assert::AreEqual(res,poly.toString());
		}

		TEST_METHOD(TestSumMember2) {
			//arrange
			TPoly poly;
			std::string res = "2x^3";
			//act
			poly = poly + TMember(2, 3);
			//assert
			Assert::AreEqual(res, poly.toString());
		}

		TEST_METHOD(TestSumPoly) {
			//arrange
			TPoly poly1(2,4), poly2(2, 3);
			std::string res="2x^4+2x^3";
			//act
			poly1=poly1+poly2;
			//assert
			Assert::AreEqual(res,poly1.toString());
		}

		TEST_METHOD(TestMullMember) {
			//arrange
			TPoly poly(2,2);
			std::string res = "2x^2*2x^3";
			//act
			poly = poly * TMember(2, 3);
			//assert
			Assert::AreEqual(res, poly.toString());
		}

		TEST_METHOD(TestMullPoly) {
			//arrange
			TPoly poly1(2, 4), poly2(2, 3);
			std::string res = "4x^7";
			//act
			poly1 = poly1 * poly2;
			//assert
			Assert::AreEqual(res, poly1.toString());
		}

		TEST_METHOD(TestMinusMember1) {
			//arrange
			TPoly poly;
			std::string res = "-2x^3";
			//act
			poly = poly - TMember(2, 3);
			//assert
			Assert::AreEqual(res, poly.toString());
		}

		TEST_METHOD(TestMinusMember2) {
			//arrange
			TPoly poly;
			std::string res = "2x^3";
			//act
			poly = poly - TMember(-2, 3);
			//assert
			Assert::AreEqual(res, poly.toString());
		}

		TEST_METHOD(TestMinusPoly) {
			//arrange
			TPoly poly1(2, 4), poly2(2, 3);
			poly2=poly2+TMember(-2,2);
			std::string res = "2x^4-2x^3+2x^2";
			//act
			poly1 = poly1 - poly2;
			//assert
			Assert::AreEqual(res, poly1.toString());
		}

		TEST_METHOD(TestEqual1) {
			//arrange
			TPoly poly1(2, 4), poly2(2, 3);
			poly2 = poly2 + TMember(-2, 2);
			bool wait_res=false, res=false;
			//act
			res = poly1 == poly2;
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestEqual2) {
			//arrange
			TPoly poly1(2, 4), poly2(2, 4);
			bool wait_res = true, res = false;
			//act
			res = poly1 == poly2;
			//assert
			Assert::AreEqual(wait_res, res);
		}

		TEST_METHOD(TestDif) {
			//arrange
			TPoly poly(1,3);
			std::string res="3x^2";
			//act
			poly=poly.dif();
			//assert
			Assert::AreEqual(res,poly.toString());
		}

		TEST_METHOD(TestCalculate) {
			//arrange
			TPoly my_polinom1, my_polinom2;
			my_polinom1 = my_polinom1 + TMember(2, 2);
			my_polinom1 = my_polinom1 * TMember(3, 4);
			my_polinom2 = my_polinom2 + TMember(2, 5);
			my_polinom2 = my_polinom2 + TMember(2, 6);
			my_polinom1 = my_polinom1 * my_polinom2;
			int wait_res=73728, res=0;
			//act
			res=my_polinom1.calculate(2);
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestIndex1) {
			//arrange
			TPoly poly(1,1);
			//act
			try {
				poly[100].coeff();
				Assert::Fail();
			}
			catch (...) {
				Assert::AreEqual(0,0);
			}
		}

		TEST_METHOD(TestIndex2) {
			//arrange
			TPoly poly(2,2);
			std::string wait_res="2x^2", res="";
			//act
			res=poly[0].toString();
			//assert
			Assert::AreEqual(wait_res,res);
		}

		TEST_METHOD(TestToString) {
			//arrange
			TPoly poly(2,3);
			poly=poly-TMember(3,4);
			poly=poly*TMember(5,6);
			std::string wait_res="2x^3-3x^4*5x^6", res="";
			//act
			res=poly.toString();
			//assert
			Assert::AreEqual(wait_res,res);
		}
	};
}
