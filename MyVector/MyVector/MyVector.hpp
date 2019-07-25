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
	MyVector(std::size_t nSize, const T& value);
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
	static const size_t DEFAULT_SIZE = 4;

	std::size_t m_nSize = 0;
	std::size_t m_nCapacity = 0;
	T *m_pBuffer = nullptr;
};

template <typename T>
MyVector<T>::MyVector() {}

template <typename T>
MyVector<T>::MyVector(size_t nSize, const T& value) : m_nSize(nSize), m_nCapacity(nSize)
{
	m_pBuffer = reinterpret_cast<T*>(operator new(nSize * sizeof(T)));

	for (size_t i = 0; i < nSize; ++i)
	{
		new(m_pBuffer[i]) T(value);
	}
}

template <typename T>
MyVector<T>::MyVector(const MyVector &rVc) : m_nSize(rVc.m_nSize), m_nCapacity(rVc.m_nCapacity)
{
	m_pBuffer = reinterpret_cast<T*>(operator new(m_nSize * sizeof(T)));

	if (std::is_pod<T>::value)
	{
		memcpy(m_pBuffer, rVc.m_pBuffer, sizeof(T)*m_nSize);
	}
	else
	{
		for (int i = 0; i < m_nSize; ++i)
		{
			new(&m_pBuffer[i]) T(rVc.m_pBuffer[i]);
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
		for (int i = 0; i < m_nSize; ++i)
		{
			m_pBuffer[i].~T();
		}
		operator delete(m_pBuffer);
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
		T* pTemp = reinterpret_cast<T*>(operator new(nSize * sizeof(T)));
		memcpy(pTemp, m_pBuffer, sizeof(T) * m_nSize);

		if (m_pBuffer)
		{
			for (int i = 0; i < m_nSize; ++i)
			{
				m_pBuffer[i].~T();
			}
			operator delete(m_pBuffer);
		}
		m_pBuffer = pTemp;
		m_nCapacity = nSize;
	}
}

template <typename T>
template <typename Type,
		  typename std::enable_if<!std::is_pod<Type>::value && std::is_nothrow_move_constructible<Type>::value>::type* = nullptr>
void MyVector<T>::reserve(std::size_t nSize)
{
	if (m_nCapacity < nSize)
	{
		T* pTemp = reinterpret_cast<T*>(operator new(nSize * sizeof(T)));

		for (int i = 0; i < m_nSize; ++i)
		{
			new(&pTemp[i]) T(std::move(m_pBuffer[i]));
		}
		if (m_pBuffer)
		{
			for (int i = 0; i < m_nSize; ++i)
			{
				m_pBuffer[i].~T();
			}
			operator delete(m_pBuffer);
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
		T* pTemp = reinterpret_cast<T*>(operator new(nSize * sizeof(T)));

		for (int i = 0; i < m_nSize; ++i)
		{
			new(&pTemp[i]) T(m_pBuffer[i]);
		}
		if (m_pBuffer)
		{
			for (int i = 0; i < m_nSize; ++i)
			{
				m_pBuffer[i].~T();
			}
			operator delete(m_pBuffer);
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
		m_pBuffer = reinterpret_cast<T*>(operator new(DEFAULT_SIZE * sizeof(T)));
		m_nCapacity = DEFAULT_SIZE;
	}
	else if (m_nSize == m_nCapacity)
	{
		reserve(m_nCapacity * 2);
	}
	new(&m_pBuffer[m_nSize++]) T(val);
}

template <typename T>
void MyVector<T>::push_back(T &&val)
{
	if (!m_pBuffer)
	{
		m_pBuffer = reinterpret_cast<T*>(operator new(DEFAULT_SIZE * sizeof(T)));
		m_nCapacity = DEFAULT_SIZE;
	}
	else if (m_nSize == m_nCapacity)
	{
		reserve(m_nCapacity * 2);
	}
	new(&m_pBuffer[m_nSize++]) T(std::forward<T>(val));
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (m_nSize)
	{
		m_pBuffer[--m_nSize].~T();
	}
}

#endif // !MY_VECTOR_HPP