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
    int * symbols = new int[256];
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
    cout<<"end"<<endl;
    return 1;
}
