#include "aiplayer.h"
#include <iostream>
#include <QDebug>

AiPlayer::AiPlayer()
{

}

bool AiPlayer::makeMove(int x, int y)
{
    int max = getBoard()->getFree();
    if (max == 0) return false;
    int idx = (rand() - 1) * max / RAND_MAX;

    idx = getBoard()->getFreeIdx(idx);

    x = idx/getBoard()->getSize();
    y = idx%getBoard()->getSize();

    qDebug() << "X = " << x << "; Y = " << y;

    return getBoard()->setVal(x,y,getValue());
}
