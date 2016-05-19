#ifndef DISPLAY_H
#define DISPLAY_H


class Display
{
public:
    const int TERM_WIDTH = 80;
    const int TERM_HEIGHT = 25;
    Display();
    void setColor(int col);
    void printMessage(const char * pStr);
    int getValue(void);
};

#endif // DISPLAY_H
