#include "stdafx.h"
#include "consolecolour.h"

ConsoleColour::ConsoleColour()
{
    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}


void ConsoleColour::SetColour(cColour TextColour)
{
    SetConsoleTextAttribute(m_hConsole, TextColour);
}
