#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <iostream>

template <typename T>
class MyVector
{
public:
	MyVector();
	explicit MyVector(std::size_t nSize);
	MyVector(const MyVector &rVc);
	MyVector(MyVector &&rVc);
	~MyVector();

	T& at(std::size_t nSize);
	T& front();
	T& back();
	T& operator [] (std::size_t nSize);

	bool empty() const;
	std::size_t size() const;

	template <typename Type = T,
			  typename std::enable_if<std::is_pod<Type>::value>::type* = nullptr>
	void reserve(std::size_t nSize);

	template <typename Type = T,
			  typename std::enable_if<!std::is_pod<Type>::value&& std::is_nothrow_move_constructible<Type>::value>::type* = nullptr>
	void reserve(std::size_t nSize);

	template <typename Type = T,
			  typename std::enable_if<!std::is_pod<Type>::value && !std::is_nothrow_move_constructible<Type>::value>::type* = nullptr>
	void reserve(std::size_t nSize);

	void push_back(const T& val);
	void push_back(T &&val);
	void pop_back();

private:
	std::size_t m_nSize = 0;
	std::size_t m_nCapacity = 0;
	T *m_pBuffer = nullptr;
};

template <typename T>
MyVector<T>::MyVector() {}

template <typename T>
MyVector<T>::MyVector(size_t nSize) : m_nSize(nSize), m_nCapacity(nSize)
{
	m_pBuffer = new T[nSize];
}

template <typename T>
MyVector<T>::MyVector(const MyVector &rVc) : m_nSize(rVc.m_nSize), m_nCapacity(rVc.m_nCapacity)
{
	m_pBuffer = new T[m_nCapacity];

	if (std::is_pod<T>::value)
	{
		memcpy(m_pBuffer, rVc.m_pBuffer, sizeof(T)*m_nSize);
	}
	else
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			m_pBuffer[i] = rVc.m_pBuffer[i];
		}
	}
}

template <typename T>
MyVector<T>::MyVector(MyVector &&rVc) : m_nSize(rVc.m_nSize), m_nCapacity(rVc.m_nCapacity)
{
	m_pBuffer = rVc.m_pBuffer;
	rVc.m_pBuffer = nullptr;
	rVc.m_nSize = 0;
	rVc.m_nCapacity = 0;
}

template <typename T>
MyVector<T>::~MyVector()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
	}
}

template <typename T>
T& MyVector<T>::at(size_t nSize)
{
	if (nSize >= m_nSize)
	{
		std::string sError = "MyVector::Out_of_range, size = " + std::to_string(m_nSize) + ", required index = " + std::to_string(nSize);
		throw std::out_of_range(sError);
	}
	return m_pBuffer[nSize];
}

template <typename T>
T& MyVector<T>::front()
{
	return m_pBuffer[0];
}

template <typename T>
T& MyVector<T>::back()
{
	return m_pBuffer[m_nSize - 1];
}

template <typename T>
T& MyVector<T>::operator [] (size_t nSize)
{
	return m_pBuffer[nSize];
}

template <typename T>
bool MyVector<T>::empty() const
{
	return m_nSize == 0;
}

template <typename T>
size_t MyVector<T>::size() const
{
	return m_nSize;
}

template <typename T>
template <typename Type,
		  typename std::enable_if<std::is_pod<Type>::value>::type* = nullptr>
void MyVector<T>::reserve(std::size_t nSize)
{
	if (m_nCapacity < nSize)
	{
		T* pTemp = new T[nSize];
		memcpy(pTemp, m_pBuffer, sizeof(T) * m_nSize);

		if (m_pBuffer)
		{
			delete[] m_pBuffer;
		}
		m_pBuffer = pTemp;
		m_nCapacity = nSize;
	}
}

template <typename T>
template <typename Type,
		  typename std::enable_if<!std::is_pod<Type>::value&& std::is_nothrow_move_constructible<Type>::value>::type* = nullptr>
void MyVector<T>::reserve(std::size_t nSize)
{
	if (m_nCapacity < nSize)
	{
		T* pTemp = new T[nSize];

		for (int i = 0; i < m_nSize; ++i)
		{
			pTemp[i] = std::move(m_pBuffer[i]);
		}
		if (m_pBuffer)
		{
			delete[] m_pBuffer;
		}
		m_pBuffer = pTemp;
		m_nCapacity = nSize;
	}
}

template <typename T>
template <typename Type,
		  typename std::enable_if<!std::is_pod<Type>::value && !std::is_nothrow_move_constructible<Type>::value>::type* = nullptr>
void MyVector<T>::reserve(std::size_t nSize)
{
	if (m_nCapacity < nSize)
	{
		T* pTemp = new T[nSize];

		for (int i = 0; i < m_nSize; ++i)
		{
			pTemp[i] = m_pBuffer[i];
		}
		if (m_pBuffer)
		{
			delete[] m_pBuffer;
		}
		m_pBuffer = pTemp;
		m_nCapacity = nSize;
	}
}

template <typename T>
void MyVector<T>::push_back(const T& val)
{
	if (!m_pBuffer)
	{
		m_pBuffer = new T[4];
		m_nCapacity = 4;
	}
	else if (m_nSize == m_nCapacity)
	{
		reserve(m_nCapacity * 2);
	}
	m_pBuffer[m_nSize++] = val;
}

template <typename T>
void MyVector<T>::push_back(T &&val)
{
	if (!m_pBuffer)
	{
		m_pBuffer = new T[4];
		m_nCapacity = 4;
	}
	else if (m_nSize == m_nCapacity)
	{
		reserve(m_nCapacity * 2);
	}
	m_pBuffer[m_nSize++] = std::move(val);
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (m_nSize)
	{
		--m_nSize;
	}
}

#endif // !MY_VECTOR_HPP