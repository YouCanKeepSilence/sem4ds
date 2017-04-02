#ifndef ARCHIVER_H
#define ARCHIVER_H
#include <string>

class Archiver
{
public:
    Archiver();
    static void archive(std::string inputFile,std::string outFile);
    static void unarchive(std::string inputFile,std::string outFile);
};

#endif // ARCHIVER_H
