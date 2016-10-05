#include "stringqueue.h"

StringQueue::StringQueue()
{

}

void StringQueue::push(std::string data)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);
    mStrings.push(data);
}

std::string StringQueue::pop(void)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);

    std::string data;
    data = mStrings.front();
    mStrings.pop();
    return std::move(data);
}

int StringQueue::size(void)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);
    return mStrings.size();
}

bool StringQueue::empty(void)
{
    std::lock_guard<std::mutex> lock(mAccessMutex);
    return mStrings.empty();
}
