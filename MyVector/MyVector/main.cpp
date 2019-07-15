#include <iostream>

#include "MyVector.h"

int main()
{
	MyVector vc;
	
	for (int i = 0; i < 1024; ++i)
	{
		vc.push_back(i);
	}

	MyVector vc1 = vc;

	for (size_t i = 0, nVcSize = vc1.size(); i < 1024; ++i)
	{
		std::cout << vc1[i] << ' ';
	}
	std::cout << '\n';

	try
	{
		vc1.at(2048);
	}
	catch(std::out_of_range exc)
	{
		std::cerr << exc.what() << '\n';
	}

	return 0;
}