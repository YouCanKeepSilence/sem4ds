
#include <iostream>
#include "mytable.h"
typedef std::vector<std::string>::iterator stringIterator ;
typedef std::vector<NElement*>::iterator elemIterator;
MyTable::MyTable(unsigned int maxSize) :
    indexOfLast(0),
    maxSize(maxSize),
    oldHash(-1)
{
    strings.resize(maxSize);
    hash.resize(maxSize);
    for(elemIterator it= hash.begin(); it != hash.end() ; it++)
    {
        *it = NULL;
    }
    for(int i = 0 ; i < 256 ; i++)
    {
        std::string str;
        str.push_back((char)i);
        this->add(i,-1,str);
    }
}

MyTable::~MyTable()
{
    for(elemIterator it = hash.begin() ; it != hash.end() ; it++)
    {
        delete *it;
    }
    hash.clear();
    strings.clear();
}

bool MyTable::contains(unsigned short id)
{
    if(id < indexOfLast)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyTable::contains(int parent, unsigned char sym)
{
    unsigned int hashNum = getHash(sym,parent);
    NElement * item = hash.at(hashNum);
    if(!item)
    {
        return false;
    }
    while(item && !(item->parentId==parent && item->symbol==sym))
    {
        item = item->next;
    }
    if(item)
    {
        parentIndex = item->id;
        return true;
    }
    else
    {
        return false;
    }

}

void MyTable::add(unsigned char lastSymbol , int parent , std::string data)
{
    if(indexOfLast >= maxSize)
    {
        parentIndex=lastSymbol;
        return;
    }
    strings[indexOfLast] = data;
    //add to hash
    unsigned int hashNum = getHash(lastSymbol,parent);
    NElement * item = hash.at(hashNum);
    if(item)
    {
        while(1)
        {
            if(!item->next)
            {
                item->next = new NElement(parent,lastSymbol,indexOfLast);
                break;
            }
            item=item->next;
        }
    }
    else
    {
        hash[hashNum] = new NElement(parent,lastSymbol,indexOfLast);
    }
    parentIndex=lastSymbol;
    indexOfLast++;
}

unsigned int MyTable::getSize()
{
    return indexOfLast;
}

unsigned int MyTable::getMaxSize()
{
    return maxSize;
}

unsigned short MyTable::getCurrentParentIndex()
{
    return parentIndex;
}

void MyTable::resetOldHash()
{
    oldHash = -1;
}

unsigned int MyTable::getHash(unsigned char symbol, int parent)
{
    if(oldHash != -1)
    {
        return (unsigned int)oldHash % this->hash.capacity();
    }
    unsigned int hash;// = 2139062143;
    hash = symbol ^ parent;//37  * key.length() * sym * parentIndex ;
    hash = hash % this->hash.capacity();
    return hash;

}

NElement::NElement(int parent,unsigned char symbol, unsigned int id)
{
    this->parentId = parent;
    this->symbol = symbol;
    this->id = id;
    this->next = NULL;
}
