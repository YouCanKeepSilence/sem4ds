#include "writer.h"

Writer::Writer()
{
    currentBit=0;
    currentByte=0;
    out=NULL;
}

void Writer::attach(std::__1::ostream *out)
{
    this->out = out;
    this->currentBit=0;
    this->currentByte=0;
}

void Writer::detach()
{
    this->out = NULL;
    this->currentBit=0;
    this->currentByte=0;
}

std::__1::ostream *Writer::getStream()
{
    return this->out;
}

void Writer::setState(Tools::States state)
{
    this->state=state;
}

void Writer::writeNextBit(bool bit)
{

    if(bit)
    {
        currentByte = currentByte | (0b10000000 >> currentBit);
    }
    currentBit++;
    if(currentBit > 7 )
    {
        currentBit=0;
        *out<<currentByte;
        currentByte = 0;
    }

}
