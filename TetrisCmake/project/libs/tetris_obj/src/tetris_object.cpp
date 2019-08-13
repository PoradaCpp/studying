#include "tetris_object.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Tetris_Object
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TetrisObject::TetrisObject(std::array<bool, 16> Arr, size_t nX, size_t nY, size_t nObjWidth, size_t nObjHeight):
    m_nX(nX),
    m_nY(nY),
    m_nObjWidth(nObjWidth),
    m_nObjHeight(nObjHeight)
{
    for (size_t i = 0; i < TetrisObject::m_nHeight; ++i)
    {
        for (size_t j = 0; j < TetrisObject::m_nWidth; ++j)
        {
            m_Arr[i][j] = Arr[i * TetrisObject::m_nHeight + j];
        }
    }
}

size_t TetrisObject::getObjWidth() const
{
    return m_nObjWidth;
}

size_t TetrisObject::getObjHeight() const
{
    return m_nObjHeight;
}

size_t TetrisObject::getObjBegX() const
{
    return m_nX;
}

size_t TetrisObject::getObjBegY() const
{
    return m_nY;
}

bool TetrisObject::isCellFilled(size_t nX, size_t nY) const
{
    return m_Arr[nX][nY];
}

pTetrisObject TetrisObject::rotate()
{
    if(m_pRotationFunc)
    {
        return m_pRotationFunc();
    }
    return nullptr;
}

void TetrisObject::setCreateObjFunc(rotationFunc rotateFunc)
{
    m_pRotationFunc = rotateFunc;
}
