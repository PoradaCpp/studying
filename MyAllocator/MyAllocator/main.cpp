// MyAllocator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyAllocator.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>

int main()
{
	const size_t TESTS_NUMBER = 524288;
	srand(static_cast<size_t>(time(nullptr)));

	MyAllocator myAllocator(TESTS_NUMBER);
	std::vector <char*> CharPtrVc;
	CharPtrVc.reserve(4096);
	size_t nCurCase(0);
	size_t nSize(0);
	uint32_t nNumOfAllocations(0);
	uint32_t nNumOfDeallocations(0);
	int nDeallocPoint(0);
	char* pTemp(nullptr);
	auto Iter = CharPtrVc.begin();

	auto start = std::chrono::system_clock::now();

	for (size_t i = 0; i < TESTS_NUMBER; ++i)
	{
		nCurCase = rand() % 93;
		if (nCurCase <= 60)
		{
			//std::cout << i << " alloc\n";
			nSize = 4 + rand() % 93;

			pTemp = reinterpret_cast<char*>(myAllocator.allocate(nSize));
			if (pTemp)
			{
				for (int8_t i = 0, p = static_cast<int8_t>(nSize) - 1; i < p; ++i)
				{
					pTemp[i] = '!' + i;
				}
				pTemp[nSize - 1] = '\0';

				CharPtrVc.push_back(pTemp);
				pTemp = nullptr;
				++nNumOfAllocations;
			}
			else
			{
				//std::cout << "_________Buffer is full\n\n";
			}
		}

		if (nCurCase > 60)
		{
			//std::cout << "dealloc\n";
			if (CharPtrVc.empty())
			{
				//std::cout << "_________Buffer is cleared\n\n";
			}
			else
			{
				nDeallocPoint = rand() % static_cast<int>(CharPtrVc.size());
				Iter = CharPtrVc.begin() + nDeallocPoint;
				myAllocator.deAlloc(*Iter);
				CharPtrVc.erase(Iter);
				++nNumOfDeallocations;
			}
		}

		/*for (char* pStr :IntPtrVc)
		{
			std::cout << pStr << '\n';
		}*/
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> difference = end - start;
	std::cout << "The execution time:     " << difference.count() << "\n";
	std::cout << "Allocations quantity:   " << nNumOfAllocations << "\n";
	std::cout << "Deallocations quantity: " << nNumOfDeallocations << "\n";

	return 0;
}

