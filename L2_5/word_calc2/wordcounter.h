#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <map>

#include "stringsplitter.h"

class WordCounter
{
private:
    std::map<std::string, int> mMap;

public:

    void start(void)
    {
        clear();
        splitter.start();
    }

    void addBlock(const std::string block)
    {
        std::vector<std::string> words;
        splitter.parseBlock(block, words);
        for (auto it = words.begin(); it != words.end(); ++it)
        {
            ++mMap[*it];
        }

    }

    void finish(void)
    {
        if (!splitter.getRemainder().empty())
            ++mMap[splitter.getRemainder()];
    }

    int count(void) { return mMap.size(); }

    auto begin() -> decltype(mMap.begin())
        { return mMap.begin(); }

    auto end() -> decltype(mMap.end())
        { return mMap.end(); }

    void clear(void)
        { mMap.clear(); }
private:
    StringSplitter splitter;
};

#endif // WORDCOUNTER_H
