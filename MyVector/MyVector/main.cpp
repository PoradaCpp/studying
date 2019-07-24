#include <iostream>
#include <string>
#include <memory>

#include "MyVector.hpp"


int main()
{
	MyVector<int*> vc;
	
	for (int i = 0; i < 1024; ++i)
	{
		vc.push_back(new int(i));
	}

	MyVector<std::string> vc1;

	for (int i = 0; i < 1024; ++i)
	{
		vc1.push_back("---" + std::to_string(i));
	}

	MyVector<std::unique_ptr<int>> vc2;

	for (int i = 0; i < 1024; ++i)
	{
		vc2.push_back(std::make_unique<int>(i));
	}

	for (size_t i = 0, nVcSize = vc2.size(); i < 1024; ++i)
	{
		std::cout << *vc2[i] << ' ';
	}
	std::cout << '\n';

	/*MyVector<int> vc1 = vc;

	for (size_t i = 0, nVcSize = vc1.size(); i < 1024; ++i)
	{
		std::cout << vc1[i] << ' ';
	}
	std::cout << '\n';

	try
	{
		vc1.at(2048);
	}
	catch(std::out_of_range &exc)
	{
		std::cerr << exc.what() << '\n';
	}*/

	system("Pause");

	return 0;
}