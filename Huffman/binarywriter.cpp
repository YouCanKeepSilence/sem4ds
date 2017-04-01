#include "binarywriter.h"
#include <sstream>
#include <fstream>
#include <QtEndian>
using namespace std;
BinaryWriter::BinaryWriter()
{

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
                toFile->write(ss.str().c_str(),1);
            }
            break;
        }
        for(unsigned int i=0; i < encodingTable[c].length(); i++)
        {

            counter++;
            cout<<counter<<endl;
            if(encodingTable[(int)c][i]=='0')
                ss<<0;
            if(encodingTable[(int)c][i]=='1')
                ss<<1;
            if(counter==8)
            {
                toFile->write(ss.str().c_str(),1);
                ss.str("");
                ss.clear();
                counter=0;
            }
        }
    }
}

void
BinaryWriter::writeHeader(ofstream *toFile, int *symbols)
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
        (*toFile).write((char*)&buf,sizeof(uint32_t));
    }
}
