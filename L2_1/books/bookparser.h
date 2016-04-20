#ifndef BOOKPARSER_H
#define BOOKPARSER_H

#include "book.h"

class BookParser
{
public:
    static bool parseLine(std::string line, Book * book);

    static inline BookParser * getInstance()
    {
        if(!pInstance)
        {
            pInstance = new BookParser();
        }
        return pInstance;
    }
private:
    static BookParser * pInstance;
    BookParser(){}
    BookParser(const BookParser&);
    BookParser& operator=(BookParser&);
};

#endif // BOOKPARSER_H
