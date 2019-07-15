#include "membitset.h"

void MemBitSet::init(uint8_t *pBuffer, size_t nNumOfBit)

{
	m_fFull = false;
    m_nByteSize = nNumOfBit / 8 + ( nNumOfBit % 8 ? 1 : 0);
    m_nNumOfData = nNumOfBit;
    m_BitArr = pBuffer;
    memset(m_BitArr, 0, m_nByteSize);
}

void MemBitSet::setBit(size_t nPos)
{
    if(nPos <= m_nNumOfData)
    {
        size_t nBytePos = nPos / 8;
        size_t nShift = nPos % 8;
        uint8_t nBitMask = 128;
        if(nShift < 8)
        {
            nBitMask >>= nShift;
            m_BitArr[nBytePos] |= nBitMask;
        }
    }
}

void MemBitSet::resetBit(size_t nPos)
{
    if(nPos <= m_nNumOfData)
    {
        size_t nBytePos = nPos / 8;
        size_t nShift = nPos % 8;
        uint8_t nBitMask = 128;
        if(nShift < 8)
        {
            nBitMask >>= nShift;
            m_BitArr[nBytePos] &= ~nBitMask;
			m_fFull = false;
        }
    }
}

std::pair<bool, size_t> MemBitSet::placeToFreePos()
{
    for (size_t i = 0; i < m_nByteSize; ++i)
    {
        if(m_BitArr[i] < 255)
        {
            uint8_t nBitMask = 128;
            for (size_t j = 0, nLim = ( i == m_nByteSize - 1 ? m_nNumOfData % 8 : 8); j < nLim; ++j)
            {
                if(!(m_BitArr[i] & nBitMask))
                {
                    m_BitArr[i] |= nBitMask;
                    return {true, i * 8 + j};
                }
                nBitMask >>= 1;
            }
        }
    }
    m_fFull = true;
    return {false, 0};
}

bool MemBitSet::full()
{
    return m_fFull;
}

bool MemBitSet::empty()
{
    for (size_t i = 0; i < m_nByteSize; ++i)
    {
        if(m_BitArr[i] > 0)
        {
            return false;
        }
    }
    return true;
}
