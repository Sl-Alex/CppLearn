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
std::mutex queueMutex;
std::mutex mapMutex;
std::atomic<bool> readerDone(false);
size_t readerTimeStart = 0;
size_t readerTimeEnd = 0;
size_t parserTimeStart = 0;
std::atomic<size_t> parserTimeEnd(0);
size_t totalTimeStart = 0;
size_t totalTimeEnd = 0;

char * fileBuffer = 0;

std::ifstream::pos_type filesize(std::string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

char * findFirstEmpty(char * data, char * end);
char * findFirstNotEmpty(char * data, char * end);
char * findLastEmpty(char * data, char * end);

void reader(std::string fileName, int bufferSize)
{
    readerTimeStart = clock();

    auto fSize = filesize(fileName);
    if (fSize == std::string::npos)
    {
        std::cout << "Wrong file size" << std::endl;
        readerDone = true;
        return;
    }

    fileBuffer = new char[fSize];

    std::ifstream wordFile(fileName, std::ios::in|std::ios::binary);
    if (!wordFile.is_open())
    {
        std::cout << "Can't open file" << std::endl;
        readerDone = true;
        return;
    }

    char * begin = fileBuffer;
    char * end = fileBuffer;

    char * cur = fileBuffer;

    while (true)
    {
        tBuffer buf;

        if (!wordFile.read(cur, bufferSize))
        {
            buf.begin = begin;
            buf.size = wordFile.gcount();

            // Add remaining data to the vector
            std::lock_guard<std::mutex> lock(queueMutex);
            rawData.push_back(buf);

            break;
        }
        cur += bufferSize;

        end = findLastEmpty(begin, cur);
        if (end)
        {
            buf.begin = begin;
            buf.size = end - begin;

            begin = end;

            // Add block to the vector
            std::lock_guard<std::mutex> lock(queueMutex);
            rawData.push_back(buf);
        }
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

char * findLastEmpty(char * data, char * end)
{
    while (end != data)
    {
        if ((*end == ' ') ||
            (*end == '\n') ||
            (*end == '\r') ||
            (*end == '\t'))
        return end;

        end--;
    }
    return 0;
}

void parser(void)
{
//    parserTimeStart = clock();

    while(true)
    {
        tBuffer buf;

        // Get buffer pointers
        size_t blocksCount = 0;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            blocksCount = rawData.size();
            if (blocksCount > 0)
            {
                buf = rawData.at(0);
                rawData.erase(rawData.begin());
            }
        }
        if (blocksCount == 0)
        {
            if (readerDone == false)
            {
                std::this_thread::yield();
                continue;
            }
            break;
        }

        // Parse buffer
        char * pBegin = buf.begin;
        char * pEnd = buf.begin;

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
                std::string word = std::string(pBegin, buf.begin + buf.size);
                std::lock_guard<std::mutex> lock(mapMutex);
                ++wordMap[word];
                break;
            }
            else
            {
                std::string word = std::string(pBegin, pEnd);
                std::lock_guard<std::mutex> lock(mapMutex);
                ++wordMap[word];
            }
        }
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

    fileBuffer = 0;

    totalTimeStart = clock();
    std::thread thread1 = std::thread(&reader, fileName, 1024);
    parserTimeStart = clock();
    std::thread thread2 = std::thread(&parser);

    thread1.join();
    thread2.join();

    if (fileBuffer)
        delete[] fileBuffer;

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

