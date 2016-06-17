#ifndef TOTALCOUNTER_H
#define TOTALCOUNTER_H


class TotalCounter
{
public:
    TotalCounter()
        :mCnt(0){}

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
            ++mCnt;
        }

    }

    void finish(void)
    {
        if (!splitter.getRemainder().empty())
            ++mCnt;
    }

    void clear(void) { mCnt = 0; }
    int count(void) { return mCnt; }

private:
    int mCnt;
    StringSplitter splitter;
};

#endif // TOTALCOUNTER_H
