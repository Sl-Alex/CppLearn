#include "bigint.h"
#include <algorithm>
#include <cstring>

BigInt::BigInt(int val)
{
    mDigCnt = mGetLength(val);
    mDigits = new int[mDigCnt];

    mDigits[0] = 0;

    unsigned int pos_val = abs(val);

    int i = 0;
    while (pos_val != 0)
    {
        mDigits[i++] = pos_val %10;
        pos_val /= 10;
    }

    mNegative = (val < 0);
}

BigInt::~BigInt()
{
    delete[] mDigits;
}

unsigned int BigInt::mGetLength(int val)
{
    unsigned int pos_val = abs(val);

    unsigned int res = 1;
    while (pos_val >= 10)
    {
        pos_val /= 10;
        res++;
    }
    return res;
}

BigInt::BigInt(const BigInt& val)
{
    mDigCnt = val.mDigCnt;
    mDigits = new int[mDigCnt];
    mNegative = val.mNegative;

    memcpy(mDigits, val.mDigits, mDigCnt*sizeof(int));
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    delete[] mDigits;

    mDigCnt = rhs.mDigCnt;
    mDigits = new int[mDigCnt];
    mNegative = rhs.mNegative;

    memcpy(mDigits, rhs.mDigits, mDigCnt*sizeof(int));

    //assignment operator
    return *this;
}

BigInt BigInt::operator+(const BigInt& rhs) const
{
    // Calculate maximum number of digits required
    unsigned int sz = std::max(mDigCnt, rhs.mDigCnt) + 1;
    bool mAddition = !(mNegative ^ rhs.mNegative);
    bool mSwapped = false;

    BigInt num1;
    BigInt num2;

    BigInt res = *this;

/*
     5  +   10  ///      5 + 10
     5  +  -10  /// - ( 10 -  5 ) (arguments are swapped)
    -5  +   10  ///     10 -  5   (arguments are swapped)
    -5  +  -10  /// - (  5 + 10 )

     5 +  1 ///    5 + 1    ==> same
     5 + -1 ///    5 - 1
    -5 +  1 /// - (5 - 1)
    -5 + -1 /// - (5 + 1)   ==> same
*/

    if (mAddition)
        res.mNegative = mNegative;
    else
    {
        if (compareArrays(mDigits,rhs.mDigits,mDigCnt,rhs.mDigCnt) > 0)
            res.mNegative = mNegative;
        else
        {
            mSwapped = true;
            res.mNegative = rhs.mNegative;
        }
    }

    if (mSwapped)
    {
        num2 = *this;
        num1 = rhs;
    }
    else
    {
        num1 = *this;
        num2 = rhs;
    }

    int ovl = 0;

    // Reserve enough of free memory
    res.mRealloc(sz);

    // Calculate a sum
    for (unsigned int i = 0; i < sz; ++i)
    {
        int tmp;
        if (mAddition)
        {
            tmp = num1.mGetNumber(i) + num2.mGetNumber(i) + ovl;
        }
        else
        {
            tmp = num1.mGetNumber(i) - num2.mGetNumber(i) + ovl;
        }
        if (tmp < 0)
        {
            tmp = 10 + tmp;
            ovl = - 1;
        }
        else
        {
            ovl = tmp / 10;
        }
        res.mDigits[i] = abs(tmp % 10);
    }

    // Update negative value
    // res.mNegative = ((*this).mNegative ^ rhs.mNegative);
    // Reduce
    res.mReduce();

    return res;
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
    BigInt num2(rhs);
    num2.mNegative = ! num2.mNegative;

    return (*this) + num2;
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    int num1cnt = mDigCnt;
    int num2cnt = rhs.mDigCnt;

    BigInt bigtmp(0);
    BigInt sum(0);

    int ovl;
    int i,j;

    // Calculate intermediates
    for (i = 0; i < num2cnt; ++i)
    {
        ovl = 0;
        bigtmp.mRealloc(num1cnt);
        for (j = 0; j < num1cnt; ++j)
        {
            int tmp = mGetNumber(j)*rhs.mGetNumber(i) + ovl;
            bigtmp.mDigits[j] = tmp % 10;
            ovl = tmp / 10;
        }
        if (ovl)
        {
            bigtmp.mRealloc(bigtmp.mDigCnt + 1);
            bigtmp.mDigits[bigtmp.mDigCnt - 1] = ovl;
        }
        for (j = 0; j < i; ++j)
        {
            bigtmp.mAppendRight(0);
        }
        bigtmp.mReduce();
        sum += bigtmp;
        bigtmp = 0;
    }

    // Update negative value
    sum.mNegative = ((*this).mNegative ^ rhs.mNegative);

    // Reduce
    sum.mReduce();

    return sum;
}

