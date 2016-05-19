#include "board.h"
#include "string.h"
#include <curses.h>

Board::Board(int size, int level)
{
    mSize = size;

    mLevel = level;

    mState = ST_ACTIVE;

    pData = new Value[mSize*mSize];
    mFreeMoves.reserve(mSize*mSize);
    for (int i = 0; i < mSize* mSize; i++)
    {
        mFreeMoves.push_back(i);
    }
    memset(pData,0,mSize*mSize*sizeof(Value));
}

Board::~Board()
{
    delete[] pData;
}

bool Board::setVal(int x, int y, Value val)
{
    // Check limits
    if ((x < 0) || (x >= mSize)) return false;
    if ((y < 0) || (y >= mSize)) return false;

    Value * pVal = &pData[x*mSize+y];

    // Check if it is empty
    if (*pVal != VAL_EMPTY) return false;

    // Set value
    *pVal = val;

    // Remove it from the "mFreeMoves" vector;
    for (auto it = mFreeMoves.begin(); it != mFreeMoves.end(); it++)
    {
        if (*it == x*mSize+y)
        {
            mFreeMoves.erase(it);
            break;
        }
    }

    // Check
    if (mState != ST_ACTIVE)
        return true;

    updateState(x,y);

    if ((mState == ST_ACTIVE) && mFreeMoves.size() == 0)
        mState = ST_WIN_NONE;

    return true;
}

Board::Value Board::getVal(int x, int y)
{
    // Check limits
    if ((x < 0) || (x >= mSize)) return VAL_EMPTY;
    if ((y < 0) || (y >= mSize)) return VAL_EMPTY;

    return pData[x*mSize+y];
}

Board::State Board::getState()
{
    return mState;
}

void Board::updateState(int x, int y)
{
    int x1,y1,x2,y2;

    int curLevel;

    x1 = x - mLevel - 1;
    x2 = x + mLevel - 1;
    y1 = y - mLevel - 1;
    y2 = y + mLevel - 1;

    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 >= mSize) x2 = mSize - 1;
    if (y2 >= mSize) y2 = mSize - 1;

    Value * pVal;
    curLevel = 0;
    Value val_old = VAL_EMPTY;

    // Check "-" line
    for (int _x = x1; _x <= x2; _x++)
    {
        pVal = &pData[_x*mSize+y];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = *pVal;
    }
    val_old = VAL_EMPTY;
    // Check "|" line
    for (int _y = y1; _y <= y2; _y++)
    {
        pVal = &pData[x*mSize+_y];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = *pVal;
    }
    val_old = VAL_EMPTY;
    // Check "\" line
    for (int _x = x1; _x <= x2; _x++)
    {
        pVal = &pData[_x*mSize+y1+_x-x1];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }

        val_old = *pVal;
    }
    val_old = VAL_EMPTY;
    // Check "/" line
    for (int _x = x1; _x <= x2; _x++)
    {
        pVal = &pData[_x*mSize+y2-_x+x1];
        if (*pVal != val_old)
            curLevel = 0;

        if (*pVal != VAL_EMPTY)
        {
            curLevel++;
            if (curLevel >= mLevel)
            {
                if (*pVal == VAL_X)
                    mState = ST_WIN_X;
                else
                    mState = ST_WIN_O;
                return;
            }
        }
        val_old = *pVal;
    }
}

void Board::printBoard(void)
{
#define X_CENTER 45
#define Y_CENTER 13
    int x_off = X_CENTER - mSize;
    int y_off = Y_CENTER - mSize;

    for (int y = 0; y < mSize; y++)
    {
        for (int x = 0; x < mSize; x++)
        {
            Board::Value val = getVal(x,y);

            if (val == Board::VAL_X)
            {
                pDisplay->setColor(8);
                mvaddch(y_off+y*2,x_off+x*2,'X');
            }
            if (val == Board::VAL_O)
            {
                pDisplay->setColor(12);
                mvaddch(y_off+y*2,x_off+x*2,'O');
            }

        }
    }
    pDisplay->setColor(2);
    for (int y = 0; y < mSize - 1; y++)
    {
        for (int x = 0; x < mSize*2-1; x++)
        {
            mvaddch(y_off+y*2+1,x_off+x,'-');
        }
    }
    for (int x = 0; x < mSize - 1; x++)
    {
        for (int y = 0; y < mSize*2-1; y++)
        {
            mvaddch(y_off+y,x_off+x*2+1,'|');
        }
    }
    pDisplay->setColor(11);
    for (int y = 0; y < mSize; y++)
    {
        mvaddch(y_off + y * 2, x_off - 2, '1' + y);
    }
    for (int x = 0; x < mSize; x++)
    {
        mvaddch(y_off - 2, x_off + x * 2, '1' + x);
    }
    refresh();
}
