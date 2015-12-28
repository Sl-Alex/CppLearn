#include <iostream>
#include <stdint.h>

using namespace std;

int main()
{
    // User input
    double number;
    int factor;

    // Internal values
    bool is_negative;   ///< If the power factor is negative
    double mult;        ///< Multiplier for the current step
    double result;      ///< Holds the result

    cout << "Enter the number (double) and the factor (integer)" << endl
         << "separated by space and press Enter" << endl;

    cin >> number >> factor;

    // Check if the factor is negative
    is_negative = (factor < 0);

    // Calculate the absolute value of the factor
    if (is_negative) factor = - factor;

    // Initial assignments
    mult = number;
    result = 1;

    // Calculate the power of the number
    while (factor > 0)
    {
        // If we have to multiply at this step
        if (factor & 1u)
            result = result * mult;

        // Calculate the next multiplier
        mult *= mult;

        // Shift out the power (we use only the lowest bit)
        factor >>= 1;
    }

    // If the power factor is negative
    if (is_negative)
        result = 1 / result;

    cout << "Result = " << result << endl;

    return 0;
}