BigInt BigInt::operator/(const BigInt& rhs) const
{
    return full_division((*this), rhs, NULL);
}

BigInt BigInt::operator%(const BigInt& rhs) const
{
    BigInt res(0);
    full_division((*this), rhs, &res);
    return res;
}

void BigInt::mRealloc(unsigned int NewCnt)
{
    // Check if it's necessary to reallocate memory
    if (mDigCnt == NewCnt) return;

    int * newNumbers = new int[NewCnt];

    memcpy(newNumbers, mDigits, std::min(NewCnt, mDigCnt)*sizeof(int));

    if (NewCnt > mDigCnt)
        memset(&newNumbers[mDigCnt], 0, (NewCnt - mDigCnt) * sizeof(int));


    mDigCnt = NewCnt;

    // Update the pointer
    delete[] mDigits;
    mDigits = newNumbers;
}

void BigInt::mReduce(void)
{
    int amount = 0;
    int idx = mDigCnt - 1;
    while ((idx > 0) && (mDigits[idx] == 0))
    {
        amount++;
        idx--;
    }
    mRealloc(mDigCnt - amount);
    if ((mDigCnt == 1) && (mDigits[0] == 0))
        mNegative = false;
}

void BigInt::mAppendRight(int val)
{
    ++mDigCnt;
    mRealloc(mDigCnt);

    for (unsigned int i = mDigCnt - 1; i > 0; --i)
    {
        mDigits[i] = mDigits[i-1];
    }
    mDigits[0] = val;
}

int compareArrays(int * arr1, int * arr2, unsigned int sz1, unsigned int sz2)
{
    if (sz1 != sz2)
        return sz1 - sz2;

    unsigned int idx = sz1;
    while((arr1[idx - 1] == arr2[idx - 1]) && (idx > 0))
        --idx;

    if (idx == 0)
        return 0;
    else
        return arr1[idx - 1] - arr2[idx - 1];
}

ostream& operator<<(ostream& os, const BigInt& val)
{
    //BigInt tmp(val);
    if (val.mNegative)
        cout << "-";
    for (unsigned int i = val.mDigCnt; i > 0; --i)
        os << val.mDigits[i - 1];

    return os;
}

BigInt operator-(const BigInt& val)
{
    BigInt res(val);
    res.mNegative = ! res.mNegative;
    return res;
}

BigInt operator+(const BigInt& val)
{
    return val;
}

BigInt full_division(const BigInt& lhs, const BigInt& rhs, BigInt * pRemainder)
{
    BigInt res(0);


    BigInt temp_res(0);
    BigInt temp_next(0);

    unsigned int cur_idx = lhs.mDigCnt;

    // Fill for the very first time
    if (rhs.mDigCnt > lhs.mDigCnt)
    {
        if (pRemainder != NULL)
            *pRemainder = rhs;
        return res;
    }
    for (unsigned int i = 0; i < rhs.mDigCnt; i++)
        temp_next.mAppendRight(lhs.mDigits[--cur_idx]);

    while (true)
    {
        if (compareArrays(temp_next.mDigits, rhs.mDigits, temp_next.mDigCnt, rhs.mDigCnt) < 0)
        {
            res.mAppendRight(0);
            --cur_idx;
            continue;
        }

        // Search for a good digit
        int i;
        BigInt last_res(0);
        for (i = 1; i < 9; ++i)
        {
            temp_next.mReduce();
            temp_res = rhs * i;
            temp_res.mNegative = false;
            if (compareArrays(temp_res.mDigits, temp_next.mDigits, temp_res.mDigCnt, temp_next.mDigCnt) > 0)
                break;
            last_res = temp_res;
        }
        res.mAppendRight(--i);

        // Calculate the difference and add the next digit
        temp_next = temp_next - last_res;
        if (cur_idx > 0)
            temp_next.mAppendRight(lhs.mDigits[--cur_idx]);
        else
            break;
    }

    if (pRemainder != NULL)
        *pRemainder = temp_next;

    res.mReduce();
    res.mNegative = lhs.mNegative ^ rhs.mNegative;

    return res;
}

