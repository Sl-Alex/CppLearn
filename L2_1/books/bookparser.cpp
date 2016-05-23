#include "bookparser.h"
#include <iostream>

#include <QStringList>

BookParser * BookParser::pInstance = NULL;

bool BookParser::parseLine(QString line, Book * book)
{
    bool ok;

    QStringList list;

    book->authors.clear();

    list = line.split(";");

    if (list.size() < 6) return false;

    book->id = list.at(0).simplified();

    book->authors.push_back(list.at(1).simplified());

    book->title = list.at(2).simplified();

    book->publisher = list.at(3).simplified();

    QStringList tmpList = list.at(3).simplified().split(",");

    book->year = tmpList.at(tmpList.size()-1).simplified().toInt(&ok);
    if (ok)
    {
        if (tmpList.size() > 1)
            book->publisher = tmpList.at(0);
        else
            book->publisher = "";
    }

    book->code = list.at(4).simplified().toInt(&ok);
    if (!ok) book->code = 0;

    book->borrowed = list.at(5).simplified();

    return true;
}
