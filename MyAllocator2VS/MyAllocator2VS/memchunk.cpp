#include "memchunk.h"

#include <cmath>

void MemChunk::init(uint8_t *pBuffer, size_t nMemChunkSize, size_t nDataSize)
{
	size_t nNumOfBits = nMemChunkSize / nDataSize;
	size_t nBitSetBufSize = nNumOfBits / 8 + (nNumOfBits % 8 ? 1 : 0);
    m_nDataSize = nDataSize;
    m_nNumOfData = (nMemChunkSize - nBitSetBufSize) / nDataSize;
    m_pBuffer = pBuffer + nBitSetBufSize;
    m_BitSet.init(pBuffer, m_nNumOfData);
}

void* MemChunk::placeData()
{
    std::pair<bool, size_t> Pos = m_BitSet.placeToFreePos();

    if(Pos.first)
    {
        return m_pBuffer + Pos.second * m_nDataSize;
    }
    return nullptr;
}

void MemChunk::removeData(void* pData)
{
    if(pData >= m_pBuffer && pData < m_pBuffer + m_nNumOfData)
    {
        size_t nDataPos = static_cast<size_t>((reinterpret_cast<uint8_t*>(pData) - m_pBuffer)) / m_nDataSize;
        m_BitSet.resetBit(nDataPos);
    }
}

bool MemChunk::full()
{
    return m_BitSet.full();
}

bool MemChunk::empty()
{
    return m_BitSet.empty();
}
