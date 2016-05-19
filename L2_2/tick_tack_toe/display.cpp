#include "display.h"
#include <curses.h>

Display::Display()
{
    // Initialize the screen
    initscr();
    nodelay(stdscr,true);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    start_color();
    for (int i = 1; i <= 7; ++i)
        init_pair(i, i, COLOR_BLACK);
}

void Display::printMessage(const char *pStr)
{
    setColor(10);
    mvprintw(23,17," ");
    for (int i = 0; i < TERM_WIDTH - 19; i++)
        addch(' ');
    mvprintw(23, 17, pStr);
    refresh();
}

void Display::setColor(int col)
{
    if (col > 15)
        col -= 15;
    if (col <= 7)
    {
        attron(COLOR_PAIR(col));
        attroff(A_BOLD);
    } else {
        attron(COLOR_PAIR(col - 7) | A_BOLD);
    }
}

int Display::getValue(void)
{
    int sz = ERR;
    while (sz == ERR)
    {
        sz = getch();
    }
    return sz - '0';
}
