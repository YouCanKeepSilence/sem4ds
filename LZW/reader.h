#ifndef READER_H
#define READER_H
#include "tools.h"
#include <iostream>
class Reader
{
public:
    Reader();
    void attach(std::istream * in);
    void detach();
    std::istream * getStream();
    void setState(Tools::States state);
private:
    Tools::States state;
    void readNextBit();
    char currentByte;
    int currentBit;

    std::ostream *out;
};

#endif // READER_H
