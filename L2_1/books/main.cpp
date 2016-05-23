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
/*
    Book book;

    if (argc < 2)
        cout << "File is not specified" << endl;

    collection.clear();

    string line;
    ifstream myfile (argv[1]);

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (BookParser::parseLine(line,&book))
            {
                collection.push_back(book);
            }
            book.clear();
        }
        myfile.close();
    }
    else
    {
        cout << "Can not open file" << endl;
    }

    for (auto book_it = collection.begin(); book_it != collection.end(); book_it++)
    {
        // Output parsed values
        cout << "Book ID     = " << book_it->id << std::endl;
        for (auto auth_it = book_it->authors.begin(); auth_it != book_it->authors.end(); auth_it++)
            std::cout << "  Author    = " << *auth_it << std::endl;
        std::cout << "Title       = " << book_it->title << std::endl;
        std::cout << "Publisher   = " << book_it->publisher << std::endl;
        if (book_it->year != 0)
            std::cout << "Year        = " << book_it->year << std::endl;

        std::cout << "Code        = " << book_it->code << std::endl;
        std::cout << "Borrowed by = " << book_it->borrowed << std::endl;
    }

    return 0;
    */
}

