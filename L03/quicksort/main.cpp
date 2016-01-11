#include <iostream>
#include <iomanip>

using namespace std;

/// @brief Width of the number (symbols)
const int NUM_WIDTH = 3;
/// @brief Array size
const int ARR_SIZE = 10;
/// @brief Output details
const bool DETAILS = false;

int myarr[ARR_SIZE] = {1,6,5,8,9,2,7,3,0,4};
int call_cnt = 0;
int swap_cnt = 0;

void print_nchar(char ch, int count)
{
    for (int i = 0; i < count; ++i)
        cout << ch;
}

void arr_swap(int * arr, int idx1, int idx2)
{
    swap_cnt++;
    for (int i = 0; i < ARR_SIZE; ++i)
    {
        cout << setw(NUM_WIDTH) << arr[i];
    }
    cout << endl;

    for (int i = 0; i < ARR_SIZE; ++i)
    {
        if (i < idx1)
            print_nchar(' ',NUM_WIDTH);
        if (i == idx1)
        {
            print_nchar(' ',NUM_WIDTH - 1);
            cout << "\xC0"; // "|_"
        }
        if (i > idx2)
            print_nchar(' ',NUM_WIDTH);
        if (i == idx2)
        {
            print_nchar('\xC4',NUM_WIDTH - 1);
            cout << "\xD9"; // "_|"
        }
        if ((i > idx1) && (i < idx2))
            print_nchar('\xC4',NUM_WIDTH); // "-"
    }
    cout << endl;

    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

void qsort(int * arr, int il, int ir)
{
    int l = il;
    int r = ir;
    int mid = arr[(l+r)/2];

    call_cnt++;

    if (DETAILS)
    {
        cout << "Sorting elements #" << il+1 << " till #" << ir+1 << endl;
        cout << "Reference value is " << mid << endl;
    }

    while ( l <= r )
    {
        while (arr[l] < mid) ++l;
        while (arr[r] > mid) --r;
        if ( l <= r )
        {
            if ((l != r) && arr[l] != arr[r])
            {
                if (DETAILS) cout << "Swapping #" << l+1 << " and #" << r+1 << endl;
                arr_swap(arr, l, r);
            }
            ++l; --r;
        }
    }
    if (il < r)
        qsort (arr, il, r);
    if (ir > l)
        qsort (arr, l, ir);
}

int main()
{
    cout << "Enter " << ARR_SIZE << " numbers separated by space and press Enter" << endl;

    // Input all numbers
    for (int i = 0; i < ARR_SIZE; ++i)
    {
        cin >> myarr[i];
    }

    print_nchar('\xCD',NUM_WIDTH * ARR_SIZE);
    cout << endl;

    qsort(myarr, 0, ARR_SIZE - 1);

    print_nchar('\xCD',NUM_WIDTH * ARR_SIZE);
    cout << endl;

    for (int i = 0; i < ARR_SIZE; ++i)
    {
        cout << setw(NUM_WIDTH) << myarr[i];
    }
    cout << endl;

    cout << "Calls : " << call_cnt << "; swaps: " << swap_cnt << endl;

    return 0;
}

