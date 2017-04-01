#ifndef BINARYWRITER_H
#define BINARYWRITER_H
#include <iostream>
#include <string>
using namespace std;
class BinaryWriter
{
public:
    BinaryWriter();
    void attach(ofstream * toFile);
    void detach();
    void writeNextBit(bool bit);
    void binaryWrite(std::ifstream * fromFile, std::string* encodingTable);
    void writeHeader(uint32_t *symbols);
private:
    void flushToFile();
    ofstream * m_toFile;
    char m_currentByte;
    int m_currentBit;

};

#endif // BINARYWRITER_H
