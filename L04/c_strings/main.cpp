#include <iostream>

using namespace std;

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);
void task6(void);

int main()
{
    int task;
    cout << "Enter task number (1..6)" << endl;
    cin >> task;
    cin.sync();
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
