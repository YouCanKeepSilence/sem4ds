#include "bitreader.h"
#include <iostream>
#include <QtEndian>
BitReader::BitReader()
{
    m_fromFile=NULL;
    m_currentBit=7;
    m_currentByte=0;
}
BitReader::~BitReader()
{

}

bool
BitReader::readHeader(uint32_t *symbols)
{
    if(m_fromFile==NULL)
    {
        throw new std::exception;
        return false;
    }
    char c[4];
    uint32_t buf;
    m_fromFile->read(c,4);
    std::string str(c);
    if(!str.compare("HUFF"))
    {
        std::cout<<"MyFile"<<std::endl;
    }
    else
    {
        std::cout<<"Not a HUFF file"<<std::endl;
        throw new std::exception;
    }
    for(int i=0; i<256 ; i++)
    {
        m_fromFile->read((char*)&buf,4);
        symbols[i]=qFromBigEndian(buf);;
    }
}

void
BitReader::detach()
{
    m_fromFile=NULL;
    m_currentBit=7;
    m_currentByte=0;
}

void
BitReader::attach(std::ifstream *fromFile)
{
    m_fromFile=fromFile;
    m_currentBit=7;
    m_currentByte=0;
}

std::ifstream *BitReader::getStream() const
{
    return m_fromFile;
}

int
BitReader::readNextBit()
{
    if(m_fromFile==NULL)
    {
        throw new std::exception;
        return -1;
    }

    m_currentBit++;

    if(m_currentBit > 7) {
            (*m_fromFile) >> m_currentByte;
            if(m_fromFile->eof()) {
                throw new std::exception();
            }
            m_currentBit = 0;
        }

        return (m_currentByte & (0x80 /* 0b1000000 */ >> m_currentBit)) ? 1 : 0;//сдвигаем на 7 бит влево и пересекаем с текущим байтом.
}
