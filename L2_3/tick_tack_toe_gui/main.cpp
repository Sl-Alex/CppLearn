#include <QApplication>
#include <iostream>
#include <time.h>
#include "boardmodel.h"
#include "display.h"
#include "mainwindow.h"
#include "abstractplayer.h"
#include "aiplayer.h"
#include "humanplayer.h"

using namespace std;

const int TERM_WIDTH = 80;
const int TERM_HEIGHT = 25;

int rand_coord(BoardModel * pBrd)
{
    int max = pBrd->getSize();
    return (rand() - 1) * max / RAND_MAX;

}

int main(int argc, char *argv[])
{
    srand(time(0));

    QApplication a(argc, argv);

    MainWindow w;
    w.showNormal();

    return a.exec();

    /*
     * Display * pDisplay = new Display();

    AbstractPlayer * pPlayer1;
    AbstractPlayer * pPlayer2;

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

    clear();
    pDisplay->setColor(11);
    mvprintw(10,29, "Choose your player");
    pDisplay->setColor(7);
    mvprintw(12,27, "1. Player 1 (X)");
    mvprintw(13,27, "2. Player 2 (O)");
    mvprintw(14,27, "3. I just want to look");
    refresh();

    int mode = 0;
    while ((mode < 1) || (mode > 3))
    {
        mode = getch() - '0';
    }

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

    pPlayer1->setDisplay(pDisplay);
    pPlayer2->setDisplay(pDisplay);

    clear();
    pDisplay->setColor(11);
    mvprintw(10,29, "Enter board size (3 - 9)");
    pDisplay->setColor(7);
    mvprintw(12,27, "Default is 3");
    refresh();

    int size = 3;
    int sz = ERR;
    while (sz == ERR)
    {
        sz = getch();
    }
    sz = sz - '0';
    if ((sz >= 3 ) && (sz <= 9))
        size = sz;

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

    Board * pBrd = new Board(size,size);
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
    */
}

