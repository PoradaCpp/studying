#include "MyVector.h"

#include <string>

MyVector::MyVector() {}

MyVector::MyVector(size_t nSize): m_nSize(nSize), m_nCapacity(nSize)
{
	m_pBuffer = new int[nSize];
}

MyVector::MyVector(const MyVector &rVc): m_nSize(rVc.m_nSize), m_nCapacity(rVc.m_nCapacity)
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
	}
	m_pBuffer = new int[m_nCapacity];

	for (int i = 0; i < m_nSize; ++i)
	{
		m_pBuffer[i] = rVc.m_pBuffer[i];
	}
}

MyVector::~MyVector()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
	}
}

int& MyVector::at(size_t nSize)
{
	if (nSize >= m_nSize)
	{
		std::string sError = "MyVector::Out_of_range, size = " + std::to_string(m_nSize) + ", required index = " + std::to_string(nSize);
		throw std::out_of_range(sError);
	}
	return m_pBuffer[nSize];
}

int& MyVector::front()
{
	return m_pBuffer[0];
}

int& MyVector::back()
{
	return m_pBuffer[m_nSize - 1];
}

int& MyVector::operator [] (size_t nSize)
{
	return m_pBuffer[nSize];
}

bool MyVector::empty() const
{
	return m_nSize == 0;
}

size_t MyVector::size() const
{
	return m_nSize;
}

void MyVector::reserve(size_t nSize)
{
	if (m_nCapacity < nSize)
	{
		int *pTemp = new int[nSize];

		for (int i = 0; i < m_nSize; ++i)
		{
			pTemp[i] = m_pBuffer[i];
		}
		delete[] m_pBuffer;
		m_pBuffer = pTemp;
		m_nCapacity = nSize;
	}
}

void MyVector::push_back(int nVal)
{
	if (!m_pBuffer)
	{
		m_pBuffer = new int[4];
		m_nCapacity = 4;
	}
	else if(m_nSize == m_nCapacity)
	{
		int *pTemp = new int[m_nCapacity * 2];

		for (int i = 0; i < m_nSize; ++i)
		{
			pTemp[i] = m_pBuffer[i];
		}
		delete[] m_pBuffer;
		m_pBuffer = pTemp;
		m_nCapacity *= 2;
	}
	m_pBuffer[m_nSize++] = nVal;
}

void MyVector::pop_back()
{
	if (m_nSize)
	{
		--m_nSize;
	}
}