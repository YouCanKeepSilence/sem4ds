#include "reader.h"

Reader::Reader()
{
    this->in = NULL;
    this->currentBit = 8;
    this->currentByte = 0;
}

Reader::~Reader()
{
    this->detach();
}

void Reader::attach(std::istream *in)
{
    this->in = in;
    this->currentBit = 8;
    this->currentByte = 0;
}

void Reader::detach()
{
    this->in = NULL;
    this->currentBit = 8;
    this->currentByte = 0;
}

std::istream *Reader::getStream()
{
    return in;
}

void Reader::setState(Tools::States state)
{
    this->state = state;
}

int Reader::readNextSymbol()
{

    if(!in)
    {
        std::cerr<<"No in thread attached , 0 returns "<<std::endl;
        return 0;
    }
    unsigned short result=0;
    unsigned short mask = 0b0000000000000001;
    for(int i = 0 ; i < 8+ state; i++)
    {
        if(in->eof() && (i==1 || i==8))
        {
            result = -1;
            break;
        }
        if(readNextBit())
        {
            result = result | (mask << i);
        }
    }
    return result;
}

bool Reader::readNextBit()
{
    if(currentBit > 7)
    {
        currentBit = 0 ;
        currentByte = in->get();
        if(in->eof())
        {
            return false;
        }
    }
    bool bit = false;
    unsigned char mask = 0b00000001;
    bit = currentByte & (mask << currentBit);
    currentBit++;

    return bit;
}