BigInt BigInt::operator+=(const BigInt &rhs)
{
    *this = (*this) + rhs;
    return (*this);
}

BigInt BigInt::operator-=(const BigInt &rhs)
{
    *this = (*this) - rhs;
    return (*this);
}

BigInt BigInt::operator*=(const BigInt &rhs)
{
    *this = (*this) * rhs;
    return (*this);
}

BigInt BigInt::operator/=(const BigInt &rhs)
{
    *this = (*this) / rhs;
    return (*this);
}

BigInt operator+(const int &lhs, const BigInt &rhs)
{
    BigInt tmp(lhs);
    return tmp + rhs;
}

BigInt operator-(const int &lhs, const BigInt &rhs)
{
    BigInt tmp(lhs);
    return tmp - rhs;
}

BigInt operator*(const int &lhs, const BigInt &rhs)
{
    BigInt tmp(lhs);
    return tmp * rhs;
}

BigInt operator/(const int &lhs, const BigInt &rhs)
{
    BigInt tmp(lhs);
    return tmp / rhs;
}

bool BigInt::isConvertable(ConvType c)
{
    bool isPossible = false;
    switch(c){
        case CONV_CHAR:
            break;
        case CONV_UCHAR:
            break;
        case CONV_SHORT:
            break;
        case CONV_USHORT:
            break;
        case CONV_INT:
            break;
        case CONV_UINT:
            break;
        case CONV_LONG:
            break;
        case CONV_ULONG:
            break;
    }
    return isPossible;
}

bool BigInt::operator==(const BigInt &rhs) const
{
    if (mNegative != rhs.mNegative) return false;
    if (compareArrays(mDigits,rhs.mDigits,mDigCnt,rhs.mDigCnt) != 0)
        return false;

    return true;
}

bool BigInt::operator!=(const BigInt &rhs) const
{
    return !((*this) == rhs);
}

bool BigInt::operator> (const BigInt &rhs) const
{
    if (mNegative == false)
    {
        if (rhs.mNegative)
            return true;
        return (compareArrays(mDigits,rhs.mDigits,mDigCnt,rhs.mDigCnt) > 0);
    }
    if (rhs.mNegative == false)
            return false;
    return (compareArrays(mDigits,rhs.mDigits,mDigCnt,rhs.mDigCnt) < 0);
}

bool BigInt::operator< (const BigInt &rhs) const
{
    if ((*this) == rhs) return false;
    if ((*this) > rhs) return false;
    return true;
}

bool BigInt::operator>=(const BigInt &rhs) const
{
    return !((*this) < rhs);
}

bool BigInt::operator<=(const BigInt &rhs) const
{
    return !((*this) > rhs);
}

BigInt& BigInt::operator++()
{
    *this = (*this) + 1;
    return *this;
}

BigInt BigInt::operator++(int)
{
    BigInt tmp(*this);
    *this = (*this) + 1;
    return tmp;
}

BigInt& BigInt::operator--()
{
    *this = (*this) - 1;
    return *this;
}

BigInt BigInt::operator--(int)
{
    BigInt tmp(*this);
    *this = (*this) - 1;
    return tmp;
}

int BigInt::mGetNumber(unsigned int idx) const
{
    if (idx < mDigCnt)
        return mDigits[idx];
    return 0;
}
