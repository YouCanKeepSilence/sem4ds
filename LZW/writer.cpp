#include "writer.h"

Writer::Writer()
{
    currentBit=0;
    currentByte=0;
    out=NULL;
}

Writer::~Writer()
{
    this->detach();
}

void Writer::attach(std::ostream *out)
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

std::ostream *Writer::getStream()
{
    return this->out;
}

void Writer::writeCode(unsigned short code)
{
    if(!out)
    {
        std::cerr<<"No out thread attached "<<std::endl;
        return;
    }
//    std::cout<<"Пишу "<<code<<std::endl;
    for(int i=0; i < 8 + state; i++)
    {
        writeNextBit(code & (0b0000000000000001 << i));
    }

}

void Writer::flush()
{
    if(!out)
    {
        std::cerr<<"No out thread attached "<<std::endl;
        return;
    }
    if(currentBit!=0)
    {
//        std::cout<<"flushing "<<currentByte<<std::endl;
        out->put(currentByte);
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
        currentByte = currentByte | (0b00000001 << currentBit);
    }

    currentBit++;
    if(currentBit > 7 )
    {
        currentBit=0;
//        for(int i=0; i<8 ;i++)
//        {
//            if(currentByte & (0b10000000 >> i))
//                std::cout<<1;
//            else
//                std::cout<<0;
//        }
//        std::cout<<std::endl;

        currentByte = 0;
    }

}
