#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book
{
public:
    Book();

    std::string id;
    std::vector<std::string> authors;
    std::string title;
    std::string publisher;
    int year;
    int code;
    std::string borrowed;

    void clear(void);
private:
};

#endif // BOOK_H
