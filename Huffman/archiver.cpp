#include "archiver.h"
#include "bintree.h"
#include "bitwriter.h"
#include "bitreader.h"
#include <fstream>
using namespace std;
Archiver::Archiver()
{

}

void
Archiver::archive(string inputFile,string outFile)
{
    uint32_t symbols[256];
    BinTree::countSymbols(symbols,inputFile);

    BinTree *root=BinTree::createHuffTree(symbols);

    string strmass[256];
    BinTree::createEncoding(strmass,root);

//    ofstream debug;
//    debug.open("ways.txt");
//    for(int i=0; i<256 ;i++)
//    {
//        debug<<i<<": "<<strmass[i]<<endl<<endl;
//    }
//    debug.close();
    ifstream input;
    ofstream out;
    input.open(inputFile);
    out.open(outFile , ios_base::binary);
    if(!input.is_open())
    {
        throw "Error open input file";
    }
    if(!out.is_open())
    {
        throw "Error open output file";
    }
    BitWriter writer;
    writer.attach(&out);
    try
    {
        writer.writeHeader(symbols);
        writer.binaryWrite( &input, strmass);
    }
    catch(const char * ex)
    {
        input.close();
        out.close();
        throw ex;
    }

    input.close();
    out.close();
}

void
Archiver::unarchive(string inputFile,string outFile)
{
    ifstream fromFile;
    ofstream toFile;
    fromFile.open(inputFile , ios_base::binary);
    toFile.open(outFile);
    if(!fromFile.is_open())
    {
        throw "Error open input file";
    }
    if(!toFile.is_open())
    {
        throw "Error open output file";
    }
    uint32_t symbols[256];
    BitReader reader;
    reader.attach(&fromFile);
    try
    {
        reader.readHeader(symbols);
    }
    catch(const char * ex)
    {
        throw ex;
    }
//    ofstream debug;
//    debug.open("forest.txt");
    uint32_t symbolsCount=0;
    for(int i=0; i<256; i++)
    {
//        debug<<i<<" "<<symbols[i]<<endl;
        symbolsCount+=symbols[i];
    }
//    debug.close();
    BinTree * root=BinTree::createHuffTree(symbols);
    BinTree * realRoot = root;
    //debug
//    string strmass[256];
//    BinTree::createEncoding(strmass,root);

//    ofstream debug;
//    debug.open("ways.txt");
//    for(int i=0; i<256 ;i++)
//    {
//        debug<<i<<": "<<strmass[i]<<endl<<endl;
//    }
//    debug.close();
    //-debug
//    debug.open("readWays.txt");
    uint32_t counter=0;
//    string way;
    int step;
    unsigned char symbol;
    while(1)
    {
        if(!root->toChild(0) && !root->toChild(1))
        {

            symbol = root->getSymbol();

//            debug<<way<<" "<<(int)symbol<<endl;
//            way.clear();
            toFile<<symbol;
            counter++;
            if(counter==symbolsCount)
            {
                fromFile.close();
                toFile.close();
                break;
            }
            root=realRoot;
            continue;
        }
        try
        {
            step = reader.readNextBit();

        }
        catch(const char * ex)
        {
            throw ex;
            fromFile.close();
            toFile.close();
            break;
        }
        if(root->toChild(step))
        {
//            if(step==1)
//            {
//                way.push_back('1');
//            }
//            else if(step==0)
//            {
//                way.push_back('0');
//            }
            root=root->toChild(step);
        }
    }


}
