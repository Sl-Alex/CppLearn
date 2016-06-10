#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <thread>

#include "wordcounter.h"
#include "totalcounter.h"

WordCounter wc;
TotalCounter tc;

void usage(void)
{
    std::cout << "Usage: word_calc filename" << std::endl;
    std::cout << "  filename - input file name" << std::endl;
}

void tcThread(std::vector<std::string> *input)
{
    for (auto word = input->begin(); word != input->end(); ++word)
    {
        tc.add(1);
    }
}

void wcThread(std::vector<std::string> *input)
{
    for (auto word = input->begin(); word != input->end(); ++word)
    {
        wc.addWord(*word);
    }
}

void string_split(std::string from, std::vector<std::string> &to, std::string delimiters)
{
    to.clear();

    size_t posBegin = 0;
    size_t posEnd = 0;
    std::string word;

    while (true)
    {
        posBegin = from.find_first_not_of(delimiters,posEnd);
        if (posBegin == std::string::npos) return;

        posEnd = from.find_first_of(delimiters,posBegin);
        if (posEnd == std::string::npos)
        {
            word = from.substr(posBegin, from.length() - posBegin);
        }
        else
        {
            word = from.substr(posBegin, posEnd - posBegin);
        }

        to.push_back(word);

        std::cout << "#" << word << "#";
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cout << "Wrong number of arguments" << std::endl;
        usage();
        return EINVAL;
    }

    std::string fileName = argv[1];

    std::ifstream wordFile(fileName, std::ios::in|std::ios::binary);
    if (!wordFile.is_open())
    {
        std::cout << "Can't open file" << std::endl;
        return EIO;
    }

    std::string line;
    std::vector<std::string> lineWords;
    while(std::getline(wordFile,line))
    {
        string_split(line, lineWords, " \x09\x0D\x0A");

        std::thread  first(wcThread, &lineWords);
        std::thread second(tcThread, &lineWords);

        second.join();
        first.join();

        std::cout << std::endl;
    }

    wordFile.close();

    std::cout << "Result - " << tc.count() << " word(s) :" << std::endl;

    std::ofstream outfile("result.txt", std::ios::out|std::ios::binary|std::ios::trunc);

    for (auto it = wc.begin(); it != wc.end(); ++it)
    {
        std::stringstream line;

        line << "(" << it->first << ") (" << it->second << ")" << std::endl;

        const std::string tmp = line.str();

        outfile.write(tmp.c_str(),tmp.length());
    }
    outfile.close();

    return EXIT_SUCCESS;
}

