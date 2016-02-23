#include <iostream>
#include <cstdlib>
#include <time.h>
#include <curses.h>
#include "game.h"
#include "gamerect.h"

using namespace std;

void select_mode (bool * mode)
{
    clear();
    game_color_set(11);
    mvprintw(10,30, "Choose play mode");
    game_color_set(7);
    mvprintw(12,32, "-> Normal");
    mvprintw(13,35, "Demo");

    int ch = ERR;
    while (ch == ERR)
    {

        ch = getch();
        if ((ch == KEY_UP) || (ch == KEY_DOWN))
        {
            *mode = ! (*mode);
            ch = ERR;
        }
        else if (ch == ERR)
            continue;
        else
            break;
        mvprintw(12,32, "  ");
        mvprintw(13,32, "  ");
        if (*mode)
            mvprintw(13,32, "->");
        else
            mvprintw(12,32, "->");
    }
}

int main()
{
    // Rectangle parameters
    int rect_x = 30;
    int rect_y = 5;
    int rect_w = 17;
    int rect_h = 5;

    // Default values
    int lives = 5;
    int scores = 0;

    // Is game automatic or not
    bool mode_auto = false;

    // Maximum number of scores
    const int scoresmax = 99;

    GameRect * rct = new GameRect();

    // Table parameters
    int table_w = 20;
    int table_x = TERM_WIDTH/2 - table_w/2;

    // Success/Game_over messages
    const char str_succ[] = "SUCCESS!!!";
    const char str_over[] = "GAME  OVER";

    // Initialize random generator
    srand(time(0));

    // Initialize the screen
    initscr();
    nodelay(stdscr,true);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);

	// Initialize palette
	game_color_init();

	// Play mode selection
	select_mode(&mode_auto);

	// Input X coordinate
    clear();
    game_color_set(11);
    mvprintw(10,30, "Enter the X position");
    game_color_set(4);
    mvprintw(11,30, "Default is %i", rect_x);
    game_color_set(7);
    mvprintw(13,32, "-> ");
    rect_x = getInt(rect_x);

    // Input Y coordinate
    clear();
    game_color_set(11);
    mvprintw(10,30, "Enter the Y position");
    game_color_set(4);
    mvprintw(11,30, "Default is %i", rect_y);
    game_color_set(7);
    mvprintw(13,32, "-> ");
    rect_y = getInt(rect_y);

    // Enter width
    clear();
    game_color_set(11);
    mvprintw(10,30, "Enter the width of the rectangle");
    game_color_set(4);
    mvprintw(11,30, "Default is %i", rect_w);
    game_color_set(7);
    mvprintw(13,32, "-> ");
    rect_w = getInt(rect_w);

    // Enter height
    clear();
    game_color_set(11);
    mvprintw(10,30, "Enter the height of the rectangle");
    game_color_set(4);
    mvprintw(11,30, "Default is %i", rect_h);
    game_color_set(7);
    mvprintw(13,32, "-> ");
    rect_h = getInt(rect_h);

    // Output the default text
    clear();
    char str1[] = "PRESS ANY KEY ";
    for (int i = 1; i <= 14; i++)
    {
        game_color_set(i);
        mvaddch(rect_y + rect_h/2, rect_x + i + rect_w/2 - 14/2, str1[i-1]);
    }

    // Prepare the game layout
    game_color_set(13);
    mvprintw(2,2,"L %u", lives);
    mvprintw(2,8,"S %3u", scores);

    // Place bricks on the table
    int cnt = 0;
    while(true)
    {
        int rx = 1 + rand()%78;
        int ry = 1 + rand()%17;

        if ((mvinch(ry,rx) & 0x7F) != ' ')
            continue;

        // exclude stats
        if ((rx < 15) && (ry < 5))
            continue;

        if ((rx >= rect_x) && (rx < rect_x + rect_w + 1) && (ry >= rect_y) && (ry < rect_y+rect_h))
            continue;

        cnt++;
        mvaddch(ry,rx,'*');
        if (cnt >= scoresmax)
            break;
    }

    // Draw all borders
    game_color_set(5);
    for (int i = 0; i < 80; i++)
        mvaddch(0, i, '#');
    for (int i = 0; i < 80; i++)
        mvaddch(TERM_HEIGHT-1, i, '-');
    for (int i = 0; i < TERM_HEIGHT; i++)
        mvaddch(i, 0, '#');
    for (int i = 0; i < TERM_HEIGHT; i++)
        mvaddch(i, 79, '#');
    for (int i = 1; i < 14; i++)
        mvaddch(4, i, '#');
    for (int i = 1; i < 5; i++)
        mvaddch(i, 6, '#');
    for (int i = 1; i < 5; i++)
        mvaddch(i, 14, '#');

    // Draw the rest once
    update_game(&scores,&lives, NULL);
    // Draw the table
    update_table(table_x,table_w);
    // Output everything
    refresh();
    // Wait for the "any" key :)
    while(getch() == ERR);
    // Update the text
    char str2[] = "HELLO_PDCURSES";
    for (int i = 1; i <= 14; i++)
    {
        game_color_set(i);
        mvaddch(rect_y + rect_h/2, rect_x + i + rect_w/2 - 14/2, str2[i-1]);
    }

    // Enter the main loop
    int col = 1;
    rct->setX(rect_x);
    rct->setY(rect_y);
    rct->setWidth(rect_w);
    rct->setHeight(rect_h);
    while ((lives > 0) && (scores < scoresmax))
    {
        // Output pointer to the current color
        mvaddch(rect_y+rect_h/2+1,rect_x + col + rect_w/2 - 14/2, '^');

        // Draw rect
        int steps = rct->stepsCount();
        for (int j = 0; j < steps/2 ; j++)
        {
            int rx;
            int ry;
            rct->setColor(col);
            rct->setChar('#');
            rct->drawStep(j);
            rct->drawStep(j + steps/2);

            // Get user input
            int mych=getch();
            if (mych != ERR)
            {
                if((mych == KEY_LEFT) && (table_x > 0)) table_x--;
                if((mych == KEY_RIGHT) && (table_x + table_w < 80)) table_x++;
                if (mych == 'q')
                {
                    endwin();
                    return 0;
                }
                // Clear the buffer
                while (mych != ERR)
                    mych = getch();
            }


            // Update the ball and the bricks
            int ball_x;
            update_game(&scores, &lives, &ball_x);

            // Automatic play
            if (mode_auto)
            {
                table_x = ball_x - table_w/2;
                if (table_x < 0) table_x = 0;
                if (table_x + table_w >= TERM_WIDTH) table_x = TERM_WIDTH - table_w;
            }

            // Output the table
            update_table(table_x,table_w);

            // Output the stats
            game_color_set(13);
            mvprintw(2,2,"L %u", lives);
            mvprintw(2,8,"S %3u", scores);

            // Break out if there are no more lives
            if (lives == 0)
                break;

            // Update the screen and delay a bit
            refresh();
            delay_output(50);

            // Clear old positions for '#' chars
            rct->setChar(' ');
            rct->drawStep(j);
            rct->drawStep(j + steps / 2);
        }
        // Clear old positions for '^' chars
        mvaddch(rect_y+rect_h/2+1,rect_x + col + rect_w/2 - 14/2, ' ');
        if (++col > 14)
            col = 1;
    }

    // Show the end animation
    if (scores == scoresmax)
        show_end(str_succ);
    else
        show_end(str_over);

    // wait for any key
    nodelay(stdscr,false);
    getch();

    // end
    endwin();
    delete rct;
    return 0;
}
