#ifndef STRINGQUEUE_H
#define STRINGQUEUE_H

#include <string>
#include <queue>
#include <mutex>

class StringQueue
{
public:
    StringQueue();

    void push(std::string data);
    std::string pop(void);
    int size(void);
    bool empty(void);

private:
    std::queue<std::string> mStrings;
    std::mutex mAccessMutex;
};

#endif // STRINGQUEUE_H
