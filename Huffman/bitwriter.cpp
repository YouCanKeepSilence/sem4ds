#include "bitwriter.h"
#include <sstream>
#include <fstream>
#include <QtEndian>
using namespace std;
BitWriter::BitWriter()
{
    m_currentBit=0;
    m_currentByte=0;
    m_toFile=NULL;
}
void
BitWriter::attach(ofstream *toFile)
{
    m_toFile=toFile;
    m_currentBit=0;
    m_currentByte=0;
}
void
BitWriter::writeNextBit(bool bit)
{
    if(bit)
    {
        m_currentByte = m_currentByte | (0b10000000 >> m_currentBit);
    }
    m_currentBit++;
    if(m_currentBit > 7)
    {
        m_currentBit=0;
        m_toFile->write(&m_currentByte,1);
        m_currentByte=0;
    }
}

void
BitWriter::detach()
{
    m_toFile=NULL;
    m_currentBit=0;
    m_currentByte=0;
}

void
BitWriter::flushToFile()
{
    if(m_currentBit!=0)
    {
        if(m_toFile)
        {
            m_toFile->write(&m_currentByte,1);
        }
        m_currentBit=0;
        m_currentByte=0;
    }
}

void
BitWriter::binaryWrite(std::ifstream *fromFile, std::string *encodingTable)
{
    if(m_toFile==NULL || fromFile==NULL || encodingTable==NULL)
    {
        throw "No pointer to streams or encoding table";
        return;
    }
    unsigned char c;
    while(1)
    {
        fromFile->read((char*)&c,1);
        if(fromFile->eof())
        {
            //Если исходный файл кончился , флашим и уходим.
            flushToFile();
            break;
        }
        for(unsigned int i=0; i < encodingTable[c].length(); i++)
        {

            writeNextBit(encodingTable[(int)c][i]=='1');
        }
    }
}

void
BitWriter::writeHeader(uint32_t *symbols)
{
    if(m_toFile==NULL || symbols == NULL)
    {
        throw "No input file";
    }
    if(symbols==NULL)
    {
        throw "No symbols array";
    }
    m_toFile->write("HUFF",4);
    uint32_t buf;
    for(int i=0; i<256; ++i)
    {
        buf=symbols[i];
        buf=qToBigEndian(buf);
        m_toFile->write((char*)&buf,4);
    }
}
