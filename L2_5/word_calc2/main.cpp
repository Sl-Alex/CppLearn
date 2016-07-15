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

using tWordMap = std::map<std::string, int>;
tWordMap wordMap;
std::vector<tBuffer> rawData;
std::vector<tWordMap*> parsersMaps;
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

void parser(tWordMap threadMap)
{
//    parserTimeStart = clock();

    while(true)
    {
        tBuffer buf;

        // Get buffer pointers
        size_t blocksCount = 0;
        {
            queueMutex.lock();
            //std::lock_guard<std::mutex> lock(queueMutex);
            blocksCount = rawData.size();
            if (blocksCount > 0)
            {
                buf = rawData.back();
                rawData.pop_back();
//                buf = rawData.at(0);
//                rawData.erase(rawData.begin());
            }
            queueMutex.unlock();
        }
        if (blocksCount == 0)
        {
            if (readerDone == false)
            {
                //std::this_thread::yield();
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
                //mapMutex.lock();
                ++threadMap[std::string(pBegin, buf.begin + buf.size)];
                //mapMutex.unlock();
                break;
            }
            else
            {
                //mapMutex.lock();
                ++threadMap[std::string(pBegin, pEnd)];
                //mapMutex.unlock();
            }
        }
    }
    parserTimeEnd = clock();
}


int main(int argc, char *argv[])
{

    if ((argc < 2) || (argc > 3))
    {
        std::cout << "Wrong number of arguments" << std::endl;
        usage();
        return EINVAL;
    }

    int threadsCount = 4;
    if (argc == 3)
    {
        std::string threadsStr = argv[2];
        threadsCount = std::stoi(threadsStr);
        std::cout << threadsCount << " thread(s) were selected" << std:: endl;
    }
    else
    {
        std::cout << "By default " << threadsCount << " thread(s) are used" << std::endl;
    }

    std::string fileName = argv[1];

    std::cout << "Processing..." << std::endl;

    std::vector<std::thread> processingPool;

    fileBuffer = 0;

    totalTimeStart = clock();
    // Start file processing thread
    std::thread fileThread = std::thread(&reader, fileName, 1024);
    // Start parser threads
    parserTimeStart = clock();
    for (int i = 0; i < threadsCount; i++)
    {
        tWordMap *myMap = new tWordMap();
        parsersMaps.push_back(myMap);
        processingPool.emplace_back(std::thread(&parser,*myMap));
    }

    // Join file processing thread (it will definitely be first)
    fileThread.join();

    for (auto it = processingPool.begin(); it != processingPool.end(); ++it)
    {
        it->join();
        tWordMap *myMap = parsersMaps.at(0);
        for (auto itMap = myMap->begin(); itMap != myMap->end(); itMap++)
        {
            wordMap[itMap->first] += itMap->second;
        }
        parsersMaps.erase(parsersMaps.begin());
    }

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

