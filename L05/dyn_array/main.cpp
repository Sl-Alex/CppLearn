#include <iostream>

using namespace std;

int * alloc_more(int * arr, int &arr_size, const unsigned int increment)
{
    // Create a new array
    int * new_arr = new int [arr_size + increment];

    // Copy all data
    for (int i = 0; i < arr_size; i++)
    {
        new_arr[i] = arr[i];
    }

    // Increase array size
    arr_size += increment;

    // Free old memory
    delete[] arr;

    return new_arr;
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
            arr = alloc_more(arr, arr_size, SIZE_INCREMENT);
            cout << "Array size was increased to " << arr_size << endl;
        }

        cin >> arr[data_cnt];
    }

    cout << "==================" << endl;
    cout << "Reversed array:" << endl;

    for (int i = data_cnt - 1; i >= 0; --i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;

    return 0;
}
