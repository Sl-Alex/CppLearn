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
private:
    std::vector<ChatConnection*> mConnections;
    std::mutex mAccessMutex;
};

#endif // CONNECTIONMANAGER_H
