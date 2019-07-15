#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H

#include "node.h"

class MyAllocator
{
public:
	explicit MyAllocator(size_t nMemSize = 1024);
	~MyAllocator();

	void* allocate(size_t nObjectSize);
	void deAlloc(void* pPointer);
	
	void debugOutput();

private:
	void *m_pStartBuffer;
	void *m_pEndBuffer;
};

#endif //MY_ALLOCATOR_H