#include "binarywriter.h"
#include <sstream>
#include <fstream>
#include <QtEndian>
using namespace std;
BinaryWriter::BinaryWriter()
{

}
void
BinaryWriter::flushToFile(ofstream *toFile, unsigned char s_byte)
{
//    unsigned char byte=0b00000000;
//    unsigned char mask=0b10000000;
//    for(unsigned int i=0; i<s_byte.length(); i++)
//    {
//        if(s_byte[i]=='0')
//        {
//            continue;
//        }
//        if(s_byte[i]=='1')
//        {
//            byte=byte | (mask>>i);
//        }
//    }
//    cout<<s_byte.length()<<endl;
    cout<<s_byte<<endl;
    cout<<"byte "<<(int)s_byte<<endl;
    toFile->write((char*)&s_byte,1);

}

void
BinaryWriter::binaryWrite(std::ofstream *toFile, std::ifstream *fromFile, std::__cxx11::string *encodingTable)
{
    if(toFile==NULL || fromFile==NULL || encodingTable==NULL)
    {
        throw "No pointer to streams or encoding table";
        return;
    }
    int counter=0;
    unsigned char c;
    unsigned char byteBuf=0b00000000;
    stringstream ss;
    while(1)
    {

        unsigned char bufMask=0b10000000;
        c=fromFile->get();
        if(fromFile->eof())
        {
            if(byteBuf!=0)//Если исходный файл кончился , флашим и уходим.
            {
                BinaryWriter::flushToFile(toFile,byteBuf);

            }
            break;
        }
        for(unsigned int i=counter; i < encodingTable[c].length(); i++)
        {

            counter++;
            if(encodingTable[(int)c][i]=='0')
            {
//                continue;
            }
            if(encodingTable[(int)c][i]=='1')
            {
                byteBuf = byteBuf | (bufMask >> i % 8);
            }
            if(counter>7)
            {
//                string currentByte=ss.str();
//                cout<<"path "<<encodingTable[c]<< " : ";

                BinaryWriter::flushToFile(toFile,byteBuf);
                byteBuf=0b00000000;
//                ss.str("");
//                ss.clear();
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
        throw "no input stream of symbols array";
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
