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

void ConnectionManager::sendTo(int num, std::string data)
{
    ChatConnection * pConnection;
    cleanup();
    std::lock_guard<std::mutex> lock(mAccessMutex);
    pConnection = mConnections.at(num);
    pConnection->sendMessage(std::move(data));
}

void ConnectionManager::disconnect(int num)
{
    ChatConnection * pConnection;
    cleanup();
    std::lock_guard<std::mutex> lock(mAccessMutex);
    pConnection = mConnections.at(num);
    pConnection->stop();
    delete pConnection;
    mConnections.erase(mConnections.begin() + num);
}

std::string ConnectionManager::getAddress(int num)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);
    if (num < 0) return std::string("");
    if (num > mConnections.size() - 1) return std::string("");

    return std::move(mConnections.at(num)->getAddress());
}
