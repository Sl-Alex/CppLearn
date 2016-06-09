#ifndef TOTALCOUNTER_H
#define TOTALCOUNTER_H


class TotalCounter
{
public:
    TotalCounter()
        :mCnt(0){}

    int add(int words) { mCnt += words; return mCnt; }
    void clear(void) { mCnt = 0; }
    int count(void) { return mCnt; }

private:
    int mCnt;
};

#endif // TOTALCOUNTER_H
