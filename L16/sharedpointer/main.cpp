#include <QCoreApplication>
#include <QLabel>
#include <mysharedpointer.h>
#include <iostream>

using namespace std;

struct C {
    C()
    { cout << "Created" << endl; }
    ~C()
    { cout << "Deleted " << val << endl; }
    int val;
};

int main()
{
    int i = 2;
    while (i--)
    {
        cout << "\n\n";
        cout << "mPtr1\n";

        MySharedPointer<C> mPtr1(new C[10], [](C * a){delete[] a;});
        for (int i = 0; i < 10; i++)
            mPtr1[i].val = i;

        cout << "mPtr2\n";
        MySharedPointer<C> mPtr2;
        mPtr2 = mPtr1;
        cout << "mPtr3\n";
        MySharedPointer<C> mPtr3;
        mPtr3 = mPtr1;
    }
}

