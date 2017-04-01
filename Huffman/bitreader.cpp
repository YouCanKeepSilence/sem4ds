#include "bitreader.h"

BitReader::BitReader()
{
    m_fromFile=NULL;
    m_currentBit=7;
    m_currentByte=0;
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
