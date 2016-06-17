#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <ctime>

#include "wordcounter.h"
#include "totalcounter.h"
#include "stringsplitter.h"

WordCounter wc;
TotalCounter tc;

void usage(void)
{
    std::cout << "Usage: word_calc filename" << std::endl;
    std::cout << "  filename - input file name" << std::endl;
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

    char * buffer = new char [1024000];

    size_t start1, end1;
    size_t start2, end2;

    size_t time1 = 0;
    size_t time2 = 0;

    std::thread thread1;
    std::thread thread2;

    wc.start();
    tc.start();

    std::cout << "Processing..." << std::endl;
    while(true)
    {
        // file read begin
        start1 = clock();
        if (!wordFile.read(buffer,1024))
        {
            end1 = clock();
            time1 += end1 - start1;
            // file read end
            break;
        }
        end1 = clock();
        time1 += end1 - start1;
        // file read end

        // parse begin
        start2 = clock();



        static bool skip = true;
        if (!skip)
        {
            thread1.join();
            thread2.join();
        }
        skip = false;

        std::string line(buffer);

        thread1 = std::thread(&wc.addBlock, &wc, line);
        thread2 = std::thread(&tc.addBlock, &tc, line);

        end2 = clock();
        time2 += end2 - start2;
        // parse end
    }
    thread1.join();
    thread2.join();

    wc.finish();
    tc.finish();

    wordFile.close();

    std::cout << "Result - " << tc.count() << " word(s)" << std::endl;
    std::cout << "         " << wc.count() << " unique word(s)" << std::endl;
    std::cout << "I/O time:        " << time1 << std::endl;
    std::cout << "Processing time: " << time2 << std::endl;
    std::cout << "Total time:      " << time1 + time2 << std::endl;

    return EXIT_SUCCESS;
}

