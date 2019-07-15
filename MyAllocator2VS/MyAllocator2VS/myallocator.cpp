#include "myallocator.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>


MyAllocator::MyAllocator(size_t nBufferSize, size_t nNumOfChunk): MEM_CHUNK_SIZE((nBufferSize - nNumOfChunk) / nNumOfChunk),
    DATA_SIZE(nBufferSize), MEM_CHUNK_NUM(nNumOfChunk), MAX_EXP_OF_TWO(static_cast<size_t>(ceil(log2(MEM_CHUNK_SIZE)))),
    m_pStartBuffer(new uint8_t[nBufferSize]), m_pEndBuffer(m_pStartBuffer + nBufferSize)
{
    m_pChunks = m_pStartBuffer + MEM_CHUNK_NUM;
    memset(m_pStartBuffer, 0, MEM_CHUNK_NUM);
}

MyAllocator::~MyAllocator()
{
    delete[] reinterpret_cast<char*>(m_pStartBuffer);
}

void* MyAllocator::allocate(size_t nObjectSize)
{
    uint8_t nExp = static_cast<uint8_t>(ceil(log2(nObjectSize)));

    if(nExp <= 2)
    {
        nExp = 2;
    }
    else if(MAX_EXP_OF_TWO <= nExp)
    {
        return nullptr;
    }

    for(size_t i = 0; i < MEM_CHUNK_NUM; ++i)
    {
        if(nExp == m_pStartBuffer[i])
        {
            MemChunk* pMemChunk = reinterpret_cast<MemChunk*>(m_pChunks + i * MEM_CHUNK_SIZE);
            if(!pMemChunk->full())
            {
                return reinterpret_cast<MemChunk*>(m_pChunks + i * MEM_CHUNK_SIZE)->placeData();
            }
        }
    }
    for(size_t i = 0; i < MEM_CHUNK_NUM; ++i)
    {
        if( 0 == m_pStartBuffer[i])
        {
            m_pStartBuffer[i] = nExp;
            MemChunk* pMemChunk = reinterpret_cast<MemChunk*>(m_pChunks + i * MEM_CHUNK_SIZE);
            pMemChunk->init(reinterpret_cast<uint8_t*>(pMemChunk + 1), MEM_CHUNK_SIZE - sizeof(MemChunk),
                            static_cast<size_t>(exp2(nExp)));

            return pMemChunk->placeData();
        }
    }
    return nullptr;
}

void MyAllocator::deAlloc(void* pPointer)
{
    if(pPointer > m_pChunks && pPointer < m_pEndBuffer)
    {
        size_t nDataPos = static_cast<size_t>((reinterpret_cast<uint8_t*>(pPointer) - m_pChunks)) / MEM_CHUNK_SIZE;
        MemChunk* pMemChunk = reinterpret_cast<MemChunk*>(m_pChunks + nDataPos * MEM_CHUNK_SIZE);
        pMemChunk->removeData(pPointer);

        if(pMemChunk->empty())
        {
            m_pStartBuffer[nDataPos] = 0;
        }
    }
}
