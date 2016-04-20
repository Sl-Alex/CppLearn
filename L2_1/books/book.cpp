#include "book.h"

Book::Book()
{
    clear();
}

void Book::clear(void)
{
    id = "";
    authors.clear();
    title = "";
    publisher = "";
    year = 0;
    code = 0;
    borrowed = "";
}
