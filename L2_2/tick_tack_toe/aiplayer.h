#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "abstractplayer.h"

class AiPlayer : public AbstractPlayer
{
public:
    AiPlayer();

    bool makeMove(void);
};

#endif // AIPLAYER_H
