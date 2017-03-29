#include <iostream>
#include "bintree.h"

#include <vector>
using namespace std;
BinTree* createHuffTree(vector<BinTree*>& trees)
{
    BinTree * root;
    vector<BinTree*>::iterator index;
    unsigned char * bufchar=NULL;
    while(1)
    {
        int weight;
        weight = 0;
        root = new BinTree();
        for(int j=0; j<2 ; j++)
        {

            int bufsize;
            BinTree * buf;
            bufsize = (trees[0])->getWeight();
            index=trees.begin();
            for(vector<BinTree*>::iterator i=trees.begin();i<trees.end();i++)
            {

                buf=*i;
                if(bufsize>buf->getWeight() && *bufchar!=*(buf->getSymbol()))
                {
                    index = i;
                    bufsize=buf->getWeight();
                    bufchar=buf->getSymbol();
                }
            }
//            cout<<"tut"<<endl;
//            buf=*index;
//            cout<<buf->getWeight()<<endl;
//            cout<<"tut1"<<endl;
            root->addChild(bufsize,bufchar,j);
//            cout<<"tut2"<<endl;
            trees.erase(index);

            weight+=bufsize;
//            cout<<"tut3";
        }
        root->setWeight(weight);
        trees.emplace(trees.begin(),root);
        if(trees.size()==1)
            break;

    }
    return root;
}

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        cout<<"Не введено имя входного файла"<<endl;
        return 0;
    }
    vector<BinTree*> trees;
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
//    trees.erase(trees.begin());

    root=createHuffTree(trees);
    cout<<"end"<<endl;
    return 1;
}
