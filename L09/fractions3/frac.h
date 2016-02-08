#ifndef FRAC_H
#define FRAC_H

#include <iostream>
using namespace std;

struct Frac {

    public:

        Frac(int n = 0, int d = 1);

        int getNum(void) const;
        int getDenom(void) const;
        Frac& setNum(int);
        Frac& setDenom(int);

        Frac operator-(const Frac &a) const;
        Frac operator+(const Frac &a) const;
        Frac operator*(const Frac &a) const;
        Frac operator/(const Frac &a) const;
        bool operator==(const Frac &a) const;
        bool operator!=(const Frac &a) const;
        bool operator>(const Frac &a) const;
        bool operator<(const Frac &a) const;
        bool operator>=(const Frac &a) const;
        bool operator<=(const Frac &a) const;

        Frac operator+=(const Frac &a);
        Frac operator-=(const Frac &a);
        Frac operator*=(const Frac &a);
        Frac operator/=(const Frac &a);

        friend ostream& operator<<(ostream& os, const Frac & a);

        friend Frac operator+(const Frac &a);
        friend Frac operator-(const Frac &a);

        friend Frac operator*(const int &a, const Frac &b);
        friend Frac operator/(const int &a, const Frac &b);
        friend Frac operator+(const int &a, const Frac &b);
        friend Frac operator-(const int &a, const Frac &b);

    private:

        int mNum;
        int mDen;

        void purify(void);
        int calc_gcd(int a, int b) const;
};

#endif // FRAC_H
