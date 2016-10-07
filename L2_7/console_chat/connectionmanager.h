#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <vector>
#include <mutex>
#include "chatconnection.h"

class ConnectionManager
{
public:
    ConnectionManager();
    void addConnection(ChatConnection * connection);
    void cleanup(void);
    void clear(void);
    void sendTo(int num, std::string data);
    int getCount(void) {return mConnections.size(); }
    std::string getAddress(int num);
    void disconnect(int num);
private:
    std::vector<ChatConnection*> mConnections;
    std::mutex mAccessMutex;
};

#endif // CONNECTIONMANAGER_H
