#include <iostream>

#include "SmartPointer.h"

struct A
{
	A(int nNum, char cSymb, double dNum): m_nNum(nNum), m_cSymb(cSymb), m_dNum(dNum) {}

	int m_nNum;
	char m_cSymb;
	double m_dNum;
};

int main()
{
	SmartPointer<A> sp = SmartPointer<A>::make_smart_ptr(3, 'a', 3.14);
	std::cout << "after creating\n";
	std::cout << (*sp).m_nNum << ' ' << (*sp).m_cSymb << ' ' << (*sp).m_dNum << '\n';

	system("pause");

    return 0;
}

