#include <iostream>

using namespace std;

void task3(void)
{
    char line[100];

    cout << "Enter the line" << endl;
    cout << "Number of words will be calculated" << endl;
    cin.getline(line, 100);

    int words = 0;
    int i = 0;

    while (line[i] != '\0')
    {
        if ((line[i] != ' ') && (line[i] != '\0'))
        {
            // If it is the very first symbol
            if (i == 0)
            {
                words++;
            }
            else
            {
                // If the previous symbol was space
                if (line[i-1] == ' ')
                    words++;
            }
        }
        i++;
    }

    cout << "Line \"" << line << "\" was entered" << endl;
    cout << "Words count: " << words << endl;
}
