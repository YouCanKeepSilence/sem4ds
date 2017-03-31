#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;
BinTree::BinTree(int weight, unsigned char symbol, BinTree *parent)
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
BinTree::addChild(int weight, unsigned char symbol, bool direction)
{
    direction ? m_rightChild=new BinTree(weight,symbol, this) : m_leftChild=new BinTree(weight,symbol,this);
}

unsigned char BinTree::getSymbol()
{
    return m_symbol;
}

int
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
//    parent->recalcWeight();
}

void
BinTree::setWeight(int weight)
{
    m_weight=weight;
}

void
BinTree::countSymbols(int *symbols, string filename)
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
}
