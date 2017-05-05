#include "reader.h"

Reader::Reader()
{
    this->in = NULL;
    this->currentBit = 0;
    this->currentByte = 0;
}

void Reader::attach(std::__1::istream *in)
{
    this->in = in;
    this->currentBit = 0;
    this->currentByte = 0;
}

void Reader::detach()
{
    this->in = NULL;
    this->currentBit = 0;
    this->currentByte = 0;
}

std::__1::istream *Reader::getStream()
{
    return in;
}

void Reader::setState(Tools::States state)
{
    this->state = state;
}

unsigned short Reader::readNextSymbol()
{
    unsigned short result=0;
    unsigned short mask = 0b0000000000000001;
    for(int i = 0 ; i< 8+ state; i++)
    {
        if(readNextBit())
        {
            result = result | (mask << i);
        }
    }
    return result;
}

bool Reader::readNextBit()
{
    if(currentByte == 0)
    {
        currentByte=in->get();
    }
    bool bit = false;
    unsigned char mask = 0b00000001;
    bit = currentByte & (mask << currentBit);
    currentBit++;
    if(currentBit > 7)
    {
        currentBit = 0 ;
        currentByte=0;
    }
    return bit;
}
