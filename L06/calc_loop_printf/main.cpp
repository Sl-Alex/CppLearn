#include <iostream>
#include <climits>
#include <stdio.h>

using namespace std;

typedef enum {
    LS_WHILE = 1,
    LS_DO_WHILE,
    LS_FOR
} loop_style_t;

typedef struct {
    int res_sum;
    int res_max;
    int res_min;
    int res_pos;
    int res_even;
    int total_cnt;
} stat_t;

void update_stat(int number, stat_t * st)
{
    st->res_sum += number;
    st->res_max = (number > st->res_max) ? number : st->res_max;
    st->res_min = (number < st->res_min) ? number : st->res_min;
    st->res_pos = (number > 0) ? st->res_pos+1 : st->res_pos;
    st->res_even = ((number % 2) == 0) ? st->res_even+1 : st->res_even;
    st->total_cnt++;
}

int main()
{
    int loop_style;

    stat_t st = {0,INT_MIN,INT_MAX,0,0,0};

    int number;
    int exit = 0;

    printf("Hello world!\n");

    printf("Select loop style:\n");
    printf("  1: while() {...}\n");
    printf("  2: do {...} while();\n");
    printf("  3: for() {...}\n");

    cin >> loop_style;

    printf("Style %i was selected\n", loop_style);

    printf("Enter digits separated by space or by newline\n");
    printf("Zero means the end of the input\n");

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
                update_stat(number,&st);
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
                update_stat(number,&st);
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
                update_stat(number,&st);
            }
            break;
        default:
            printf("Wrong or not yet implemented loop style\n");
    }

    if (st.total_cnt > 0)
    {
        printf("\n");
        printf("Input statistics:\n");
        printf("Sum = %i\n", st.res_sum);
        printf("Max = %i\n", st.res_max);
        printf("Min = %i\n", st.res_min);
        printf("Positive count = %i\n", st.res_pos);
        printf("Even count = %i\n", st.res_even);
        printf("=============================\n");
        printf("Total count = %i\n", st.total_cnt);
    }
    else
    {
        printf ("Empty input\n");
    }

    return 0;
}
