#include <iostream>
#include "bintree.h"
#include <deque>
#include <vector>
using namespace std;
BinTree* createHuffTree(deque<BinTree*>& trees)
{
    BinTree * root;
    deque<BinTree*>::iterator index;
    unsigned char * bufchar=NULL;
    while(1)
    {
        int weight;
        weight = 0;
        root = new BinTree();
        for(int j=0; j<2 ; j++)
        {

            int bufsize;
            bufsize = (trees.front())->getWeight();
            index=trees.begin();
            for(deque<BinTree*>::iterator i=trees.begin();i<trees.end();i++)
            {
                if(bufsize>(*i)->getWeight())
                {
                    if(bufchar)
                    {
                        if(*bufchar = *((*i)->getSymbol()))
                        {
                            continue;
                        }
                    }
                    index = i;
                    bufsize=(*i)->getWeight();
                    bufchar=(*i)->getSymbol();
                }
            }
            root->addChild(*index,root,j);
            trees.erase(index);
            weight+=bufsize;
        }
        root->setWeight(weight);
        trees.push_front(root);
        if(trees.size()==0)
            break;

    }
    return root;
}
bool checkChar(unsigned char& symbol, BinTree * root)
{
    if(root)
    {
        if(root->getSymbol())
        {
            if(symbol==*(root->getSymbol()))
            {
                return true;
            }
        }
    }
    return false;
}

string findChar(unsigned char symbol,BinTree * root)
{
    string way;
    while(1)
    {
        if(!root->toChild(0))
        {
            break;
        }
        root=root->toChild(0);
        way.push_back(0);
    }
//    root=root->toChild(0);
    while(1)
    {
        if(checkChar(symbol,root))
        {
            return way;
        }
        if(root->toChild(1))
        {
            root=root->toChild(1);
        }
        else
        {
            root=root->toParent();
            way.pop_back();
        }
    }
    return way;
}

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        cout<<"Не введено имя входного файла"<<endl;
        return 0;
    }
    deque<BinTree*> trees;
    BinTree * root;
    string filename=argv[1];
    int * symbols = new int[256];
    BinTree::countSymbols(symbols,filename);

    for(int i=0; i<256; i++)
    {
        unsigned char * c = new unsigned char(i);
        BinTree * tree = new BinTree(symbols[i], c);
        trees.push_back(tree);
    }

    root=createHuffTree(trees);
    cout<<"result "<<findChar(32,root)<<endl;
    cout<<"end"<<endl;
    return 1;
}
