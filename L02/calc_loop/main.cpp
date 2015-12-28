#include <iostream>
#include <climits>

using namespace std;

typedef enum {
    LS_WHILE = 1,
    LS_DO_WHILE,
    LS_FOR
} loop_style_t;

int main()
{
    int loop_style;

    int res_sum = 0;
    int res_max = INT_MIN;
    int res_min = INT_MAX;
    int res_pos = 0;
    int res_even = 0;
    int total_cnt = 0;
    int number;
    int exit = 0;

    cout << "Hello world!" << endl;

    cout << "Select loop style:" << endl;
    cout << "  1: while() {...}" << endl;
    cout << "  2: do {...} while();" << endl;
    cout << "  3: for() {...}" << endl;
    cin >> loop_style;

    cout << "Enter digits separated by space or by newline" << endl;
    cout << "Zero means the end of the input" << endl;

    switch (loop_style)
    {
        case LS_WHILE:
            while (!exit)
            {
                cin >> number;
                if (number == 0)
                {
                    exit = 1;
                    continue;
                }
                res_sum += number;
                res_max = (number > res_max) ? number : res_max;
                res_min = (number < res_min) ? number : res_min;
                res_pos = (number > 0) ? res_pos+1 : res_pos;
                res_even = ((number % 2) == 0) ? res_even+1 : res_even;

                total_cnt++;
            }
            break;
        case LS_DO_WHILE:
            do
            {
                cin >> number;
                if (number == 0)
                {
                    exit = 1;
                    continue;
                }
                res_sum += number;
                res_max = (number > res_max) ? number : res_max;
                res_min = (number < res_min) ? number : res_min;
                res_pos = (number > 0) ? res_pos+1 : res_pos;
                res_even = ((number % 2) == 0) ? res_even+1 : res_even;

                total_cnt++;
            }
            while (!exit);
            break;
        case LS_FOR:
            for (;!exit;)
            {
                cin >> number;
                if (number == 0)
                {
                    exit = 1;
                    continue;
                }
                res_sum += number;
                res_max = (number > res_max) ? number : res_max;
                res_min = (number < res_min) ? number : res_min;
                res_pos = (number > 0) ? res_pos+1 : res_pos;
                res_even = ((number % 2) == 0) ? res_even+1 : res_even;

                total_cnt++;
            }
            break;
        default:
            cout << "Wrong or not yet implemented loop style" << endl;
    }

    if (total_cnt > 0)
    {
        cout << endl;
        cout << "Input statistics:" << endl;
        cout << "Sum = " << res_sum << endl;
        cout << "Max = " << res_max << endl;
        cout << "Min = " << res_min << endl;
        cout << "Positive count = " << res_pos << endl;
        cout << "Even count = " << res_even << endl;
        cout << "=============================" << endl;
        cout << "Total count = " << total_cnt << endl;
    }
    else
    {
        cout << "Empty input";
    }

    return 0;
}
