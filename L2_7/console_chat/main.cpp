#include <iostream>
#include <vector>
#include <string>
#include "win_curses.h"

#include "chatserver.h"

#define LISTEN_PORT 20000

void setColor(int col)
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

int main(int argc, char *argv[])
{
    ChatServer server;

    std::cout << "Simple console chat. Allows any incoming connection, one connection per IP." << std::endl;
    std::cout << "Connection can be initiated either by you or by remote IP." << std::endl;
    std::cout << "Special commands:" << std::endl;
    std::cout << "  -c 192.168.1.100 connects to the defined IP address." << std::endl;
    std::cout << "  -d 192.168.1.100 disconnects from the defined IP." << std::endl;
    std::cout << "  -b 192.168.1.100 disconnects and blocks further connections to the defined IP" << std::endl;

    server.init();
    server.start();
    server.connectTo("127.0.0.1");

    initscr();
    nodelay(stdscr,true);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    start_color();
    for (int i = 1; i <= 7; ++i)
        init_pair(i, i, COLOR_BLACK);

    setColor(10);
    mvprintw(23, 17, "TEST");
    refresh();

    char key;
    do
    {
        key = getch();
        if (key == 'b')
        {
            server.broadcast("TEST");
        }
    } while (key != 0x1B);

    server.stop();

    mvprintw(1, 1, "Done");

    refresh();

    return 0;
}
