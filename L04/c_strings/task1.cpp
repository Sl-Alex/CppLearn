#include <iostream>
#include "str_utils.h"

using namespace std;

void task1(void)
{
    char line[100];

    cout << "Enter the line" << endl;
    cout << "Number of chars will be calculated" << endl;
    cin.getline(line, 100);
    cout << "Line \"" << line << "\" was entered" << endl;

    // Output the number of the symbols in the string;
    cout << "Length is " << str_utils_get_len(line) << " symbols" << endl;
}
