#include <iostream>
#include <cstdlib>
#include <cassert>
#include "frac.h"

using namespace std;

/// @brief Constructor
Frac::Frac(int n, int d)
    :num(n),denom(d)
{

}

void Frac::purify()
{
    // Check for a negative denominator
    if (this->denom < 0)
    {
        this->num   = - this->num;
        this->denom = - this->denom;
    }
    // Check for a zero nominator
    if (this->num == 0)
    {
        this->denom = 1;
    }
    // Check for a zero denominator
    assert(this->denom != 0);

    // Simplify
    int gcd = calc_gcd(abs(this->num),this->denom);
    this->num /= gcd;
    this->denom /= gcd;
}

Frac Frac::operator+(const Frac &a)
{
    Frac arg1 = *this;
    Frac arg2 = a;

    arg1.purify();
    arg2.purify();

    int gcd = calc_gcd(arg1.denom, arg2.denom);
    int mult1 = arg1.denom / gcd;
    int mult2 = arg2.denom / gcd;

    arg1.num = arg1.num * mult2 + arg2.num * mult1;
    arg1.denom = arg1.denom * mult2;

    arg1.purify();

    return arg1;
}

Frac Frac::operator-(const Frac &a)
{
    Frac arg1 = *this;
    Frac arg2 = a;

    arg2.num = -arg2.num;

    return arg1 + arg2;
}

Frac Frac::operator*(const Frac &a)
{
    Frac arg1 = *this;

    arg1.num = arg1.num * a.num;
    arg1.denom = arg1.denom * a.denom;

    arg1.purify();
    return arg1;
}

Frac Frac::operator/(const Frac &a)
{
    Frac arg1 = *this;
    Frac arg2 = a;

    swap(arg2.num, arg2.denom);
    return arg1 * arg2;
}

bool Frac::operator==(const Frac &a)
{
    Frac arg1 = *this;
    Frac arg2 = a;

    arg1.purify();
    arg2.purify();

    if (arg1.num != arg2.num)
        return false;
    if (arg1.denom != arg2.denom)
        return false;
    return true;
}

bool Frac::operator!=(const Frac &a)
{
    return !(*this == a);
}

/// @TODO
bool Frac::operator>(const Frac &a)
{
    return false;
}

/// @TODO
bool Frac::operator<(const Frac &a)
{
    return false;
}

ostream& operator<<(ostream& os, const Frac& a)
{
    os << a.num << '/' << a.denom;
    return os;
}
/**********************
 * Internal functions *
 **********************/

int Frac::calc_gcd(int a, int b)
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

