#ifndef FRAC_H
#define FRAC_H

using namespace std;

struct Frac {
    int num;
    int denom;

    Frac(int n = 0, int d = 1)
    {
        num = n;
        denom = d;
    }
    Frac(const Frac &f)
    {
        num = f.num;
        denom = f.denom;
    }

    friend ostream& operator<<(ostream& os, const Frac& a);
};

void FracSimplify (Frac * value);
Frac FracMultiply (Frac a, Frac b);
Frac FracDivide   (Frac a, Frac b);
Frac FracAdd      (Frac a, Frac b);
Frac FracSubstract(Frac a, Frac b);
void FracPrint(const Frac * f);

Frac operator+(const Frac &a, const Frac &b);
Frac operator-(const Frac &a, const Frac &b);
Frac operator*(const Frac &a, const Frac &b);
Frac operator/(const Frac &a, const Frac &b);
bool operator==(const Frac &a, const Frac &b);
ostream& operator<<(ostream& os, Frac& a);

#endif // FRAC_H
