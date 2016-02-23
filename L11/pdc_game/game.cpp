#include <curses.h>
#include <cstdlib>
#include "game.h"
#include "gamerect.h"

void update_table(int table_x, int table_w)
{
    game_color_set(5);

    if (table_x > 0)
        mvaddch(TERM_HEIGHT - 1, table_x-1, '-');
    if (table_x + table_w < TERM_WIDTH)
        mvaddch(TERM_HEIGHT - 1, table_x+table_w, '-');

    game_color_set(7);
    mvaddch(TERM_HEIGHT - 1,table_x,'[');
    mvaddch(TERM_HEIGHT - 1,table_x + table_w - 1,']');
    for (int k = table_x + 1; k < table_x+table_w - 1; k++)
        mvaddch(TERM_HEIGHT - 1,k,'=');
}

void game_color_set(int c)
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

void game_color_init(void)
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

void show_end(const char * str)
{
    int w;

    const int SZ = 16;

    GameRect * rct = new GameRect();

    rct->setColor(14);
    rct->setY(12);
    rct->setHeight(5);
    for (w = 1; w < SZ-1; w+=2)
    {
        rct->setX(TERM_WIDTH/2-SZ/2+6-w/2);
        rct->setWidth(w);
        rct->setChar('#');
        rct->drawRect();
        if (w >= 5)
        {
            game_color_set(6 + (w/2));
            mvaddch(14, TERM_WIDTH/2-SZ/2+8-w/2, str[6 - (w/2)]);
            game_color_set(6 + (w/2));
            mvaddch(14, TERM_WIDTH/2-SZ/2+5+w/2, str[3 + (w/2)]);
        }
        refresh();
        delay_output(30);
        rct->setChar(' ');
        rct->drawRect();
    }
    rct->setX(TERM_WIDTH/2-SZ/2+6-w/2);
    rct->setWidth(w);
    rct->setChar('#');
    rct->drawRect();
    refresh();
    delete rct;
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

    game_color_set(7);

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
