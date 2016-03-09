#include <QCoreApplication>
#include <QLabel>
#include <mysharedpointer.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);


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
        mPtr3 = mPtr2;
        cout << "delete 1\n";
        mPtr1.~MySharedPointer();
        cout << "deleted\n";
    }


//    return a.exec();
}

