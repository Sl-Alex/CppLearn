#include <curses.h>
#include <cstdlib>
#include "game.h"

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

void update_table(int table_x, int table_w)
{
    color_set(5);

    if (table_x > 0)
        mvaddch(TERM_HEIGHT - 1, table_x-1, '-');
    if (table_x + table_w < TERM_WIDTH)
        mvaddch(TERM_HEIGHT - 1, table_x+table_w, '-');

    color_set(7);
    mvaddch(TERM_HEIGHT - 1,table_x,'[');
    mvaddch(TERM_HEIGHT - 1,table_x + table_w - 1,']');
    for (int k = table_x + 1; k < table_x+table_w - 1; k++)
        mvaddch(TERM_HEIGHT - 1,k,205);
}

void color_set(int c)
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

void color_init(void)
{
    start_color();
    for (int i = 1; i <= 7; ++i)
        init_pair(i, i, COLOR_BLACK);
}

int getInt(int def)
{
    int ret = 0;
    int ch = ERR;
    while(ch == ERR)
    {
        ch = getch();
        if (ch == ERR)
            continue;
        if (abs(ch - '0') < 10)
        {
            ret*=10;
            ret += (ch - '0');
            addch(ch);
            ch = ERR;
        }
    }
    if (ret == 0)
        ret = def;

    return ret;
}

int getRectSteps(int w, int h)
{
    return 2*w + 2*h - 2;
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

void rect(int x, int y, int w, int h, int c, int ch)
{
    int steps = getRectSteps(w,h);
    color_set(c);
    for (int i = 0; i < steps; i++)
    {
        int rx;
        int ry;
        getRectXY(x, y, w, h, i, &rx, &ry);
        mvaddch(ry,rx,ch);
        getRectXY(x, y, w, h, i + steps/2, &rx, &ry);
        mvaddch(ry,rx,ch);
    }
}

void show_end(const char * str)
{
    int w;

    const int SZ = 16;

    for (w = 1; w < SZ-1; w+=2)
    {
        rect(TERM_WIDTH/2-SZ/2+6-w/2, 12, w, 5, 14, '#');
        if (w >= 5)
        {
            color_set(6 + (w/2));
            mvaddch(14, TERM_WIDTH/2-SZ/2+8-w/2, str[6 - (w/2)]);
            color_set(6 + (w/2));
            mvaddch(14, TERM_WIDTH/2-SZ/2+5+w/2, str[3 + (w/2)]);
        }
        refresh();
        delay_output(30);
        rect(TERM_WIDTH/2-SZ/2+6-w/2,12,w,5,7,' ');
    }
    rect(TERM_WIDTH/2-SZ/2+6-w/2,12,w,5,14,'#');
    refresh();
}

void update_game(int * scores, int * lives, int * bx)
{
    static int ball_x = TERM_WIDTH/2;
    static int ball_y = TERM_HEIGHT-3;
    static bool ball_dir_x = true;
    static bool ball_dir_y = true;

    static int i = 0;
    if (bx != NULL)
        *bx = ball_x;
    if (i-- > 0) return;
    i = 1;

    int bch_l = mvinch(ball_y,ball_x-1) & 0x7F;
    int bch_r = mvinch(ball_y,ball_x+1) & 0x7F;
    int bch_t = mvinch(ball_y-1,ball_x) & 0x7F;
    int bch_b = mvinch(ball_y+1,ball_x) & 0x7F;
    int bch_lt = mvinch(ball_y-1,ball_x-1) & 0x7F;
    int bch_rt = mvinch(ball_y-1,ball_x+1) & 0x7F;
    int bch_lb = mvinch(ball_y+1,ball_x-1) & 0x7F;
    int bch_rb = mvinch(ball_y+1,ball_x+1) & 0x7F;

    mvaddch(ball_y,ball_x,' ');

    color_set(7);

    mvaddch(ball_y,ball_x,' ');

    int new_x = ball_x;
    int new_y = ball_y;

    bool hit = false;

    if (ball_dir_x)
    {
        if (bch_r == '*')
        {
            (*scores)++;
            mvaddch(ball_y, ball_x+1, ' ');
        }
        if (bch_r == ' ')
        {
                new_x = ball_x + 1;
        }
        else
        {
            hit = true;
            ball_dir_x = ! ball_dir_x;
        }
    }
    else
    {
        if (bch_l == '*')
        {
            (*scores)++;
            mvaddch(ball_y, ball_x-1, ' ');
        }
        if (bch_l == ' ')
        {
                new_x = ball_x - 1;
        }
        else
        {
            hit = true;
            ball_dir_x = ! ball_dir_x;
        }
    }
    if (ball_dir_y)
    {
        if (bch_b == '*')
        {
            (*scores)++;
            mvaddch(ball_y+1, ball_x, ' ');
        }
        if (bch_b == '-')
        {
            (*lives)--;
        }
        if (bch_b == ' ')
        {
            new_y = ball_y + 1;
        }
        else
        {
            hit = true;
            ball_dir_y = ! ball_dir_y;
        }
    }
    else
    {
        if (bch_t == '*')
        {
            (*scores)++;
            mvaddch(ball_y-1, ball_x, ' ');
        }
        if (bch_t == ' ')
        {
            new_y = ball_y - 1;
        }
        else
        {
            hit = true;
            ball_dir_y = ! ball_dir_y;
        }
    }

    int inv = 0;
    // to right-bottom
    if (!hit)
    {
        if (ball_dir_x && ball_dir_y)
        {
            if (bch_rb == '*')
            {
                (*scores)++;
                mvaddch(ball_y+1, ball_x+1, ' ');
            }
            if (bch_rb != ' ')
            {
                inv = 1;
                ball_dir_x = !ball_dir_x;
                ball_dir_y = !ball_dir_y;
            }
        }
        // to left-bottom
        else if ((!ball_dir_x) && ball_dir_y)
        {
            if (bch_lb == '*')
            {
                (*scores)++;
                mvaddch(ball_y+1, ball_x-1, ' ');
            }
            if (bch_lb != ' ')
            {
                inv = 1;
                ball_dir_x = !ball_dir_x;
                ball_dir_y = !ball_dir_y;
            }
        }
        // to left-top
        else if ((!ball_dir_x) && (!ball_dir_y))
        {
            if (bch_lt == '*')
            {
                (*scores)++;
                mvaddch(ball_y-1, ball_x-1, ' ');
            }
            if (bch_lt != ' ')
            {
                inv = 1;
                ball_dir_x = !ball_dir_x;
                ball_dir_y = !ball_dir_y;
            }
        }
        // to right-top
        else
        {
            if (bch_rt == '*')
            {
                (*scores)++;
                mvaddch(ball_y-1, ball_x+1, ' ');
            }
            if (bch_rt != ' ')
            {
                inv = 1;
                ball_dir_x = !ball_dir_x;
                ball_dir_y = !ball_dir_y;
            }
        }
    }

    if (inv == 0)
    {
        ball_x = new_x;
        ball_y = new_y;
    }

    mvaddch(ball_y,ball_x,'O');
}
