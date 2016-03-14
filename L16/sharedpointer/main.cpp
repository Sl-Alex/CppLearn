#include <QCoreApplication>
#include <QLabel>
#include <mysharedpointer.h>
#include <iostream>

using namespace std;

int main()
{
    int i = 2;
    while (i--)
    {
        cout << "\n\n";
        cout << "mPtr1\n";
        MySharedPointer<int> mPtr1(new int[10], true);
        for (int i = 0; i < 10; i++)
            mPtr1[i] = i;
        cout << "mPtr2\n";
        MySharedPointer<int> mPtr2;
        mPtr2 = mPtr1;
        cout << "mPtr3\n";
        MySharedPointer<int> mPtr3;
        mPtr3 = mPtr1;
    }
}

