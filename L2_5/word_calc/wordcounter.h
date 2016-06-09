#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <map>
#include <tr1/unordered_map>

class WordCounter
{
private:
    std::tr1::unordered_map<std::string, int> mMap;

public:

    int addWord(std::string word);
    int count(void) { return mMap.size(); }

    auto begin() -> decltype(mMap.begin())
        { return mMap.begin(); }

    auto end() -> decltype(mMap.end())
        { return mMap.end(); }

    void clear(void)
        { mMap.clear(); }
};

#endif // WORDCOUNTER_H
