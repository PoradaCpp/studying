#include <iostream>
#include <string>
#include <memory>

#include "MyVector.hpp"

class A
{
public:
	A(int nNum1, int nNum2): m_nNum1(nNum1), m_nNum2(nNum2), m_pNum3(new int(rand() % 100))
	{
		std::cout << "A c-tor!\n";
	}

	A(const A &other) : m_nNum1(other.m_nNum1), m_nNum2(other.m_nNum2), m_pNum3(new int(*other.m_pNum3))
	{
		std::cout << "A copy c-tor!\n";
	}

	~A()
	{
		delete m_pNum3;
		std::cout << "A d-tor!\n";
	}

	int m_nNum1;
	int m_nNum2;
	int *m_pNum3;
};


int main()
{
	MyVector<int> vc;
	
	for (int i = 0; i < 1024; ++i)
	{
		vc.push_back(i);
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
	vc2.pop_back();
	for (size_t i = 0, nVcSize = vc2.size(); i < nVcSize; ++i)
	{
		std::cout << *vc2[i] << ' ';
	}
	std::cout << '\n';

	MyVector<int> vc3 = vc;

	MyVector<A> vc4;

	for (int i = 0; i < 5; ++i)
	{
		vc4.push_back({ i, 11 });
	}
	vc4.pop_back();
	for (size_t i = 0, nVcSize = vc4.size(); i < nVcSize; ++i)
	{
		std::cout << vc4[i].m_nNum1 << ' ';
	}
	std::cout << '\n';

	MyVector<A> vc5 = vc4;

	for (size_t i = 0, nVcSize = vc3.size(); i < 1024; ++i)
	{
		std::cout << vc3[i] << ' ';
	}
	std::cout << '\n';

	try
	{
		vc3.at(2048);
	}
	catch(std::out_of_range &exc)
	{
		std::cerr << exc.what() << '\n';
	}

	system("Pause");

	return 0;
}