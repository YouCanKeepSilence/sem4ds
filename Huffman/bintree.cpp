#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;
BinTree::BinTree(uint32_t weight, unsigned char symbol, BinTree *parent)
{
    m_parent=parent;
    m_leftChild=NULL;
    m_rightChild=NULL;
    m_weight=weight;
    m_symbol=symbol;
}

BinTree::~BinTree()
{
}

BinTree*
BinTree::toChild(bool direction)
{
    return (direction) ? (m_rightChild) : (m_leftChild);
}

BinTree*
BinTree::toParent()
{
    return m_parent;
}

void
BinTree::setParent(BinTree *parent)
{
    m_parent=parent;
}

void
BinTree::addChild(uint32_t weight, unsigned char symbol, bool direction)
{
    direction ? m_rightChild=new BinTree(weight,symbol, this) : m_leftChild=new BinTree(weight,symbol,this);
}

unsigned char BinTree::getSymbol()
{
    return m_symbol;
}

uint32_t
BinTree::getWeight()
{
    return m_weight;
}

void
BinTree::recalcWeight()
{

    if(m_leftChild && m_rightChild)
    {
        m_weight = m_leftChild->m_weight + m_rightChild->m_weight;
    }

}

void
BinTree::addChild(BinTree *child,BinTree * parent, bool direction)
{
    child->setParent(parent);
    direction ? parent->m_rightChild=child : parent->m_leftChild=child;
}

void
BinTree::setWeight(uint32_t weight)
{
    m_weight=weight;
}

void
BinTree::countSymbols(uint32_t *symbols, string filename)
{
    int counter=0;
    ifstream fromFile;
    fromFile.open(filename);
    if(!fromFile.is_open())
    {
        cout<<"Не удалось открыть файл "+filename<<endl;
        exit(0);
    }
    for(int i=0;i<256;i++)
    {
        symbols[i]=0;
    }
    while(1)
    {
        unsigned char c;
        c=fromFile.get();
        if(fromFile.eof())
        {
            cout<<counter<<endl;
            break;
        }
        counter++;
        symbols[(int)c]++;
    }
    fromFile.close();
}

std::list<BinTree*>
BinTree::createForest(uint32_t *symbols)
{
    list<BinTree*> trees;
    for(int i=0; i<256; i++)
    {
        BinTree * tree = new BinTree(symbols[i], i);
        trees.push_back(tree);
    }
    return trees;
}

BinTree*
BinTree::createHuffTree(uint32_t * symbols)
{
    BinTree * root;
    list<BinTree*> forest=BinTree::createForest(symbols);
    ofstream debug;
    debug.open("tree-debug.txt");
    list<BinTree*>::iterator i;
    while(1)
    {
        list<BinTree*>::iterator first = forest.begin();
        list<BinTree*>::iterator second = forest.begin();
        for( i=forest.begin(); i != forest.end(); ++i)
        {
            if(((*first)->getWeight() > (*i)->getWeight()))
            {
                first = i;
            }
        }
        if(first==second)
        {
            second++;
        }
        for( i=forest.begin(); i != forest.end(); ++i)
        {
            if(((*second)->getWeight() > (*i)->getWeight()) && (i != first) )
            {
                second = i;
            }
        }
        root = new BinTree();

        root->addChild(*first,root,0);
        root->addChild(*second,root,1);
        debug<<"Объединяем: "<<(int)(*first)->getSymbol()<<" и "<<(int)(*second)->getSymbol()<<endl<<"Их весы: "<<(*first)->getWeight()
            <<" и "<<(*second)->getWeight()<<endl;
        int weight=(*first)->getWeight() + (*second)->getWeight();
//        debug<<" Итоговый вес : "<<weight<<endl;
        root->setWeight(weight);

        forest.erase(first);
        forest.erase(second);
        forest.push_front(root);

        if(forest.size()==1)
        {
            root=forest.front();
            forest.clear();
            cout<<root->getWeight()<<endl;
            debug.close();
            break;
        }

    }
    return root;
}

void
BinTree::createEncoding(string *symbolsEncoding, BinTree *root)
{
    string way;
    if(!root->toChild(0) && !root->toChild(1))
    {
        cout<<"Дерево не имеет детей"<<endl;
        exit(1);
    }
    char c=0;
    while(1)
    {
        if(way.empty() && c=='1' && root->toParent() == NULL)
        {
            cout<<"Tree completed"<<endl;
            break;
        }
        if((!root->toChild(0) && !root->toChild(1)) || c=='1')
        {
            c=way.back();
            way.pop_back();
            root=root->toParent();
        }
        else if(root->toChild(0) && c!='0')
        {
            root=root->toChild(0);
            way.push_back('0');
            continue;
        }
        else if(root->toChild(1) && c!='1')
        {
            root=root->toChild(1);
            way.push_back('1');
            symbolsEncoding[root->getSymbol()] = way;
            continue;
        }
    }
}
