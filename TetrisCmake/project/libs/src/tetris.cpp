#include "tetris.h"

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>

tetris::tetris()
{
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle,&structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo( handle, &structCursorInfo );
}

bool tetris::isCellFree(size_t nX, size_t nY) const
{
    return (m_Field[nY]).at(nX) == ' ';
}

void tetris::setCellFilled(size_t nX, size_t nY)
{
    (m_Field[nY]).at(nX) = '*';
}

void tetris::createObject()
{
    switch(m_rand_6())
    {
    case 0:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_O_R0);
        break;
    case 1:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_I_R0);
        break;
    case 2:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_L_R0);
        break;
    case 3:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_J_R0);
        break;
    case 4:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_S_R0);
        break;
    case 5:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_Z_R0);
        break;
    default:
        m_pObject = std::make_unique<TetrisObject>(Tetris_Objects::tetrisObjects.Tetris_T_R0);
        break;
    }
    m_nLastPosX = START_OBJ_POS_X * 2 + FIELD_SHIFT_X;
    m_nLastPosY = START_OBJ_POS_Y + FIELD_SHIFT_Y;
}

void tetris::printMap()
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for(size_t i = 0; i < FIELD_SHIFT_X; ++i)
    {
        std::cout << ' ';
    }
    std::cout << "CURRENT SCORE: " << m_nPoints << '\n';
    coord.Y = FIELD_SHIFT_Y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (std::string sLine: m_Field)
    {
        for(size_t i = 0; i < FIELD_SHIFT_X; ++i)
        {
            std::cout << ' ';
        }
        for (char cSym : sLine)
        {
            std::cout << cSym << ' ';
        }
        std::cout << '\n';
    }
}

