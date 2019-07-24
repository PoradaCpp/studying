#include <iostream>
#include <algorithm>
#include <type_traits>
#include <string>

#include "function.hpp"

int func1()
{
	return 0;
}

struct callable
{
	int operator() ()
	{
		return 1;
	}
};


int main()
{
	function<int(void)> f1;
	if (!f1)
	{
		std::cout << "f1 is empty\n";
	}
	f1 = func1;

	std::cout << f1() << '\n';
	callable c;
	function<int(void)> f2(f1);

	std::cout << f2() << '\n';
	f2 = c;
	std::cout << f2() << '\n';

	system("pause");

    return 0;
}
