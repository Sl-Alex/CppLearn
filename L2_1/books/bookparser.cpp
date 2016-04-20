#include "bookparser.h"
#include <iostream>

BookParser * BookParser::pInstance = NULL;

bool BookParser::parseLine(std::string line, Book * book)
{
    // 1. ID
    size_t pos = line.find(";");
    if (pos == std::string::npos) return false;
    book->id = line.substr(0,pos);

    // 2. Authors
    pos++;
    if (pos >= line.length()) return false;
    size_t newPos = line.find(";", pos);
    if (newPos == std::string::npos) return false;
    std::string authors = line.substr(pos,newPos - pos);
    book->authors.clear();
    size_t auth_pos1 = 0;
    size_t auth_pos2 = 0;
    while (auth_pos1 != std::string::npos)
    {
        auth_pos2 = authors.find(". ", auth_pos1);
        if (auth_pos2 != std::string::npos)
        {
            book->authors.push_back(authors.substr(auth_pos1, auth_pos2 - auth_pos1 + 1));
            auth_pos2 += 2;
        }
        else
        {
            if (auth_pos1 != (authors.length() - 1))
            {
                book->authors.push_back(authors.substr(auth_pos1, authors.length() - auth_pos1));
            }
        }
        auth_pos1 = auth_pos2;
    }
    //book->authors.push_back(authors);

    // 3. Title
    pos = newPos + 1;
    if (pos >= line.length()) return false;
    newPos = line.find(";", pos);
    if (newPos == std::string::npos) return false;
    book->title = line.substr(pos,newPos - pos);

    // 4. Publisher
    pos = newPos + 1;
    if (pos >= line.length()) return false;
    newPos = line.find(";", pos);
    if (newPos == std::string::npos) return false;
    std::string publisher = line.substr(pos,newPos - pos);
    size_t pos_year = publisher.find(", ");
    if (pos_year != std::string::npos)
    {
        try
        {
            //std::cout << "\"" << publisher.substr(pos_year+2,publisher.length() - 1) << "\"" << std:endl;
            book->year = stoi(publisher.substr(pos_year + 1,publisher.length()));
            book->publisher = publisher.substr(0,pos_year);
        }
        catch (...)
        {
            book->publisher = publisher;
            book->year = 0;
        }
    }
    else
    {
        book->publisher = publisher;
        book->year = 0;
    }

    // 5. Code
    pos = newPos + 1;
    if (pos >= line.length()) return false;
    newPos = line.find(";", pos);
    if (newPos == std::string::npos) return false;
    try
    {
        if (newPos == pos) book->code = 0;
        else book->code = stoi(line.substr(pos,newPos - pos));
    }
    catch (...)
    {
        book->code = 0;
    }

    // 6. Borrowed by
    pos = newPos + 1;
    if (pos >= line.length()) return false;
    newPos = line.find(";", pos);
    if (newPos != std::string::npos)
    {
        book->borrowed = line.substr(pos,newPos - pos);
    }
    else
    {
        book->borrowed = line.substr(pos,line.length() - 1);
    }

    return true;
}
