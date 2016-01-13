#include <iostream>

using namespace std;

int char_count(const char *);

void task5(void)
{
    char line1[100];
    char line2[100];

    cout << "Lines will be concatenated in a new line" << endl;

    cout << "Enter line number 1" << endl;
    cin.getline(line1, 100);
    cout << "Enter line number 2" << endl;
    cin.getline(line2, 100);

    // The length of the result with the null-termination
    int sz = char_count(line1) + char_count(line1) + 1;

    char * line3 = new char[sz];

    int i = 0;
    char * pstr = line3;

    // Copy first string
    while (line1[i] != 0)
        *pstr++ = line1[i++];

    i = 0;

    // Copy second string
    while (line2[i] != 0)
        *pstr++ = line2[i++];

    // Add null-termination
    *pstr = '\0';

    cout << "Line1: \"" << line1 << "\"" << endl;
    cout << "Line2: \"" << line2 << "\"" << endl;
    cout << "Result: \"" << line3 << "\"" << endl;

    delete[] line3;
}
