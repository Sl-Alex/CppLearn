#include <iostream>

using namespace std;

int char_count(const char * line)
{
    int cnt = 0;
    const char * start = line;

    // Loop until the first null
    while (*(line++) != '\0');

    // Return pointer difference;
    return line - start - 1;
}

void task1(void)
{
    char line[100];

    cout << "Enter the line" << endl;
    cout << "Number of chars will be calculated" << endl;
    cin.getline(line, 100);
    cout << "Line \"" << line << "\" was entered" << endl;

    // Output the number of the symbols in the string;
    cout << "Length is " << char_count(line) << " symbols" << endl;
}
