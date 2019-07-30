#include "stdafx.h"
#include "CppUnitTest.h"

#include "../StringLib/StringCalc.h"

#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SimpleStringCalc
{		
	TEST_CLASS(StringCalcTest)
	{
	public:
		TEST_METHOD(Check_if_empty_string_as_argument_works_correctly)
		{
			StringCalc calc;
			std::string TaskStr("");
			Assert::AreEqual(calc.add(TaskStr), 0);
		}
		TEST_METHOD(Check_if_three_numbers_divided_by_comma_adds_correctly)
		{
			StringCalc calc;			
			Assert::AreEqual(calc.add("1,2,3"), 6);
		}

		TEST_METHOD(Check_if_different_delimeters_work_correctly)
		{
			StringCalc calc;
			std::string TaskStr("1\n2,3");
			Assert::AreEqual(calc.add(TaskStr), 6);
		}
		TEST_METHOD(Check_if_empty_delimeters_list_works_correctly)
		{
			StringCalc calc;
			std::string TaskStr("<//\n12");
			Assert::AreEqual(calc.add(TaskStr), 12);
		}

		TEST_METHOD(Check_if_filled_delimeters_list_works_correctly)
		{
			StringCalc calc;
			std::string TaskStr("//.\n1.2.3");
			Assert::AreEqual(calc.add(TaskStr), 6);
		}

		TEST_METHOD(Check_if_negative_numbers_in_string_cause_exception_with_list_of_negatives)
		{
			StringCalc calc;
			std::string TaskStr("//...\n-1...-2...-3");
			auto func = [&calc, TaskStr] { return calc.add(TaskStr); };
			Assert::ExpectException<std::logic_error>(func);
		}

		TEST_METHOD(Check_if_numbers_larger_than_1000_are_passed)
		{
			StringCalc calc;
			std::string TaskStr("//...\n1...2...1001");
			auto func = [&calc, TaskStr] { return calc.add(TaskStr); };
			Assert::AreEqual(calc.add(TaskStr), 3);
		}

		TEST_METHOD(Check_if_different_delimetres_work_properly)
		{
			StringCalc calc;
			std::string TaskStr("//[*][#][.]\n1*2#3.4");
			auto func = [&calc, TaskStr] { return calc.add(TaskStr); };
			Assert::ExpectException<std::logic_error>(func);
		}

		TEST_METHOD(Check_if_multiple_different_delimetres_work_properly)
		{
			StringCalc calc;
			std::string TaskStr("//[***][###][...]\n1***2###3...4");
			auto func = [&calc, TaskStr] { return calc.add(TaskStr); };
			Assert::ExpectException<std::logic_error>(func);
		}
	};
}