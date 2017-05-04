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

void Writer::writeCode(unsigned short code)
{
    unsigned char * bytes;
    bytes = (unsigned char*)&code;
//    std::cout<<(int)bytes[0]<<" "<<(int)bytes[1]<<std::endl;
    unsigned char mask = 0b00000001;
    std::cout<<8+state<<std::endl;
    for(int i=0; i < 8 + state; i++)
    {
        std::cout<<"Пишу "<<(int) i/8 <<" байт числа "<<code<<" ";
        writeNextBit(bytes[(int) i/8] & (mask << i%8));
    }
    std::cout<<std::endl;
}

void Writer::flush()
{
    if(currentByte)
    {
        *out<<currentByte;
    }
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
//        std::cout<<1<<" ";
    }
    else
    {
//        std::cout<<0<<" ";
    }
    currentBit++;
    if(currentBit > 7 )
    {
        currentBit=0;
        *out<<currentByte;
        currentByte = 0;
    }

}
