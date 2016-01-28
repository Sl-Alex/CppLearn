#include <iostream>
#include <cstdlib>
#include "frac.h"

using namespace std;

static int gcd_euclidean(int a, int b);

void FracSimplify(Frac * value)
{
    int gcd = gcd_euclidean(abs(value->num),value->denom);

    value->num /= gcd;
    value->denom /= gcd;
}

void FracMultiply(Frac * res, const Frac * a, const Frac * b)
{
    res->num = a->num * b->num;
    res->denom = a->denom * b->denom;

    FracSimplify(res);
}

void FracDivide(Frac * res, const Frac * a, const Frac * b)
{
    int b_sign = (b->num >= 0)? 1 : -1;

    Frac tmp;
    tmp.num = b->denom*b_sign;
    tmp.denom = abs(b->num);

    FracMultiply(res,a,&tmp);
}

void FracAdd(Frac * res, const Frac * a, const Frac * b)
{
    int gcd = gcd_euclidean(a->denom,b->denom);
    int mult_a = b->denom / gcd;
    int mult_b = a->denom / gcd;

    res->num = a->num * mult_a + b->num * mult_b;
    res->denom = a->denom * mult_a;

    FracSimplify(res);
}

void FracSubstract(Frac * res, const Frac * a, const Frac * b)
{
    Frac tmp;
    tmp.num = -b->num;
    tmp.denom = b->denom;
    FracAdd(res,a,&tmp);
}

void FracPrint(const Frac * f)
{
    cout << f->num << "/" << f->denom;
}

Frac operator+(const Frac &a, const Frac &b)
{
    Frac c;
    FracAdd(&c,&a,&b);
    return c;
}

Frac operator-(const Frac &a, const Frac &b)
{
    Frac c;
    FracSubstract(&c,&a,&b);
    return c;
}

Frac operator*(const Frac &a, const Frac &b)
{
    Frac c;
    FracMultiply(&c,&a,&b);
    return c;
}

Frac operator/(const Frac &a, const Frac &b)
{
    Frac c;
    FracDivide(&c,&a,&b);
    return c;
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
    int a1 = max(a, b);
    int b1 = min(a, b);

    if (b1 == 0) return 1;

    if ((a1 % b1) == 0)
        return b1;

    while (a1 >= b1)
    {
        a1 -= b1;
    }

    if (a1 == 0)
        return 0;

    int res = gcd_euclidean(b1, a1);
    if (res == 0)
        return a1;
    else
        return res;

    return 0;
}

