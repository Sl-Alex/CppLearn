#include <iostream>

using namespace std;

void task2(void)
{
    char line1[100];
    char line2[100];

    cout << "Lines will be compared" << endl;
    cout << "Enter line number 1" << endl;
    cin.getline(line1, 100);
    cout << "Enter line number 2" << endl;
    cin.getline(line2, 100);

    int i = 0;
    bool are_equal = false;

    while (line1[i] == line2[i])
    {
        if ((line1[i] == '\0' ) && (line2[i] == '\0'))
            are_equal = true;
        i++;
    }
    cout << "Line1 \"" << line1 << "\" was entered" << endl;
    cout << "Line2 \"" << line2 << "\" was entered" << endl;

    if (are_equal)
        cout << "Strings are equal" << endl;
    else
        cout << "Strings are different" << endl;

}
