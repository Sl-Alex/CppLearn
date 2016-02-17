#include <iostream>
#include <curses.h>

using namespace std;

enum RectSide{
    RCT_LEFTTOP,
    RCT_TOP,
    RCT_RIGHTTOP,
    RCT_RIGHT,
    RCT_RIGHTBOTTOM,
    RCT_BOTTOM,
    RCT_LEFTBOTTOM,
    RCT_LEFT
};

RectSide getRectSideOffset(int w, int h, int step, int * offset);

void color (int c)
{
    if (c > 15)
        c -= 15;
    //c &= 0x0F;
    if (c <= 7)
    {
        attron(COLOR_PAIR(c));
        attroff(A_BOLD);
    } else {
        attron(COLOR_PAIR(c - 7) | A_BOLD);
    }
}

int getRectSteps(int w, int h)
{
    return 2*w + 2*h - 2;
}

void getRectXY(int x, int y, int w, int h, int step, int * ret_x, int * ret_y)
{
    // step 0 means the left top corner, the rest is clockwise
    if (step >= getRectSteps(w,h)) return;

    int offset;
    RectSide side = getRectSideOffset(w,h,step,&offset);
    switch(side)
    {
        case RCT_LEFTTOP:
            *ret_x = x;
            *ret_y = y;
            return;
        case RCT_TOP:
            *ret_x = x + offset;
            *ret_y = y;
            return;
        case RCT_RIGHTTOP:
            *ret_x = x + w;
            *ret_y = y;
            return;
        case RCT_RIGHT:
            *ret_x = x + w;
            *ret_y = y + offset;
            return;
        case RCT_RIGHTBOTTOM:
            *ret_x = x + w;
            *ret_y = y + h - 1;
            return;
        case RCT_BOTTOM:
            *ret_x = x + w - offset;
            *ret_y = y + h - 1;
            return;
        case RCT_LEFTBOTTOM:
            *ret_x = x;
            *ret_y = y + h - 1;
            return;
        case RCT_LEFT:
            *ret_x = x;
            *ret_y = y + h - 1 - offset;
            return;
    }
}

RectSide getRectSideOffset(int w, int h, int step, int * offset)
{
    if (step == 0)
    {
        *offset = 0;
        return RCT_LEFTTOP;
    }
    if (step < w)
    {
        *offset = step;
        return RCT_TOP;
    }
    if (step == w)
    {
        *offset = 0;
        return RCT_RIGHTTOP;
    }
    step -= w;
    if (step < h - 1)
    {
        *offset = step;
        return RCT_RIGHT;
    }
    if (step == h - 1)
    {
        *offset = 0;
        return RCT_RIGHTBOTTOM;
    }
    step -= (h - 1);
    if (step < w)
    {
        *offset = step;
        return RCT_BOTTOM;
    }
    if (step == w)
    {
        *offset = 0;
        return RCT_LEFTBOTTOM;
    }
    *offset = step - w;
    return RCT_LEFT;
}

void rect(int x, int y, int w, int h, int c)
{
    // Top and bottom
    int i;
    int steps = getRectSteps(w,h);
    for (int i = 0; i < steps/2; i++)
    {
        int rx;
        int ry;
        int ch= '#';
    color(c);
        getRectXY(x, y, w, h, i, &rx, &ry);
        mvprintw(ry,rx,"#");
        getRectXY(x, y, w, h, i + steps/2, &rx, &ry);
        mvprintw(ry,rx,"#");
        refresh();
        delay_output(50);
    }
}

int main()
{
    int x = 30;
    int y = 5;
    int w = 17;
    int h = 5;

    initscr();
    nodelay(stdscr,true);
	//raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    start_color();
        for (int i = 1; i <= 7; ++i)
        {
            init_pair(i, i, COLOR_BLACK);
        }

    char str[] = "HELLO_PDCURSES";
    for (int i = 1; i <= 14; i++)
    {
        color(i);
        int ch = '#';
        mvaddch(y + 2, x + 1 + i, str[i-1]);
        //printw("in main(): i = %2d: This is a test.\n", i);
    }
    refresh();

    curs_set(0);

    int i = 1;
    bool close = false;
    while (!close)
    {
        color(i);
        mvaddch(y+3,x+1+i, '^');
        // Draw one symbol
        int j;
        int steps = getRectSteps(w,h);
        for (int j = 0; j < steps/2 ; j++)
        {
            int rx;
            int ry;
            int ch= '#';
            getRectXY(x, y, w, h, j, &rx, &ry);
            mvprintw(ry,rx,"#");
            getRectXY(x, y, w, h, j + steps/2, &rx, &ry);
            mvprintw(ry,rx,"#");
            refresh();
            delay_output(50);
            int mych=getch();
            if (mych != ERR)
            {
                close = true;
                break;
            }
        }
        mvaddch(y+3,x+1+i, ' ');
        if (++i > 14)
            i = 1;
    }
    getch();
    endwin();
    return 0;
}
