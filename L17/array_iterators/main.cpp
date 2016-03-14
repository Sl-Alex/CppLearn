#include <iostream>
#include "dynarr.h"
#include "fixarr.h"

using namespace std;

const int farrSize = 3;

int main()
{
    DynArr<int> arr;

    FixArr<int, farrSize> farr1;
    FixArr<int, farrSize> farr2;

    farr1[0] = 1; farr1[1] = 2; farr1[2] = 3;
    farr2[0] = 4; farr2[1] = 5; farr2[2] = 6;

    DynArr<int> darr;
    darr[0] = 1;
    darr[1] = 2;
    darr[2] = 3;
    darr[3] = 4;
    darr[4] = 5;

    cout << "Dyn arr output with iterator: " << endl;
    for (auto it = darr.begin(); it != darr.end(); ++it)
        cout << *it << endl;

    cout << "Fixed arr output with iterator: " << endl;
    for (auto it = farr1.begin(); it != farr1.end(); ++it)
        cout << *it << endl;

    cout << "Fixed arr1: " << farr1 << endl;
    cout << "Fixed arr2: " << farr2 << endl;
    farr2 = farr1;
    cout << "Copy farr1 to farr2. farr2: " << farr2 << endl;
    farr2[0] = 7; farr2[1] = 8; farr2[2] = 9;
    cout << "Fixed arr1: " << farr1 << endl;
    cout << "Fixed arr2: " << farr2 << endl;

    DynArr< FixArr< int,3 > > dfarr;

    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            farr1[j] = i*10 + j;
        }
        dfarr[i] = farr1;
    }

    cout << "DynArr<FixArr<int,3>>: " << dfarr << endl;

    FixArr< DynArr< int >, 3 > fdarr;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5 + i; ++j)
        {
            fdarr[i][j] = i*10 + j;
        }
    }

    cout << "FixArr<DynArr<int>,3>: " << fdarr << endl;

    return 0;
}
