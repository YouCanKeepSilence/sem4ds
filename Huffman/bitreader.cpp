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

}
