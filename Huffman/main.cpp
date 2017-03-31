#include <iostream>
#include "bintree.h"
#include "bitreader.h"
#include <vector>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <list>
#include <netinet/in.h>
using namespace std;

BinTree* createHuffTree(list<BinTree*>& trees)
{
    BinTree * root;
    list<BinTree*>::iterator i;
    while(1)
    {
        list<BinTree*>::iterator first = trees.begin();
        list<BinTree*>::iterator second = trees.begin();

        if(first==second)
        {
            second++;
        }
        for( i=trees.begin(); i != trees.end(); ++i)
        {
            if(((*second)->getWeight() > (*i)->getWeight()) && (i != first) )
            {
                second = i;
            }
        }
        root = new BinTree();
        root->addChild(*first,root,0);
        root->addChild(*second,root,1);

        int weight=(*first)->getWeight() + (*second)->getWeight();

        root->setWeight(weight);

        trees.erase(first);
        trees.erase(second);
        trees.push_front(root);

        if(trees.size()==1)
        {
            root=trees.front();
            cout<<root->getWeight()<<endl;
            break;
        }

    }
    return root;
}



void createEncoding(string *symbolsEncoding, BinTree * root)
{
    stringstream way;
    string bufway;
    if(!root->toChild(0) && !root->toChild(1))
    {
        cout<<"Дерево не имеет детей"<<endl;
        exit(1);
    }
    char c=0;
    while(1)
    {
        if(bufway.empty() && c=='1' && root->toParent() == NULL)
        {
            cout<<"Tree completed"<<endl;
            break;
        }
        if((!root->toChild(0) && !root->toChild(1)) || c=='1')
        {
            c=bufway.back();
            bufway.pop_back();
            root=root->toParent();
        }
        else if(root->toChild(0) && c!='0')
        {
            root=root->toChild(0);
            bufway.push_back('0');
            continue;
        }
        else if(root->toChild(1) && c!='1')
        {
            root=root->toChild(1);
            bufway.push_back('1');
            symbolsEncoding[root->getSymbol()] = bufway;
            continue;
        }
    }

}
void writeHeader(ofstream * toFile, int* symbols)
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
        buf=htonl(buf);
        (*toFile).write((char*)&buf,sizeof(uint32_t));
    }
}

void binaryWrite(ofstream * toFile, ifstream * fromFile, string* encodingTable)
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
            if(ss.str().length()!=0)
            {
                toFile->write(ss.str().c_str(),1);
            }
            break;
        }
        for(int i=0; i < encodingTable[c].length(); i++)
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

int main(int argc, char *argv[])
{
    system("clear");
    if(argc!=2)
    {
        cout<<"Не введено имя входного файла"<<endl;
        return 0;
    }
    list<BinTree*> trees;
    BinTree * root;
    string filename=argv[1];
    int * symbols = new int[256];
    BinTree::countSymbols(symbols,filename);

    for(int i=0; i<256; i++)
    {
        BinTree * tree = new BinTree(symbols[i], i);
        trees.push_back(tree);
    }


    root=createHuffTree(trees);
    string strmass[256];

    createEncoding(strmass,root);

    ifstream is;
    is.open(filename);
    ofstream os;
    os.open("13.txt" , ios_base::binary);
    writeHeader(&os,symbols);
    binaryWrite(&os, &is, strmass);
    is.close();
    cout<<"end"<<endl;
    return 1;
}
