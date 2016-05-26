#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <abstractplayer.h>

class HumanPlayer : public AbstractPlayer
{
public:
    HumanPlayer();

    bool makeMove(int x, int y);
};

#endif // HUMANPLAYER_H
