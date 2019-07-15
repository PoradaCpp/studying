#ifndef MEMBITSET_HPP
#define MEMBITSET_HPP

#include <stdint.h>
#include <cstring>
#include <utility>


class MemBitSet
{
public:
    void init(uint8_t *pBuffer, size_t nBitNumber);

    void setBit(size_t nPos);
    void resetBit(size_t nPos);
    std::pair<bool, size_t> placeToFreePos();

    bool full();
    bool empty();

private:
    size_t m_nByteSize = 0;
    size_t m_nNumOfData = 0;
    bool m_fFull = false;
    uint8_t *m_BitArr = nullptr;
};

#endif // MEMBITSET_HPP
