#ifndef BITREADER_H
#define BITREADER_H
#include <fstream>

class BitReader
{
public:
    BitReader();
    ~BitReader();
    void attach(std::ifstream * fromFile);
    void detach();
    std::ifstream * getStream() const;
    int readNextBit();

private:

    std::ifstream * m_fromFile;
    unsigned char m_currentByte;
    int m_currentBit;
};

#endif // BITREADER_H
