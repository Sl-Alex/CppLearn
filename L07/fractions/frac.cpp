#include <iostream>
#include <cstdlib>
#include <cassert>
#include "frac.h"

using namespace std;

static int gcd_euclidean(int a, int b);

void FracPurify(Frac & value)
{
    // Check for a negative denominator
    if (value.denom < 0)
    {
        value.num   = - value.num;
        value.denom = - value.denom;
    }
    // Check for a zero nominator
    if (value.num == 0)
    {
        value.denom = 1;
    }
    // Check for a zero denominator
    assert(value.denom != 0);

    // Simplify
    int gcd = gcd_euclidean(abs(value.num),value.denom);
    value.num /= gcd;
    value.denom /= gcd;
}

Frac FracMultiply(Frac a, Frac b)
{
    Frac res;
    res.num = a.num * b.num;
    res.denom = a.denom * b.denom;

    FracPurify(res);
    return res;
}

Frac FracDivide(Frac a, Frac b)
{
    swap(b.num, b.denom);

    return FracMultiply(a,b);
}

Frac FracAdd(Frac a, Frac b)
{
    Frac res;

    FracPurify(a);
    FracPurify(b);

    int gcd = gcd_euclidean(a.denom, b.denom);
    int mult_a = b.denom / gcd;
    int mult_b = a.denom / gcd;

    res.num = a.num * mult_a + b.num * mult_b;
    res.denom = a.denom * mult_a;

    FracPurify(res);
    return res;
}

Frac FracSubstract(Frac a, Frac b)
{
    Frac tmp;
    b.num = -b.num;
    return FracAdd(a,b);
}

void FracPrint(const Frac * f)
{
    cout << f->num << "/" << f->denom;
}

Frac operator+(const Frac &a, const Frac &b)
{
    return FracAdd(a,b);
}

Frac operator-(const Frac &a, const Frac &b)
{
    return FracSubstract(a,b);
}

Frac operator*(const Frac &a, const Frac &b)
{
    return FracMultiply(a,b);
}

Frac operator/(const Frac &a, const Frac &b)
{
    return FracDivide(a,b);
}

bool operator==(const Frac &a, const Frac &b)
{
    Frac a1 = a;
    Frac b1 = b;
    FracPurify(a1);
    FracPurify(b1);
    if (a1.num != b1.num)
        return false;
    if (a1.denom != b1.denom)
        return false;
    return true;
}

ostream& operator<<(ostream& os, Frac& a)
{
    os << a.num << '/' << a.denom;
    return os;
}
/**********************
 * Internal functions *
 **********************/

static int gcd_euclidean(int a, int b)
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

