#include <iostream>

using namespace std;

void task1(void);
void task2(void);

int main()
{
    const int max_task = 1;
    int task;

    cout <<  "Enter task number (0..1)" << endl;
    cin >> task;

    if ((task > max_task) || (task < 0))
    {
        cout << "Wrong number" << endl;
        return -1;
    }

    cout << "Task number " << task << " was selected" << endl;

    // Choose which task to solve
    switch (task)
    {
        case 0:
            // Solving Task 0
            task1();
        break;
        case 1:
            // Solving Task 1
            task2();
        break;
    }

    cout << "Done." << endl;

    return 0;
}

void task1(void)
{
    int int1, int2;
    double double1, double2;

    cout << "Enter two integer numbers separated by space" << endl;
    cin >> int1 >> int2;

    cout << int1 << " + " << int2 << " = " << int1 + int2 << endl;
    cout << int1 << " - " << int2 << " = " << int1 - int2 << endl;
    cout << int1 << " * " << int2 << " = " << int1 * int2 << endl;
    cout << int1 << " / " << int2 << " = " << int1 / int2 << endl;
    cout << int1 << " % " << int2 << " = " << int1 % int2 << endl;

    cout << "Enter two floating-point numbers separated by space" << endl;
    cin >> double1 >> double2;

    cout << double1 << " + " << double2 << " = " << double1 + double2 << endl;
    cout << double1 << " - " << double2 << " = " << double1 - double2 << endl;
    cout << double1 << " * " << double2 << " = " << double1 * double2 << endl;
    cout << double1 << " / " << double2 << " = " << double1 / double2 << endl;
}

void task2(void)
{
    unsigned int num;

    cout <<  "Enter any unsigned integer" << endl;
    cin >> num;
    cout << "Number " << num << " was entered" << endl;

    unsigned int sum = 0;

    do {
        sum += num % 10;
        num /= 10;
    } while (num > 0);

    cout << "Sum of the digits is equal to " << sum << endl;
}
