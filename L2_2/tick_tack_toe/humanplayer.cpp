#include "humanplayer.h"

HumanPlayer::HumanPlayer()
{

}

bool HumanPlayer::makeMove(void)
{
    int x, y;
    while(true)
    {
        getDisplay()->printMessage("Enter x and y coordinates");

        x = getDisplay()->getValue() - 1;
        y = getDisplay()->getValue() - 1;
        if (!getBoard()->setVal(x,y,getValue()))
            getDisplay()->printMessage("Wrong coordinates, try once again");
        else
            break;
    }

    getBoard()->printBoard();

    if (getBoard()->getState() == Board::ST_ACTIVE)
        return true;
    else
        return false;
}

