#include <QCoreApplication>
#include <QLabel>
#include <myscopedpointer.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);


    int i = 2;
    while (i--)
    {
        MyScopedPointer<int> mPtr(new int[10], true);
        for (int i = 0; i < 10; i++)
            mPtr[i] = i;
        MyScopedPointer<int> mPtr2(new int[20], true);
        for (int i = 0; i < 20; i++)
            mPtr2[i] = i;
        MyScopedPointer<int> mPtr3;
        cout << mPtr[0] << endl;
    }


//    return a.exec();
}

