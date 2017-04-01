#ifndef BINARYWRITER_H
#define BINARYWRITER_H
#include <iostream>
#include <string>

class BinaryWriter
{
public:
    BinaryWriter();
    static void binaryWrite(std::ofstream * toFile, std::ifstream * fromFile, std::string* encodingTable);
    static void writeHeader(std::ofstream * toFile, int* symbols);
};

#endif // BINARYWRITER_H
