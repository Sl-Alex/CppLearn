#ifndef ABSTRACTPLAYER_H
#define ABSTRACTPLAYER_H

#include "boardmodel.h"

class AbstractPlayer
{
public:

    void setValue(BoardModel::Value val) { mValue = val; }
    BoardModel::Value getValue() {return mValue; }
    BoardModel * getBoard(void) { return pBoard; }
    void setBoard(BoardModel * pBrd) { pBoard = pBrd; }

    virtual bool makeMove(int x, int y) = 0;
    virtual ~AbstractPlayer() {}

private:

    BoardModel::Value mValue = BoardModel::VAL_EMPTY;
    BoardModel * pBoard;
};

#endif // ABSTRACTPLAYER_H
