#ifndef STRINGSPLITTER_H
#define STRINGSPLITTER_H

#include <string>
#include <vector>
#include <iostream>

class StringSplitter
{
public:
    StringSplitter();

    void start(void) { remainder = ""; }
    void end(std::vector<std::string> &output)
    {
        if (!remainder.empty())
            output.emplace_back(remainder);
    }

    void parseBlock(const std::string input, std::vector<std::string> &output)
    {
        output.clear();

        size_t pos = input.find_first_of(delimiters);

        if (pos != 0)
            remainder.clear();

        size_t posBegin = 0;
        size_t posEnd = 0;

        std::string word;

        while (true)
        {
            posBegin = input.find_first_not_of(delimiters,posEnd);
            if (posBegin == std::string::npos) return;

            posEnd = input.find_first_of(delimiters,posBegin);
            if (posEnd == std::string::npos)
            {
                // Last word without end delimiter
                remainder = input.substr(posBegin, input.length() - posBegin);
                return;
            }
            else
            {
                word = input.substr(posBegin, posEnd - posBegin);
            }

            output.emplace_back(word);
        }
    }

    std::string &getRemainder(void) { return remainder; }

private:
    std::string remainder;
    const char * delimiters = " \n\r\t";
};

#endif // STRINGSPLITTER_H
