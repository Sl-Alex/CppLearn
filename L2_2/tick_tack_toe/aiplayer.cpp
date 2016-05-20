#include "aiplayer.h"
#include <iostream>

AiPlayer::AiPlayer()
{

}

bool AiPlayer::makeMove(void)
{
    int max = getBoard()->getFree();
    int idx = (rand() - 1) * max / RAND_MAX;

    idx = getBoard()->getFreeIdx(idx);

    int x, y;

    x = idx/getBoard()->getSize();
    y = idx%getBoard()->getSize();

    getBoard()->setVal(x,y,getValue());

    char msg[100];
    if (getValue() == Board::VAL_X)
        sprintf(msg,"Computer (X) chooses cell %u,%u. Press any key to continue.",x + 1,y + 1);
    else
        sprintf(msg,"Computer (O) chooses cell %u,%u. Press any key to continue.",x + 1,y + 1);

    getBoard()->printBoard();
    getDisplay()->printMessage(msg);
    getDisplay()->getValue();

    if (getBoard()->getState() == Board::ST_ACTIVE)
        return true;
    else
        return false;
}
