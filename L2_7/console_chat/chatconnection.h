#ifndef CHATCONNECTION_H
#define CHATCONNECTION_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "windows.h"
#include <thread>
#include <atomic>

#include "stringqueue.h"

class ChatConnection
{
public:
    ChatConnection();
    ~ChatConnection();
    void start(SOCKET newSocket);
    void stop(void);
    bool isRunning(void) {return mRunning;}
    void sendMessage(std::string data);
private:
    std::atomic_bool mRunning;
    std::atomic_bool mStop;
    std::thread mThread;
    SOCKET mSocket;

    StringQueue mSendQueue;
    StringQueue mReceiveQueue;
};

#endif // CHATCONNECTION_H
