#include <iostream>
#include "bintree.h"
#include <deque>
#include <stack>
#include <vector>
#include <sstream>
#include <queue>
#include <list>
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
//        trees.insert(trees.begin(),root);
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
bool checkChar(unsigned char& symbol, BinTree * root)
{
    if(root)
    {
        if(symbol==root->getSymbol())
        {
            return true;
        }

    }
    return false;
}


void createEncoding(vector<string>& symbolsEncoding, BinTree * root)
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
        if(bufway.length()==1 && bufway.back()=='1' && root->toParent() == NULL)
        {
            cout<<"Дерево пройдено"<<endl;
            break;
        }
        if((!root->toChild(0) && !root->toChild(1)) || c=='1')
        {
            cout<<"leave "<<endl;
            symbolsEncoding[root->getSymbol()]=bufway;
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
            continue;
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
    cout<<"qq"<<endl;

    vector<string> strmass;
    strmass.reserve(256);

    createEncoding(strmass,root);
    cout<<"end"<<endl;
    return 1;
}
