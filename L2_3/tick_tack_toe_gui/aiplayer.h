#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "abstractplayer.h"

class AiPlayer : public AbstractPlayer
{
public:
    AiPlayer();

    bool makeMove(int x, int y);
};

#endif // AIPLAYER_H
