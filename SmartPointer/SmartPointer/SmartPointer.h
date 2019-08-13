#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include <iostream>
#include <utility>

template <typename T>
class SmartPointer
{
public:
	SmartPointer();
	SmartPointer(T* pData);
	SmartPointer(const SmartPointer& object);
	SmartPointer(SmartPointer&& object);
	~SmartPointer();

	template <typename... Args>
	static SmartPointer<T> make_smart_ptr(Args&&... args);

	T& operator * ();
	T* get();
	uint32_t use_count();

private:
	uint32_t *m_pCounter = nullptr;
	T* m_pData = nullptr;
};

template <typename T>
SmartPointer<T>::SmartPointer()
{
	std::cout << "def constructor\n";
}

template <typename T>
SmartPointer<T>::SmartPointer(T* pData): m_pCounter(new uint32_t), m_pData(pData)
{
	std::cout << "constructor\n";
	*m_pCounter = 1;
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer& other): m_pCounter(other.m_pCounter), m_pData(other.m_pData)
{
	std::cout << "copy constructor\n";
	*m_pCounter += 1;
}

template <typename T>
SmartPointer<T>::SmartPointer(SmartPointer&& other) : m_pCounter(other.m_pCounter), m_pData(other.m_pData)
{
	std::cout << "move constructor\n";
	*m_pCounter += 1;
}

template <typename T>
template <typename... Args>
SmartPointer<T> SmartPointer<T>::make_smart_ptr(Args&&... args)
{
	std::cout << "make_smart_ptr(Args&&... args)\n";
	return SmartPointer<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
SmartPointer<T>::~SmartPointer()
{
	std::cout << "destructor\n";
	if (m_pCounter && !(*m_pCounter))
	{
		delete m_pCounter;
		delete m_pData;
	}
	else
	{
		*m_pCounter -= 1;
	}
}

template <typename T>
T& SmartPointer<T>::operator * ()
{
	return *m_pData;
}

template <typename T>
T* SmartPointer<T>::get()
{
	return m_pData;
}

template <typename T>
uint32_t SmartPointer<T>::use_count()
{
	return *m_pCounter;
}

#endif // SMART_POINTER_H

