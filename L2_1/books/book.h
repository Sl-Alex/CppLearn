#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <vector>

class Book
{
public:
    Book();

    QString id;
    std::vector<QString> authors;
    QString title;
    QString publisher;
    int year;
    int code;
    QString borrowed;

    void clear(void);
private:
};

#endif // BOOK_H
