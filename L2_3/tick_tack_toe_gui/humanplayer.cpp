#include "humanplayer.h"

HumanPlayer::HumanPlayer()
{

}

bool HumanPlayer::makeMove(int x, int y)
{
    return getBoard()->setVal(x,y,getValue());
}

