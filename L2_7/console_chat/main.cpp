#include <iostream>
#include <vector>
#include <string>
#include "win_curses.h"

#include <winsock2.h>
#include "windows.h"
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
    WSAData wsaData;

    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
        return 255;
    }

    std::cout << "Simple console chat. Allows any incoming connection, one connection per IP." << std::endl;
    std::cout << "Connection can be initiated either by you or by remote IP." << std::endl;
    std::cout << "Special commands:" << std::endl;
    std::cout << "  -c 192.168.1.100 connects to the defined IP address." << std::endl;
    std::cout << "  -d 192.168.1.100 disconnects from the defined IP." << std::endl;
    std::cout << "  -b 192.168.1.100 disconnects and blocks further connections to the defined IP" << std::endl;

    server.init();
    server.start();
    volatile bool test = true;
    //Sleep(10000);
    while(test)
    {

    }
    server.stop();

    WSACleanup();
    return 0;
#if 0
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

    WSACleanup();
    return 0;
#endif
}
