#ifndef FRAC_H
#define FRAC_H

using namespace std;

struct Frac {
    int num;
    int denom;

    Frac() = default;

    Frac(int a)
    {
        num = a;
        denom = 1;
    }
    friend ostream& operator<<(ostream& os, const Frac& a);
};

void FracSimplify (Frac * value);
void FracMultiply (Frac * res, const Frac * a, const Frac * b);
void FracDivide   (Frac * res, const Frac * a, const Frac * b);
void FracAdd      (Frac * res, const Frac * a, const Frac * b);
void FracSubstract(Frac * res, const Frac * a, const Frac * b);
void FracPrint(const Frac * f);

Frac operator+(const Frac &a, const Frac &b);
Frac operator-(const Frac &a, const Frac &b);
Frac operator*(const Frac &a, const Frac &b);
Frac operator/(const Frac &a, const Frac &b);
ostream& operator<<(ostream& os, Frac& a);

#endif // FRAC_H
