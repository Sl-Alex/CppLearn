#include <iostream>
#include <cstdlib>
#include <climits>

#include "arr_funcs.h"

using namespace std;

int my_comp(const void * a, const void * b)
{
    if (*static_cast<const int *>(a) > *static_cast<const int *>(b))
        return -1;

    if (*static_cast<const int *>(a) < *static_cast<const int *>(b))
        return 1;

    return 0;
}

int main()
{
    const int SIZE_INCREMENT = 5;
    int arr_size = SIZE_INCREMENT;
    int data_cnt = 0;
    int * arr = new int [arr_size];

    cout << "Enter any numbers, one by one." << endl;
    cout << "They will be added to the array." << endl;
    cout << "Zero means the end of the input." << endl;
    cout << "Array size will be adjusted automatically" << endl;

    cin >> arr[data_cnt];
    while (arr[data_cnt])
    {
        ++data_cnt;

        if (data_cnt >= arr_size)
        {
            arr = arr_alloc_more(arr, &arr_size, SIZE_INCREMENT);
            cout << "Array size was increased to " << arr_size << endl;
        }

        cin >> arr[data_cnt];
    }

    cout << "====================" << endl;
    cout << "Reversed array:" << endl;

    arr_print(arr, data_cnt);

    cout << "Calling std::qsort()" << endl;

    std::qsort(arr, data_cnt, sizeof(int),my_comp);

    cout << "====================" << endl;
    cout << "Sorted array:" << endl;

    arr_print(arr, data_cnt);

    delete[] arr;

    return 0;
}
