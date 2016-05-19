#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "display.h"

class Board
{
public:
    enum Value {VAL_EMPTY = 0, VAL_X, VAL_O, VAL_MAX};
    enum State {ST_ACTIVE = 0, ST_WIN_X, ST_WIN_O, ST_WIN_NONE};
    Board(int size = 3, int level = 3);
    ~Board();

    bool setVal(int x, int y, Value val);
    Value getVal(int x, int y);

    State getState();

    void setDisplay(Display * pDisp) { pDisplay = pDisp; }

    int getSize(void) { return mSize; }
    int getFree(void) { return mFreeMoves.size(); }
    int getFreeIdx(int num) { return mFreeMoves.at(num); }

    void printBoard(void);

private:
    int mSize;
    int mLevel;


    State mState;

    std::vector<int> mFreeMoves;

    void updateState(int x, int y);

    Value * pData;

    Display * pDisplay;
};

#endif // BOARD_H
