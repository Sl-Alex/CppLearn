#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

const int TERM_WIDTH = 80;
const int TERM_HEIGHT = 24;

void update_table(int table_x, int table_w);
void update_game(int * scores, int * lives, int * bx);
void show_end(const char * str);

void game_color_init(void);
void game_color_set(int c);

int getRectSteps(int w, int h);
void getRectXY(int x, int y, int w, int h, int step, int * ret_x, int * ret_y);
int getInt(int def);

#endif // GAME_H_INCLUDED
