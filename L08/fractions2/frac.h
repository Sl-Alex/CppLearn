#ifndef FRAC_H
#define FRAC_H

#include <iostream>
using namespace std;

struct Frac {
    public:

        int num;
        int denom;

        Frac(int n = 0, int d = 1);

        friend ostream& operator<<(ostream& os, const Frac & a);

        Frac operator-(const Frac &a);
        Frac operator+(const Frac &a);
        Frac operator*(const Frac &a);
        Frac operator/(const Frac &a);
        bool operator==(const Frac &a);
        bool operator!=(const Frac &a);
        bool operator>(const Frac &a);
        bool operator<(const Frac &a);
        bool operator>=(const Frac &a);
        bool operator<=(const Frac &a);

    private:
        void purify(void);
        int calc_gcd(int a, int b);
};


#endif // FRAC_H
