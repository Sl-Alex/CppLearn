#include "wordcounter.h"

int WordCounter::addWord(std::string word)
{
    auto it = mMap.find(word);
    if (it != mMap.end())
    {
        it->second++;
        return it->second;
    }
    else
    {
        std::pair<std::string,int> pair(word,1);
        mMap.insert(pair);
        return 1;
    }
}