void tetris::printOblect()
{
    COORD coord;
    coord.X = m_nLastPosX + (m_pObject->getObjBegX() % 2 ? m_pObject->getObjBegX() + 1: m_pObject->getObjBegX());
    coord.Y = m_nLastPosY + m_pObject->getObjBegY();

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for(size_t i = m_pObject->getObjBegY(), nEndY = m_pObject->getObjBegY() + m_pObject->getObjHeight(); i < nEndY; ++i)
    {
        for(size_t j = m_pObject->getObjBegX(), nEndX = m_pObject->getObjBegX() + m_pObject->getObjWidth(); j < nEndX; ++j)
        {
            std::cout << (m_pObject->isCellFilled(i, j) ? '*' : ' ') << ' ';
        }
        ++coord.Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
}

void tetris::clearOblect()
{
    COORD coord;
    coord.X = m_nLastPosX + (m_pObject->getObjBegX() % 2 ? m_pObject->getObjBegX() + 1: m_pObject->getObjBegX());
    coord.Y = m_nLastPosY + m_pObject->getObjBegY();

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for(size_t i = m_pObject->getObjBegY(), nEndY = m_pObject->getObjBegY() + m_pObject->getObjHeight(); i < nEndY; ++i)
    {
        for(size_t j = m_pObject->getObjBegX(), nEndX = m_pObject->getObjBegX() + m_pObject->getObjWidth(); j < nEndX; ++j)
        {
            std::cout << ' ' << ' ';
        }
        ++coord.Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
}

void tetris::moveOblect(MoveDirection direction)
{
    if(m_pObject)
    {
        clearOblect();
        switch(direction)
        {
        case MoveDirection::DOWN:
            if(!checkCollision(direction))
            {
                ++m_nLastPosY;
            }
            else
            {
                m_fCommit = true;
            }
            break;
        case MoveDirection::LEFT:
            if(!checkCollision(direction))
            {
                m_nLastPosX -= 2;
            }
            break;
        case MoveDirection::RIGHT:
            if(!checkCollision(direction))
            {
                m_nLastPosX += 2;
            }
            break;
        case MoveDirection::TURN:
            auto pTemp = m_pObject->rotate();
            std::swap(pTemp, m_pObject);
            if(checkCollision(direction))
            {
                std::swap(pTemp, m_pObject);
            }
            break;
        }
        printOblect();
    }
}

void tetris::engine()
{
    while(m_fBreak)
    {
        if(kbhit())
        {
            switch(_getch())
            {
            case 224:
                switch(_getch())
                {
                case 75:
                    moveOblect(MoveDirection::LEFT);
                    break;
                case 77:
                    moveOblect(MoveDirection::RIGHT);
                    break;
                case 80:
                    moveOblect(MoveDirection::DOWN);
                    break;
                case 72:
                    moveOblect(MoveDirection::TURN);
                    break;
                }
                break;

            case 27:
                COORD coord;
                coord.X = 0;
                coord.Y = FIELD_HEIGHT + FIELD_SHIFT_Y + 2;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                std::cout << "Quit...\n";
                m_fBreak = false;
                break;
            }
        }
        m_TimeNow = std::chrono::system_clock::now();
        m_TimeDifference = m_TimeNow - m_LastTime;

        if(m_TimeDifference.count() > 1)
        {
            moveOblect(MoveDirection::DOWN);
            m_LastTime = std::chrono::system_clock::now();

            if(m_fCommit)
            {
                m_fCommit = false;
                commitObject();
                m_pObject.reset();
                createObject();
                clearFilled();
            }
        }
    }
}

void tetris::mainAction()
{
    printMap();
    createObject();
    printOblect();
    engine();
}

void tetris::commitObject()
{
    size_t nX(0), nY(0);

    for(size_t i = m_pObject->getObjBegY(), nEndY = m_pObject->getObjBegY() + m_pObject->getObjHeight(); i < nEndY; ++i)
    {
        nY = i + (m_nLastPosY - FIELD_SHIFT_Y);

        for(size_t j = m_pObject->getObjBegX(), nEndX = m_pObject->getObjBegX() + m_pObject->getObjWidth(); j < nEndX; ++j)
        {
            nX = j + (m_nLastPosX - FIELD_SHIFT_X) / 2;

            if(m_pObject->isCellFilled(i, j))
            {
                setCellFilled(nX, nY);
            }
        }
    }
    printMap();
}

bool tetris::checkCollision(MoveDirection direction)
{
    size_t nX(0), nY(0);
    size_t nDX((m_nLastPosX - FIELD_SHIFT_X) / 2);
    size_t nDY(m_nLastPosY - FIELD_SHIFT_Y);

    switch(direction)
    {
    case MoveDirection::DOWN:
        ++nDY;
        break;
    case MoveDirection::LEFT:
        nDX -= 1;
        break;
    case MoveDirection::RIGHT:
        nDX += 1;
        break;
    case MoveDirection::TURN:
        break;
    }

    for(size_t i = m_pObject->getObjBegY(), nEndY = m_pObject->getObjBegY() + m_pObject->getObjHeight(); i < nEndY; ++i)
    {
        nY = i + nDY;

        for(size_t j = m_pObject->getObjBegX(), nEndX = m_pObject->getObjBegX() + m_pObject->getObjWidth(); j < nEndX; ++j)
        {
            nX = j + nDX;

            if(m_pObject->isCellFilled(i, j) && !isCellFree(nX, nY))
            {
                return true;
            }
        }
    }
    return false;
}

void tetris::clearFilled()
{
    bool fFilled;

    for (size_t i = m_Field.size() - 1; i < m_Field.size(); --i)
    {
        fFilled = true;

        for (char cSym : m_Field[i])
        {
            if(('-' == cSym) || ( cSym != '|' && cSym != '*'))
            {
                fFilled = false;
                break;
            }
        }
        if(fFilled)
        {
            for (size_t j = i; j >= 1; --j)
            {
                m_Field[j] = m_Field[j - 1];
            }
            m_Field[0] = "|          |";
            i = m_Field.size() - 1;
            m_nPoints += POINTS_PER_LINE;
            printMap();
        }
    }
}
