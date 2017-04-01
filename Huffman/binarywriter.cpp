#include "binarywriter.h"
#include <sstream>
#include <fstream>
#include <QtEndian>
using namespace std;
BinaryWriter::BinaryWriter()
{

}
void
BinaryWriter::flushToFile(ofstream *toFile, string s_byte)
{
    unsigned char byte=0b00000000;
    unsigned char mask=0b10000000;
    for(unsigned int i=0; i<s_byte.length(); i++)
    {
        if(s_byte[i]=='0')
        {
            continue;
        }
        if(s_byte[i]=='1')
        {
            byte=byte | (mask>>i);
        }
    }
    cout<<s_byte<<endl;
    cout<<"byte "<<(int)byte<<endl;
    toFile->write((char*)&byte,1);

}

void
BinaryWriter::binaryWrite(std::ofstream *toFile, std::ifstream *fromFile, std::__cxx11::string *encodingTable)
{
    if(toFile==NULL || fromFile==NULL || encodingTable==NULL)
    {
        throw new std::exception;
        return;
    }
    int counter=0;
    unsigned char c;
    stringstream ss;
    while(1)
    {
        c=fromFile->get();
        if(fromFile->eof())
        {
            if(ss.str().length()!=0)//Если исходный файл кончился , флашим и уходим.
            {
                string currentByte=ss.str();
                flushToFile(toFile,currentByte);

            }
            break;
        }
        for(unsigned int i=0; i < encodingTable[c].length(); i++)
        {

            counter++;
            if(encodingTable[(int)c][i]=='0')
                ss<<0;
            if(encodingTable[(int)c][i]=='1')
                ss<<1;
            if(counter==8)
            {
                string currentByte=ss.str();
                flushToFile(toFile,currentByte);
                ss.str("");
                ss.clear();
                counter=0;
            }
        }
    }
}

void
BinaryWriter::writeHeader(ofstream *toFile, uint32_t *symbols)
{
    if(toFile==NULL || symbols == NULL)
    {
        throw new std::exception;
        return;
    }
    *toFile<<"HUFF";
    uint32_t buf;
    for(int i=0; i<256; ++i)
    {
        buf=symbols[i];
        buf=qToBigEndian(buf);
        (*toFile).write((char*)&buf,4);
    }
}
