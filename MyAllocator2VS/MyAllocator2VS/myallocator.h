#ifndef MY_ALLOCATOR_HPP
#define MY_ALLOCATOR_HPP

#include "memchunk.h"

class MyAllocator
{
public:
    MyAllocator(size_t nBufferSize, size_t nNumOfChunk);
	~MyAllocator();

	void* allocate(size_t nObjectSize);
	void deAlloc(void* pPointer);

private:
    const size_t MEM_CHUNK_SIZE;
    const size_t MEM_CHUNK_NUM;
    const size_t MAX_EXP_OF_TWO;

    uint8_t *m_pStartBuffer;
    uint8_t *m_pEndBuffer;
    uint8_t *m_pChunks;
};

#endif //MY_ALLOCATOR_HPP
