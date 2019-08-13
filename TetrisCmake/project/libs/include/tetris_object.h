#ifndef TETRIS_OBJECT_H
#define TETRIS_OBJECT_H

#include <cstddef>
#include <memory>
#include <array>
#include <functional>
#include "tetris_game_export.h"

class TetrisObject;
typedef std::unique_ptr<TetrisObject> pTetrisObject;
typedef std::function<std::unique_ptr<TetrisObject>()> rotationFunc;

class TETRIS_GAME_EXPORT TetrisObject
{
public:    
    TetrisObject(std::array<bool, 16> Arr, size_t nX, size_t nY, size_t nObjWidth, size_t nObjHeight);

    size_t getObjWidth() const;
    size_t getObjHeight() const;
    size_t getObjBegX() const;
    size_t getObjBegY() const;
    bool isCellFilled(size_t nX, size_t nY) const;
    pTetrisObject rotate();
    void setCreateObjFunc(rotationFunc rotateFunc);

    static constexpr size_t m_nCenterX = 2;
    static constexpr size_t m_nCenterY = 2;
    static constexpr size_t m_nWidth  = 4;
    static constexpr size_t m_nHeight = 4;

protected:
    size_t m_nX         = 0;
    size_t m_nY         = 0;
    size_t m_nObjWidth  = 0;
    size_t m_nObjHeight = 0;
    bool m_Arr[m_nHeight][m_nWidth];
    rotationFunc m_pRotationFunc;
};

struct TETRIS_GAME_EXPORT TetrisObjects
{
    TetrisObjects():
        Tetris_O_R0({0, 0, 0, 0,
                     0, 1, 1, 0,
                     0, 1, 1, 0,
                     0, 0, 0, 0}, 1, 1, 2, 2),

        Tetris_I_R0({0, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 1, 0, 0}, 1, 0, 1, 4),

        Tetris_I_R1({0, 0, 0, 0,
                     1, 1, 1, 1,
                     0, 0, 0, 0,
                     0, 0, 0, 0}, 0, 1, 4, 1),

        Tetris_L_R0({0, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 1, 1, 0,
                     0, 0, 0, 0}, 1, 0, 2, 3),

        Tetris_L_R1({0, 0, 0, 0,
                     1, 1, 1, 0,
                     1, 0, 0, 0,
                     0, 0, 0, 0}, 0, 1, 3, 2),

        Tetris_L_R2({1, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0}, 0, 0, 2, 3),

        Tetris_L_R3({0, 0, 1, 0,
                     1, 1, 1, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0}, 0, 0, 3, 2),

        Tetris_J_R0({0, 1, 0, 0,
                     0, 1, 0, 0,
                     1, 1, 0, 0,
                     0, 0, 0, 0}, 0, 0, 2, 3),

        Tetris_J_R1({1, 0, 0, 0,
                     1, 1, 1, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0}, 0, 0, 3, 2),

        Tetris_J_R2({0, 1, 1, 0,
                     0, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0}, 1, 0, 2, 3),

        Tetris_J_R3({0, 0, 0, 0,
                     1, 1, 1, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 0}, 0, 1, 3, 2),

        Tetris_S_R0({0, 1, 1, 0,
                     1, 1, 0, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0}, 0, 0, 3, 2),

        Tetris_S_R1({1, 0, 0, 0,
                     1, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0}, 0, 0, 2, 3),

        Tetris_Z_R0({1, 1, 0, 0,
                     0, 1, 1, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0}, 0, 0, 3, 2),

        Tetris_Z_R1({0, 0, 1, 0,
                     0, 1, 1, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0}, 1, 0, 2, 3),

        Tetris_T_R0({0, 1, 0, 0,
                     1, 1, 1, 0,
                     0, 0, 0, 0,
                     0, 0, 0, 0}, 0, 0, 3, 2),

        Tetris_T_R1({0, 1, 0, 0,
                     0, 1, 1, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0}, 1, 0, 2, 3),

        Tetris_T_R2({0, 0, 0, 0,
                     1, 1, 1, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0}, 0, 1, 3, 2),

        Tetris_T_R3({0, 1, 0, 0,
                     1, 1, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 0 }, 0, 0, 2, 3)
    {
        Tetris_O_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_O_R0);
        });
        Tetris_I_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_I_R1);
        });
        Tetris_I_R1.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_I_R0);
        });
        Tetris_L_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_L_R1);
        });
        Tetris_L_R1.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_L_R2);
        });
        Tetris_L_R2.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_L_R3);
        });
        Tetris_L_R3.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_L_R0);
        });
        Tetris_J_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_J_R1);
        });
        Tetris_J_R1.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_J_R2);
        });
        Tetris_J_R2.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_J_R3);
        });
        Tetris_J_R3.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_J_R0);
        });
        Tetris_S_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_S_R1);
        });
        Tetris_S_R1.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_S_R0);
        });
        Tetris_Z_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_Z_R1);
        });
        Tetris_Z_R1.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_Z_R0);
        });
        Tetris_T_R0.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_T_R1);
        });
        Tetris_T_R1.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_T_R2);
        });
        Tetris_T_R2.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_T_R3);
        });
        Tetris_T_R3.setCreateObjFunc([this]
        {
            return std::make_unique<TetrisObject>(Tetris_T_R0);
        });
    }

    TetrisObject Tetris_O_R0;
    TetrisObject Tetris_I_R0;
    TetrisObject Tetris_I_R1;
    TetrisObject Tetris_L_R0;
    TetrisObject Tetris_L_R1;
    TetrisObject Tetris_L_R2;
    TetrisObject Tetris_L_R3;
    TetrisObject Tetris_J_R0;
    TetrisObject Tetris_J_R1;
    TetrisObject Tetris_J_R2;
    TetrisObject Tetris_J_R3;
    TetrisObject Tetris_S_R0;
    TetrisObject Tetris_S_R1;
    TetrisObject Tetris_Z_R0;
    TetrisObject Tetris_Z_R1;
    TetrisObject Tetris_T_R0;
    TetrisObject Tetris_T_R1;
    TetrisObject Tetris_T_R2;
    TetrisObject Tetris_T_R3;
};

namespace Tetris_Objects
{
    static TetrisObjects tetrisObjects;
}

#endif // TETRIS_OBJECT_H
