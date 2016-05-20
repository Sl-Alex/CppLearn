#include <iostream>
#include <curses.h>
#include <time.h>
#include "board.h"
#include "display.h"
#include "abstractplayer.h"
#include "aiplayer.h"
#include "humanplayer.h"

using namespace std;

const int TERM_WIDTH = 80;
const int TERM_HEIGHT = 25;

int rand_coord(Board * pBrd)
{
    int max = pBrd->getSize();
    return (rand() - 1) * max / RAND_MAX;

}

int getVal(void)
{
    int sz = ERR;
    while (sz == ERR)
    {
        sz = getch();
    }
    return sz - '0';
}

int main()
{
    Display * pDisplay = new Display();

    AbstractPlayer * pPlayer1;
    AbstractPlayer * pPlayer2;

    // Print welcome screen
    clear();
    pDisplay->setColor(7);
    mvprintw(10,25, "Welcome to the ");
    pDisplay->setColor(11);
    addstr("TIC-");
    pDisplay->setColor(9);
    addstr("TAC-");
    pDisplay->setColor(8);
    addstr("TOE,");
    pDisplay->setColor(7);
    mvprintw(11,21, "the best computer game ever written");
    mvprintw(13,28, "Press any key to proceed");
    refresh();
    while(getch() == ERR);

    // Ask for play mode
    const char * mode_list[3] = {"1. Player 1 (X)",
                 "2. Player 2 (O)",
                 "3. I just want to look"};

    int mode = pDisplay->ask("Choose your player", mode_list,3,1);

    // Initialize players
    switch(mode)
    {
        case 1:
            pPlayer1 = new HumanPlayer();
            pPlayer2 = new AiPlayer();
        break;
        case 2:
            pPlayer1 = new AiPlayer();
            pPlayer2 = new HumanPlayer();
        break;
        case 3:
            pPlayer1 = new AiPlayer();
            pPlayer2 = new AiPlayer();
        break;
    }

    pPlayer1->setValue(Board::VAL_X);
    pPlayer2->setValue(Board::VAL_O);

    // Get board size
    int size = pDisplay->ask("Enter board size (3 - 9)",0,7,3);

    // Get win limit
    int limit = size;
    if (size > 3)
        limit = pDisplay->ask("Enter win limit (3 to board size)", 0, size - 3 + 1, 3);

    clear();
    pDisplay->setColor(2);
    for (int i = 0; i < TERM_WIDTH; i++)
        mvaddch(0, i, '#');
    for (int i = 0; i < TERM_WIDTH; i++)
        mvaddch(TERM_HEIGHT-1, i, '#');
    for (int i = 0; i < TERM_HEIGHT; i++)
        mvaddch(i, 0, '#');
    for (int i = 0; i < TERM_HEIGHT; i++)
        mvaddch(i, 79, '#');

    pDisplay->setColor(4);
    mvprintw(1,2," P1   P2");
    pDisplay->setColor(5);
    mvprintw(2,2,"You   CPU");
    pDisplay->setColor(2);
    for (int i = 0; i < TERM_HEIGHT; i++)
        mvaddch(i, 12, '#');
    for (int i = 0; i < TERM_HEIGHT; i++)
        mvaddch(i, 6, '#');
    for (int i = 0; i < 12; i++)
        mvaddch(3, i, '#');
    mvaddch(2,16,'0' + mode);
    mvaddch(4,16,'0' + size);

    refresh();

    srand(time(0));

    Board * pBrd = new Board(size,limit);
    pBrd->setDisplay(pDisplay);

    pPlayer1->setBoard(pBrd);
    pPlayer2->setBoard(pBrd);

    pBrd->printBoard();

    while (true)
    {
        pPlayer1->makeMove();

        if (pBrd->getState() != Board::ST_ACTIVE)
            break;

        pPlayer2->makeMove();

        if (pBrd->getState() != Board::ST_ACTIVE)
            break;
    }

    if (pBrd->getState() == Board::ST_WIN_NONE)
    {
        if (mode == 3)
            pDisplay->printMessage("There are no loosers and winners, only the universe...");
        else
            pDisplay->printMessage("Computer will never overcome another computer!");
    }
    else if (((mode == 1) && (pBrd->getState() == Board::ST_WIN_X)) ||
             ((mode == 2) && (pBrd->getState() == Board::ST_WIN_O)))
    {
        pDisplay->printMessage("You won! Of course, human's brains are smarter...");
    }
    else if (mode != 3)
    {
        pDisplay->printMessage("You loose! I'm the winner!");
    }
    else if (mode == 3)
    {
        if (pBrd->getState() == Board::ST_WIN_X)
            pDisplay->printMessage("\"X\" computer won");
        else
            pDisplay->printMessage("\"O\" computer won");
    }

    return 0;
    delete pBrd;
}

