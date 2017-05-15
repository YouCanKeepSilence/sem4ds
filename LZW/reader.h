#ifndef READER_H
#define READER_H
#include "tools.h"
#include <iostream>
class Reader
{
public:
    Reader();
    ~Reader();
    void attach(std::istream * in);
    void detach();
    std::istream * getStream();
    void setState(Tools::States state);
    int readNextSymbol();
private:
    Tools::States state;
    bool readNextBit();
    char currentByte;
    int currentBit;
    std::istream *in;
};

#endif // READER_H
