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

int Display::ask(const char * message, const char ** options, int numOptions, int start)
{
    clear();
    setColor(11);
    mvprintw(8,29, message);
    setColor(7);
    if (options == 0)
    {
        mvprintw(10,27, "Range from ");
        addch('0' + start);
        printw(" to ");
        addch('0' + start + numOptions - 1);
    }
    else
    {
        for (int i = 0; i < numOptions; i++)
        {
            mvprintw(10 + i,27, options[i]);
        }
    }
    refresh();

    int res = start - 1;
    while ((res < start) || (res > start + numOptions - 1))
    {
        res = getch() - '0';
    }
    return res;
}
