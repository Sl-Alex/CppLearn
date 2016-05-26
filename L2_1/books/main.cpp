#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include "mainwindow.h"
#include "book.h"
#include "booktablemodel.h"

using namespace std;

std::vector<Book> collection;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showNormal();

    return a.exec();
}

