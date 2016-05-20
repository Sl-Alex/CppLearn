#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include "board.h"
#include "display.h"

class AbstractPlayer
{
public:

    void setValue(Board::Value val) { mValue = val; }
    Board::Value getValue() {return mValue; }
    Board * getBoard(void) { return pBoard; }
    void setBoard(Board * pBrd) { pBoard = pBrd; }

    virtual bool makeMove(void) = 0;

private:

    Board::Value mValue = Board::VAL_EMPTY;
    Board * pBoard;
};

#endif // ABSTRACTPLAYER_H
