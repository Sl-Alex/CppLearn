#include <iostream>
#include "bigint.h"

using namespace std;

int main()
{
    BigInt a(316);
    BigInt b(12);
    BigInt c(100);

    BigInt d(2);

    c = a * b;

    cout << "c = " << c << endl;

    for (int i = 1; i < 200; ++i)
    {
        c *= 2;
        cout << "c(" << i << ") = " << c << endl;
    }
    return 0;
}
