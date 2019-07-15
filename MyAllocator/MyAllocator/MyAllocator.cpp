#include "stdafx.h"
#include "MyAllocator.h"

#include <iostream>
#include <iomanip>

MyAllocator::MyAllocator(size_t nMemSize): m_pStartBuffer(new char[nMemSize]), m_pEndBuffer((char*)m_pStartBuffer + nMemSize)
{
	if (nMemSize < 3 * sizeof(Node))
	{
		nMemSize = 3 * sizeof(Node);
	}
	new(m_pStartBuffer) Node(nullptr, nullptr, true);
	new((Node*)m_pEndBuffer - 1) Node((Node*)m_pStartBuffer, nullptr, false);
}

MyAllocator::~MyAllocator()
{
	delete[](char*) m_pStartBuffer;
}

void* MyAllocator::allocate(size_t nObjectSize)
{
	Node* pTempNode = (Node*)m_pStartBuffer;

	while (pTempNode->getNextNode())
	{
		if (pTempNode->getChunkState() && pTempNode->getChunkSize() >= nObjectSize)
		{
			pTempNode->setChunkState(false);
			if (pTempNode->getChunkSize() >= nObjectSize + sizeof(Node) + 1)
			{
				new((char*)pTempNode + sizeof(Node) + nObjectSize) Node(pTempNode, pTempNode->getNextNode(), true);
			}
			return pTempNode + 1;
		}
		else
		{
			pTempNode = pTempNode->getNextNode();
		}
	}
	return nullptr;
}

void MyAllocator::deAlloc(void* pPointer)
{
	((Node*)((char*)pPointer - sizeof(Node)))->setChunkState(true);
}

void MyAllocator::debugOutput()
{
	Node* pTempNode = (Node*)m_pStartBuffer;

	while (pTempNode)
	{
		std::cout << " //////////////// ";
		for (size_t i = 0, p = pTempNode->getChunkSize(); i < p; ++i)
		{
			std::cout << '|';
		}
		pTempNode = pTempNode->getNextNode();
	}
	std::cout << '\n';

	Node* pTempNode1 = (Node*)m_pStartBuffer;

	while (pTempNode1)
	{
		std::cout << pTempNode1 << " | " << pTempNode1->getPreviousNode() << " | " << pTempNode1->getNextNode() << " | " <<
			std::setw(3) << pTempNode1->getChunkSize() << " | " << pTempNode1->getChunkState() << "\n";

		pTempNode1 = pTempNode1->getNextNode();
	}
	std::cout << "----------------------------------------------\n\n";
}