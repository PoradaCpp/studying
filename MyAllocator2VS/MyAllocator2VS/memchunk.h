#ifndef MEMCHUNK_HPP
#define MEMCHUNK_HPP

#include <stdint.h>

#include "membitset.h"

class MemChunk
{
public:
    void init(uint8_t *pBuffer, size_t nMemChunkSize, size_t nDataSize);

    void* placeData();
    void removeData(void* pData);

    bool full();
    bool empty();

//private:
    size_t m_nMemChunkSize;
    size_t m_nDataSize;
    size_t m_nNumOfData;

    MemBitSet m_BitSet;
    uint8_t* m_pBuffer;
};

#endif // MEMCHUNK_HPP
