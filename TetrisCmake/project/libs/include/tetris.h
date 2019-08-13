#ifndef TETRIS_H
#define TETRIS_H

#include <cstddef>
#include <array>
#include <string>
#include <chrono>

#include "tetris_object.h"
#include "random_uint32_t.h"
#include "tetris_game_export.h"

class TETRIS_GAME_EXPORT tetris
{
public:
    tetris();

    bool isCellFree(size_t nX, size_t nY) const;
    void setCellFilled(size_t nX, size_t nY);
    void createObject();
    void printMap();
    void printOblect();
    void engine();
    void mainAction();

private:
    enum class MoveDirection
    {
        DOWN  = 0,
        LEFT  = 1,
        RIGHT = 2,
        TURN  = 3
    };

    static constexpr size_t FIELD_WIDTH     = 10;
    static constexpr size_t FIELD_HEIGHT    = 20;
    static constexpr size_t FIELD_SHIFT_X   = 6;
    static constexpr size_t FIELD_SHIFT_Y   = 2;
    static constexpr size_t START_OBJ_POS_X = 4;
    static constexpr size_t START_OBJ_POS_Y = 0;
    static constexpr size_t POINTS_PER_LINE = 100;

    pTetrisObject m_pObject;
    Random_uint32_t m_rand_6 {0, 6};
    size_t m_nLastPosX = 0;
    size_t m_nLastPosY = 0;
    size_t m_nPoints   = 0;
    bool m_fBreak      = true;
    bool m_fCommit     = false;
    std::chrono::time_point<std::chrono::system_clock> m_LastTime = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> m_TimeNow;
    std::chrono::duration<double> m_TimeDifference;

    std::array <std::string, FIELD_HEIGHT + 1> m_Field =
    {{
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"|          |"},
         {"------------"}
     }};

    void clearOblect();
    void moveOblect(MoveDirection direction);
    void commitObject();
    bool checkCollision(MoveDirection direction);
    void clearFilled();
};

#endif // TETRIS_H
