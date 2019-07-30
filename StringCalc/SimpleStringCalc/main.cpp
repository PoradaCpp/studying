#include <iostream>

#include "../StringLib/StringCalc.h"

int main()
{
	StringCalc calc;

	try
	{
		std::cout << "calc.add(\"-1, -2, -3, 5\") = " << calc.add("-1, -2, -3, 5") << '\n';
	}
	catch (std::logic_error& exc)
	{
		std::cout << exc.what() << '\n';
	}

	system("pause");

	return 0;
}