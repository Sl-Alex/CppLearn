#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> arr;
    cout << "Enter any numbers, one by one." << endl;
    cout << "They will be added to the array." << endl;
    cout << "Zero means the end of the input." << endl;
    cout << "Array size will be adjusted automatically" << endl;

    int tmp;
    cin >> tmp;

    while (tmp)
    {
        arr.push_back(tmp);
        cin >> tmp;
    }

    cout << "==================" << endl;

    cout << "Normal output:" << endl;
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << endl;

    cout << "Reversed output:" << endl;
    for (auto it = arr.rbegin(); it != arr.rend(); ++it)
        cout << *it << endl;

    sort(arr.begin(),arr.end());

    cout << "Normal output:" << endl;
    for (auto it = arr.begin(); it != arr.end(); ++it)
        cout << *it << endl;

    return 0;
}
