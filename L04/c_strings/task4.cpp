#include <iostream>
#include "str_utils.h"

using namespace std;

void task4(void)
{
    char line1[100];

    cout << "Enter the line" << endl;
    cout << "String will be copied to the new string" << endl;
    cin.getline(line1, 100);

    // Array size is one char longer (null-termination)
    int sz = str_utils_get_len(line1) + 1;

    char * line2 = new char[sz];

    for (int i = 0; i < sz; i++)
        line2[i] = line1[i];


    cout << "Entered line: \"" << line1 << "\" (array size is 100 chars)" << endl;
    cout << "Copied  line: \"" << line2 << "\" (array size is " << sz << " chars)" << endl;

    delete[] line2;
}
