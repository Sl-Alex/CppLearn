#include <iostream>
#include <vector>
#include <string>
#include "win_curses.h"

#include "chatserver.h"

#define LISTEN_PORT 20000

#define TERM_WIDTH  80
#define TERM_HEIGHT 24

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

    int key;
    std::string str;
    setColor(2);
    for (int x = 0; x < TERM_WIDTH; ++x)
    {
        mvaddch(0,x,'#');
        mvaddch(TERM_HEIGHT - 1,x,'#');
    }
    for (int x = 0; x < TERM_WIDTH - 18; ++x)
    {
        mvaddch(2,x,'#');
        mvaddch(TERM_HEIGHT - 3,x,'#');
    }
    for (int y = 0; y < TERM_HEIGHT; ++y)
    {
        mvaddch(y,0,'#');
        mvaddch(y,TERM_WIDTH - 1,'#');
        mvaddch(y,TERM_WIDTH - 19,'#');
    }
    setColor(6);
    //mvprintw(2,TERM_WIDTH - 17, "192.168.169.170");
    int selNum = -1;
    std::string selAddr = "";
    for (int x = 1; x < TERM_WIDTH - 19; ++x)
    {
        mvaddch(1,x,' ');
    }
    mvprintw(1,1,"Enter \":c192.168.0.100\" to connect to 192.168.0.100");
    do
    {
        int connections = server.getCount();
        for (int i = 0; i < TERM_HEIGHT - 3; ++i)
        {
            if (i < connections)
                mvprintw(2 + i,TERM_WIDTH - 17, server.getAddr(i).c_str());
            else
                mvprintw(2 + i,TERM_WIDTH - 17, "               ");
            if (i == selNum)
                mvprintw(2 + i,TERM_WIDTH - 18, ">");
            else
                mvprintw(2 + i,TERM_WIDTH - 18, " ");
        }

        key = getch();
        if (key == 'b')
        {
            server.broadcast("TEST");
        }
        if (key == 10) // RETURN
        {
            if (str[0] == ':')
            {
                switch (str[1])
                {
                    case 'c':
                        {
                            std::string address = str.substr(2);
                            server.connectTo(address);
                            selNum = server.getCount() - 1;
                            selAddr = address;
                            for (int x = 1; x < TERM_WIDTH - 19; ++x)
                            {
                                mvaddch(1,x,' ');
                            }
                            mvprintw(1,1,"Connected to ");
                            mvprintw(1,14,selAddr.c_str());
                        }
                        break;
                    case 'd':
                        {
                            int num;
                            num = std::stoi(str.substr(2));
                            selAddr = server.getAddr(num);
                            server.disconnectFrom(num);
                            for (int x = 1; x < TERM_WIDTH - 19; ++x)
                            {
                                mvaddch(1,x,' ');
                            }
                            mvprintw(1,1,"Disconnected from ");
                            mvprintw(1,19,selAddr.c_str());
                            selNum = server.getCount() - 1;
                            selAddr = server.getAddr(selNum);
                        }
                        break;
                    case 's':
                        selNum = std::stoi(str.substr(2));
                        selAddr = server.getAddr(selNum);
                        for (int x = 1; x < TERM_WIDTH - 19; ++x)
                        {
                            mvaddch(1,x,' ');
                        }
                        mvprintw(1,1,"Selected");
                        break;
                    default:
                        for (int x = 1; x < TERM_WIDTH - 19; ++x)
                        {
                            mvaddch(1,x,' ');
                        }
                        mvprintw(1,1,"Unknown command");
                }
            }
            else
            {
                for (int x = 1; x < TERM_WIDTH - 19; ++x)
                {
                    mvaddch(1,x,' ');
                }
                mvprintw(1,1,"String sent");
                server.sendTo(selNum, str);
            }
            str = "";
            for (int x = 1; x < TERM_WIDTH - 19; ++x)
            {
                mvaddch(TERM_HEIGHT - 2,x,' ');
            }
            continue;
        }
//        if (key != ERR)
//            std::cout << "C = " << (int) key << std::endl;
        if (key == ERR)
            continue;

        char app[2];
        app[1] = 0;
        app[0] = key;
        str.append(app);

        mvprintw(TERM_HEIGHT - 2, 1, str.c_str());

    } while (key != 0x1B);

    server.stop();

    mvprintw(1, 1, "Done");

    refresh();

    return 0;
}
