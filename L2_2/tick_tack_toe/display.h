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

    int ask(const char * message, const char ** options, int numOptions, int start);
};

#endif // DISPLAY_H
