#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <ctime>
#include <map>
#include <mutex>
#include <atomic>

void usage(void)
{
    std::cout << "Usage: word_calc filename" << std::endl;
    std::cout << "  filename - input file name" << std::endl;
}

typedef struct {
    char * begin;
    size_t size;
} tBuffer;

std::map<std::string, int> wordMap;
std::vector<tBuffer> rawData;
std::mutex dataMutex;
std::atomic<bool> readerDone(false);
size_t readerTimeStart = 0;
size_t readerTimeEnd = 0;
size_t parserTimeStart = 0;
size_t parserTimeEnd = 0;
size_t totalTimeStart = 0;
size_t totalTimeEnd = 0;

void reader(std::string fileName, int bufferSize)
{
    readerTimeStart = clock();
    std::ifstream wordFile(fileName, std::ios::in|std::ios::binary);
    if (!wordFile.is_open())
    {
        std::cout << "Can't open file" << std::endl;
        readerDone = true;
        return;
    }

    while (true)
    {
        tBuffer buf;

        char * buffer = new char[bufferSize];
        buf.begin = buffer;
        if (!wordFile.read(buffer, bufferSize))
        {
            buf.size = wordFile.gcount();

            // Add remaining data to the vector
            dataMutex.lock();
            rawData.push_back(buf);
            dataMutex.unlock();

            break;
        }

        buf.size = bufferSize;

        // Add block to the vector
        dataMutex.lock();
        rawData.push_back(buf);
        dataMutex.unlock();
    }


    // Done
    wordFile.close();
    readerDone = true;
    readerTimeEnd = clock();
}

char * findFirstEmpty(char * data, char * end)
{
    while (data != end)
    {
        if ((*data == ' ') ||
            (*data == '\n') ||
            (*data == '\r') ||
            (*data == '\t'))
        return data;

        data++;
    }
    return 0;
}

char * findFirstNotEmpty(char * data, char * end)
{
    while (data != end)
    {
        if ((*data != ' ') &&
            (*data != '\n') &&
            (*data != '\r') &
            (*data != '\t'))
        return data;

        data++;
    }
    return 0;
}

void parser(void)
{
    parserTimeStart = clock();
    std::string remainder;

    while(true)
    {
        // Get buffer pointers
        dataMutex.lock();
        if (rawData.size() == 0)
        {
            if (readerDone)
            {
                dataMutex.unlock();
                break;
            }
            dataMutex.unlock();
            std::this_thread::yield();
            continue;
        }
        tBuffer buf = rawData.at(0);
        rawData.erase(rawData.begin());
        dataMutex.unlock();

        // Parse buffer
        char * pBegin = buf.begin;
        char * pEnd = buf.begin;

        if (!remainder.empty())
        {
            pBegin = findFirstNotEmpty(pBegin, buf.begin + buf.size);
            if (pBegin == buf.begin)
            {
                std::string second_part;
                pEnd = findFirstEmpty(pBegin, buf.begin + buf.size);
                if (pEnd)
                {
                    second_part = std::string(pBegin,pEnd);
                    remainder += second_part;
                    ++wordMap[remainder];
                    remainder.clear();
                }
                else
                {
                    second_part = std::string(pBegin,buf.begin + buf.size);
                    remainder += second_part;
                }
            }
            else
            {
                ++wordMap[remainder];
                remainder.clear();
            }
        }

        while (true)
        {
            pBegin = findFirstNotEmpty(pEnd, buf.begin + buf.size);
            if (pBegin == 0)
            {
                break;
            }
            else

            pEnd = findFirstEmpty(pBegin, buf.begin + buf.size);
            if (pEnd == 0)
            {
                // Last word without end delimiter
                remainder = std::string(pBegin, buf.begin + buf.size);
                break;
            }
            else
            {
                std::string word = std::string(pBegin, pEnd);
                ++wordMap[word];
            }
        }

        // Release buffer
        delete[] buf.begin;
    }
    parserTimeEnd = clock();
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

    std::cout << "Processing..." << std::endl;

    totalTimeStart = clock();
    std::thread thread1 = std::thread(&reader, fileName, 1024);
    std::thread thread2 = std::thread(&parser);

    thread1.join();
    thread2.join();

    totalTimeEnd = clock();

    std::cout << "Done." << std::endl;

    std::ofstream ofs ("result.txt", std::ofstream::out);

    for (auto it = wordMap.begin(); it != wordMap.end(); it++)
    {
        ofs << "(" << it->first << ") (" << it->second << ")" << std::endl;
    }

    ofs.close();

    std::cout << "Reader time: " << readerTimeEnd - readerTimeStart << std::endl;
    std::cout << "Parser time: " << parserTimeEnd - parserTimeStart << std::endl;
    std::cout << "Total time:  " << totalTimeEnd - totalTimeStart << std::endl;

    return EXIT_SUCCESS;
}

