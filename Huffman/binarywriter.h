#ifndef BINARYWRITER_H
#define BINARYWRITER_H
#include <iostream>
#include <string>

class BinaryWriter
{
public:
    BinaryWriter();
    static void binaryWrite(std::ofstream * toFile, std::ifstream * fromFile, std::string* encodingTable);
    static void writeHeader(std::ofstream * toFile, uint32_t *symbols);
private:
    static void flushToFile(std::ofstream * toFile, std::string s_byte);
};

#endif // BINARYWRITER_H
