#include "gamerect.h"
#include <curses.h>

GameRect::GameRect()
{
    //ctor
}

GameRect::~GameRect()
{
    //dtorW
}

GameRect::GameRect(const GameRect& other)
{
    //copy ctor
}

GameRect& GameRect::operator=(const GameRect& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void GameRect::drawStep(int stepNumber)
{
    if (stepNumber >= stepsCount())
        return;

    refreshColor();

    int x, y;
    getRectXY(stepNumber, &x, &y);
    mvaddch(y,x,m_Char);
}

void GameRect::drawRect(void)
{
    int steps = stepsCount();
    for (int i = 0; i < steps; i++)
    {
        drawStep(i);
    }
}

int GameRect::stepsCount(void)
{
    return 2*m_Width + 2*m_Height - 2;
}

void GameRect::refreshColor(void)
{
    if (m_Color <= 7)
    {
        attron(COLOR_PAIR(m_Color));
        attroff(A_BOLD);
    } else {
        attron(COLOR_PAIR(m_Color - 7) | A_BOLD);
    }
}

GameRect::RectSide GameRect::getRectSideOffset(int step, int * offset)
{
    if (step == 0)
    {
        *offset = 0;
        return RCT_LEFTTOP;
    }
    if (step < m_Width)
    {
        *offset = step;
        return RCT_TOP;
    }
    if (step == m_Width)
    {
        *offset = 0;
        return RCT_RIGHTTOP;
    }
    step -= m_Width;
    if (step < m_Height - 1)
    {
        *offset = step;
        return RCT_RIGHT;
    }
    if (step == m_Height - 1)
    {
        *offset = 0;
        return RCT_RIGHTBOTTOM;
    }
    step -= (m_Height - 1);
    if (step < m_Width)
    {
        *offset = step;
        return RCT_BOTTOM;
    }
    if (step == m_Width)
    {
        *offset = 0;
        return RCT_LEFTBOTTOM;
    }
    *offset = step - m_Width;
    return RCT_LEFT;
}

void GameRect::getRectXY(int step, int * ret_x, int * ret_y)
{
    // step 0 means the left top corner, the rest is clockwise
    if (step >= stepsCount()) return;

    int offset;
    RectSide side = getRectSideOffset(step, &offset);
    switch(side)
    {
        case RCT_LEFTTOP:
            *ret_x = m_X;
            *ret_y = m_Y;
            return;
        case RCT_TOP:
            *ret_x = m_X + offset;
            *ret_y = m_Y;
            return;
        case RCT_RIGHTTOP:
            *ret_x = m_X + m_Width;
            *ret_y = m_Y;
            return;
        case RCT_RIGHT:
            *ret_x = m_X + m_Width;
            *ret_y = m_Y + offset;
            return;
        case RCT_RIGHTBOTTOM:
            *ret_x = m_X + m_Width;
            *ret_y = m_Y + m_Height - 1;
            return;
        case RCT_BOTTOM:
            *ret_x = m_X + m_Width - offset;
            *ret_y = m_Y + m_Height - 1;
            return;
        case RCT_LEFTBOTTOM:
            *ret_x = m_X;
            *ret_y = m_Y + m_Height - 1;
            return;
        case RCT_LEFT:
            *ret_x = m_X;
            *ret_y = m_Y + m_Height - 1 - offset;
            return;
    }
}
