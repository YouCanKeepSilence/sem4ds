#ifndef BITREADER_H
#define BITREADER_H
#include <fstream>

class BitReader
{
public:
    BitReader();
    ~BitReader();
    void attach(const std::ifstream * fromFile);
    void detach();
    const std::ifstream * getStream();
    int readNextBit();

private:

    std::ifstream * m_fromFile;
    unsigned char m_currentByte;
    int m_currentBit;
};

#endif // BITREADER_H
