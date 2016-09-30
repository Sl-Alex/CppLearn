#include "connectionmanager.h"

ConnectionManager::ConnectionManager()
{

}

void ConnectionManager::addConnection(ChatConnection * connection)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);

    mConnections.emplace_back(connection);
}

void ConnectionManager::cleanup(void)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);

    auto it = mConnections.begin();
    while (it != mConnections.end())
    {
        // Erase only "non-running" iterators
        if ((*it)->isRunning() == false)
        {
            delete *it;
            mConnections.erase(it);

        }
        else
            it++;
    }
}

void ConnectionManager::clear(void)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);

    auto it = mConnections.begin();
    while (it != mConnections.end())
    {
        delete *it;
        mConnections.erase(it);
    }

}
