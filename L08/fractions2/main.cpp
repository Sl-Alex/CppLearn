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

    Frac f1;
    Frac f2;

    cin >> f1.num;
    cin >> f1.denom;
    cin >> f2.num;
    cin >> f2.denom;

    Frac res;

    cout << endl;

    res = f1 * f2 - (f1 - f2) / f1;
    cout << "Formula #1: res = f1 * f2 - (f1 - f2) / f1;" << endl;
    cout << "  Result #1 = " << res << endl;

    cout << endl;

    res = f1 * f2 - (static_cast<Frac>(2)*f1 - f2) / f1;
    cout << "Formula #2: res = f1 * f2 - (2*f1 - f2) / f1;" << endl;
    cout << "  Result #2 = " << res << endl;

    cout << endl;

    cout << "The following statements are correct:" << endl;

    if (f1 != f2)
        cout << "  Fractions are different" << endl;
    if (f1 == f2)
        cout << "  Fractions are equal" << endl;
    if (f1 >= f2)
        cout << "  f1 >= f2" << endl;
    if (f1 <= f2)
        cout << "  f1 <= f2" << endl;
    if (f1 > f2)
        cout << "  f1 > f2" << endl;
    if (f1 < f2)
        cout << "  f1 < f2" << endl;

    return 0;
}
