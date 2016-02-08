#include <iostream>
#include <cstdlib>
#include <cassert>
#include "frac.h"

using namespace std;

/// @brief Constructor
Frac::Frac(int n, int d)
    :mNum(n),mDen(d)
{
    purify();
}

void Frac::purify()
{
    // Check for a negative denominator
    if (mDen < 0)
    {
        mNum   = - mNum;
        mDen = - mDen;
    }
    // Check for a zero nominator
    if (mNum == 0)
    {
        mDen = 1;
    }
    // Check for a zero denominator
    assert(mDen != 0);

    // Simplify
    int gcd = calc_gcd(abs(mNum),mDen);
    mNum /= gcd;
    mDen /= gcd;
}

Frac Frac::operator+(const Frac &a) const
{
    Frac ret(*this);

    int gcd = calc_gcd(ret.mDen, a.mDen);
    int mult1 = ret.mDen / gcd;
    int mult2 = a.mDen / gcd;

    ret.mNum = ret.mNum * mult2 + a.mNum * mult1;
    ret.mDen = ret.mDen * mult2;

    ret.purify();

    return ret;
}

Frac Frac::operator-(const Frac &a) const
{
    Frac arg2(a);

    arg2.mNum = -arg2.mNum;

    return (*this) + arg2;
}

Frac Frac::operator*(const Frac &a) const
{
    Frac ret(*this);

    ret.mNum = ret.mNum * a.mNum;
    ret.mDen = ret.mDen * a.mDen;

    ret.purify();
    return ret;
}

Frac Frac::operator/(const Frac &a) const
{
    Frac arg2 = a;

    swap(arg2.mNum, arg2.mDen);
    return (*this) * arg2;
}

bool Frac::operator==(const Frac &a) const
{
    if (mNum != a.mNum)
        return false;
    if (mDen != a.mDen)
        return false;
    return true;
}

bool Frac::operator!=(const Frac &a) const
{
    return !(*this == a);
}

bool Frac::operator>(const Frac &a) const
{
    int gcd = calc_gcd(mDen, a.mDen);
    int mult1 = mDen / gcd;
    int mult2 = a.mDen / gcd;

    int arg1_num = mNum * mult2;
    int arg2_num = a.mNum * mult1;

    if (arg1_num > arg2_num)
        return true;

    return false;
}

bool Frac::operator<(const Frac &a) const
{
    if (*this == a)
        return false;

    if (*this > a)
        return false;

    return true;
}

bool Frac::operator>=(const Frac &a) const
{
    if (*this == a)
        return true;

    if (*this > a)
        return true;

    return false;
}

bool Frac::operator<=(const Frac &a) const
{
    if (*this > a)
        return false;

    return true;
}

Frac Frac::operator+=(const Frac &a)
{
    (*this) = (*this) + a;
    return (*this);
}

Frac Frac::operator-=(const Frac &a)
{
    (*this) = (*this) - a;
    return (*this);
}

Frac Frac::operator*=(const Frac &a)
{
    (*this) = (*this) * a;
    return (*this);
}

Frac Frac::operator/=(const Frac &a)
{
    (*this) = (*this) / a;
    return (*this);
}


ostream& operator<<(ostream& os, const Frac& a)
{
    os << a.mNum << '/' << a.mDen;
    return os;
}

Frac operator+(const Frac &a)
{
    return a;
}

Frac operator-(const Frac &a)
{
    Frac ret(a);
    ret.mNum = - ret.mNum;
    return a;
}

Frac operator*(const int &a, const Frac &b)
{
    Frac tmp(a,1);
    return tmp * b;
}

Frac operator/(const int &a, const Frac &b)
{
    Frac tmp(a,1);
    return tmp / b;
}

Frac operator+(const int &a, const Frac &b)
{
    Frac tmp(a,1);
    return tmp + b;
}

Frac operator-(const int &a, const Frac &b)
{
    Frac tmp(a,1);
    return tmp - b;
}

int Frac::getNum(void) const
{
    return mNum;
}

int Frac::getDenom(void) const
{
    return mDen;
}

Frac& Frac::setNum(int a)
{
    mNum = a;
    purify();
    return *this;
}

Frac& Frac::setDenom(int a)
{
    mDen = a;
    purify();
    return *this;
}
/**********************
 * Internal functions *
 **********************/

int Frac::calc_gcd(int a, int b) const
{
    while ((a != 0) && (b != 0))
    {
        if (a >= b)
            a -= b;
        if (b >= a)
            b -= a;
    }

    return a + b;
}

