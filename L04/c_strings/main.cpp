#include <iostream>
#include <limits>
#include "tasks.h"

using namespace std;

int main()
{
    int task;
    cout << "Enter task number (1..6)" << endl;
    cin >> task;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    switch(task)
    {
        case 1:
            task1();
        break;
        case 2:
            task2();
        break;
        case 3:
            task3();
        break;
        case 4:
            task4();
        break;
        case 5:
            task5();
        break;
        case 6:
            task6();
        break;
        default:
            cout << "Wrong task selected" << endl;
    }
    return 0;
}
