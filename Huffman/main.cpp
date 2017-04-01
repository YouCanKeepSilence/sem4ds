#include <iostream>
#include "bintree.h"
#include "bitreader.h"
#include "binarywriter.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    system("clear");
    if(argc!=2)
    {
        cout<<"Не введено имя входного файла"<<endl;
        return 0;
    }

    string filename=argv[1];
    uint32_t symbols[256];
    BinTree::countSymbols(symbols,filename);

    BinTree *root=BinTree::createHuffTree(symbols);

    string strmass[256];
    BinTree::createEncoding(strmass,root);

    ifstream is;
    is.open(filename);
    ofstream os;
    os.open("13.txt" , ios_base::binary);
    BinaryWriter::writeHeader(&os,symbols);
    BinaryWriter::binaryWrite(&os, &is, strmass);
    is.close();
    os.close();
    is.open("13.txt",ios_base::binary);
    uint32_t symbol1[256];
    BitReader rr;
    rr.attach(&is);
    rr.readHeader(symbol1);
    for(int i=0; i<8 ; i++)
    {
        cout<<rr.readNextBit();
    }
//    cout<<"end"<<endl;
    return 1;
}
