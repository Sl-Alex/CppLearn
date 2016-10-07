#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "windows.h"
#include <thread>
#include <atomic>

#include "connectionmanager.h"

class ChatServer
{
public:
    ChatServer();
    bool init(void);
    bool start(void);
    void stop(void);
    in_addr getSelfAddress(void) { return selfAddr; }
    void connectTo(std::string address);
    void disconnectFrom(int num);
    void broadcast(std::string data);
    void sendTo(int num, std::string data);
    int getCount(void);
    std::string getAddr(int num);
    ~ChatServer();
private:
    struct in_addr selfAddr;
    struct addrinfo *ownAddr;
    SOCKET ListenSocket;
    std::atomic_bool mStop;
    std::atomic_bool mRunning;

    std::thread serverThread;

    ConnectionManager manager;
};

#endif // CHATSERVER_H
