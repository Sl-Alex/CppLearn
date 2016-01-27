#include <iostream>
#include "frac.h"

using namespace std;

int main()
{
    cout << "This is a fractions example." << endl;
    cout << "Please enter 4 integer numbers." << endl;
    cout << "They will be assigned to the numerators and denominators" << endl;
    cout << "of two fractions in the following manner:" << endl;
    cout << "  f1 = number1 / number2" << endl;
    cout << "  f2 = number3 / number4" << endl;
    cout << "Numbers 2 and 4 should be positive, otherwise" << endl;
    cout << "calculation will fail." << endl;

    Frac d1;
    Frac d2;

    cin >> d1.num;
    cin >> d1.denom;
    cin >> d2.num;
    cin >> d2.denom;

    Frac tmp1, tmp2, tmp3, tmp4, tmp_mult, res;

    //    _____res______
    //   |              |
    //   |           __tmp3__
    //   |          |        |
    //  tmp1       tmp2      |
    // |    |     |    |     |
    // d1 * d2 - (d1 - d2) / d1;
    FracMultiply(&tmp1,&d1,&d2);
    FracSubstract(&tmp2,&d1,&d2);
    FracDivide(&tmp3,&tmp2,&d1);
    FracSubstract(&res,&tmp1,&tmp3);

    cout << endl;
    cout << "Formula #1: res = f1 * f2 - (f1 - f2) / f1" << endl;
    cout << "Result #1 = " << res.num << "/" << res.denom << endl;
    cout << endl;

    //    _____res________
    //   |                |
    //   |             __tmp4__
    //   |            |        |
    //   |          _tmp3      |
    //   |         |     |     |
    //  tmp1      tmp2   |     |
    // |    |     | |    |     |
    // d1 * d2 - (2*d1 - d2) / d1;
    FracMultiply(&tmp1,&d1,&d2);
    tmp_mult.num = 2;
    tmp_mult.denom = 1;
    FracMultiply(&tmp2, &tmp_mult, &d1);
    FracSubstract(&tmp3,&tmp2,&d2);
    FracDivide(&tmp4,&tmp3,&d1);
    FracSubstract(&res,&tmp1,&tmp4);

    cout << "Formula #2: res = f1 * f2 - (2*f1 - f2) / f1" << endl;
    cout << "Result #2 = " << res.num << "/" << res.denom << endl;
    return 0;
}
