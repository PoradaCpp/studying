#pragma once

#include <cstddef>
#include <stdexcept>

class MyVector
{
public:
	MyVector();
	explicit MyVector(std::size_t nSize);
	MyVector(const MyVector &rVc);
	~MyVector();

	int& at(std::size_t nSize);
	int& front();
	int& back();
	int& operator [] (std::size_t nSize);

	bool empty() const;
	std::size_t size() const;
	void reserve(std::size_t nSize);
	void push_back(int nVal);
	void pop_back();

private:
	std::size_t m_nSize = 0;
	std::size_t m_nCapacity = 0;
	int *m_pBuffer = nullptr;
};

