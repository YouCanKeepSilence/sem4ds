#ifndef WRITER_H
#define WRITER_H
#include "tools.h"
#include <iostream>
class Writer
{
public:
    Writer();
    ~Writer();
    void attach(std::ostream * out);
    void detach();
    std::ostream * getStream();
    void writeCode(unsigned short code);
    void flush();
    void setState(Tools::States state);

private:
    Tools::States state;
    void writeNextBit(bool bit);
    char currentByte;
    int currentBit;

    std::ostream *out;
};

#endif // WRITER_H
