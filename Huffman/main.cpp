#include <iostream>
#include "bintree.h"
#include "bitreader.h"
#include "binarywriter.h"
#include <fstream>

using namespace std;
void archive(string inputFile,string outFile)
{
    uint32_t symbols[256];
    BinTree::countSymbols(symbols,inputFile);

    BinTree *root=BinTree::createHuffTree(symbols);

    string strmass[256];
    BinTree::createEncoding(strmass,root);


    ifstream input;
    ofstream out;
    input.open(inputFile);
    out.open(outFile , ios_base::binary);
    BinaryWriter writer;
    writer.attach(&out);
    writer.writeHeader(symbols);
    writer.binaryWrite( &input, strmass);
    input.close();
    out.close();
}

void unarchive(ofstream * toFile , ifstream * fromFile)
{
    uint32_t symbols[256];
    BitReader rr;
    rr.attach(fromFile);
    try
    {
        rr.readHeader(symbols);
    }
    catch(const char * ex)
    {
        cout<<ex<<endl;
    }

    BinTree * root=BinTree::createHuffTree(symbols);
    BinTree * realRoot = root;
    unsigned int step;
    char symbol;
    while(1)
    {
        try
        {
            if(!root->toChild(0) && !root->toChild(1))
            {
                symbol = root->getSymbol();
                *toFile<<symbol;
                root=realRoot;
                continue;
            }
            step = rr.readNextBit();
            if(root->toChild(step))
            {
                root=root->toChild(step);
            }

        }
        catch(const char * ex)
        {
            cout<<ex<<endl;
            break;
        }
    }


}

int main(int argc, char *argv[])
{
    system("clear");
    if(argc!=3)
    {
        cout<<"Not enough files"<<endl;
        return 0;
    }
    string input;
    string out;
    input=argv[1];
    out=argv[2];
    archive(input,out);
//    ifstream is;
//    ofstream os;
//    is.open("huff.txt",ios_base::binary);
//    os.open("unzip.txt");
//    unarchive(&os,&is);
    cout<<"end"<<endl;
    return 1;
}
