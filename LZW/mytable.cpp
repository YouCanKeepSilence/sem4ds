
#include <iostream>
#include "mytable.h"
typedef std::vector<std::string>::iterator stringIterator ;
typedef std::vector<NElement*>::iterator elemIterator;
MyTable::MyTable(unsigned int maxSize) :
    indexOfLast(0),
    maxSize(maxSize),
    oldHash(-1),
    forNew(NULL)


{
    strings.resize(maxSize);
    hash.resize(maxSize*2);
    for(elemIterator it= hash.begin(); it != hash.end() ; it++)
    {
        *it = NULL;
    }
    for(int i = 0 ; i < 256 ; i++)
    {
        std::string str;
        str.push_back((char)i);
        strings[i] = str;
        indexOfLast++;
        hash[i]=new NElement(-1,char(i), i);
    }
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

bool MyTable::contains(std::string key)
{
    unsigned int hashNum = getHash(key);
    NElement * item = hash.at(hashNum);
    if(!item)
    {
        return false;
    }
    while(1)
    {
        if(item)
        {
            if(strings.at(item->id) == key)
            {
                parentIndex = item->id;
                return true;
            }
        }
        else
        {

            return false;
        }
        forNew = item;
        item = item->next;

    }
}

void MyTable::add(std::string data)
{
    unsigned char lastSym = data[data.length()-1];
    if(indexOfLast >= maxSize)
    {
        parentIndex=lastSym;
        return;
    }
    strings[indexOfLast] = data;
    //add to hash
    unsigned int hashNum = getHash(data);
    NElement * item = hash.at(hashNum);
    if(item)//forNew)
    {
//        forNew->next = new NElement(parentIndex,lastSym,indexOfLast);
//        forNew = NULL;
        while(1)
        {
            if(!item->next)
            {
                item->next = new NElement(parentIndex,lastSym,indexOfLast);
                break;
            }
            item=item->next;
        }
    }
    else
    {
//        unsigned int hashNum = getHash(data);
        hash[hashNum] = new NElement(parentIndex,lastSym,indexOfLast);
    }
    parentIndex=lastSym;
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

unsigned short MyTable::get(std::string data)
{
    unsigned int hashNum = getHash(data);
    NElement * item = hash.at(hashNum);
    if(!item)
    {
        std::cerr<<"ОШИБКА НЕТ ТАКОЙ ЭЛЕМЕНТА"<<std::endl;
        return 0;
    }
    while(1)
    {
        if(item)
        {
            if(strings.at(item->id) == data)
            {
//                std::string str = strings[item->id];
                return item->id;
            }
        }
        else
        {
            std::cerr<<"ОШИБКА НЕТ ТАКОЙ ЭЛЕМЕНТА"<<std::endl;
            return 0;
        }
        item = item->next;

    }
}

unsigned short MyTable::getCurrentParentIndex()
{
    return parentIndex;
}

void MyTable::resetOldHash()
{
    oldHash = -1;
}

unsigned int MyTable::getHash(std::string key)
{
    if(oldHash != -1)
    {
        return (unsigned int)oldHash % this->hash.capacity();
    }
    if(key.length() == 1)
    {
        std::cout<<"HASH SINGLE "<<(unsigned short)(unsigned char)key[0]<<std::endl;
        return (unsigned char)key[0];
    }
    unsigned char sym = key[key.length()-1] + 1 ;
    unsigned int hash = 2139062143;
    hash *= sym ^ parentIndex;//37  * key.length() * sym * parentIndex ;
    hash = hash % this->hash.capacity();
    std::cout<<"HASH LONG "<<hash<<std::endl;
    return hash;

}

NElement::NElement(int parent, char symbol, unsigned int id)
{
    this->parentId = parent;
    this->symbol = symbol;
    this->id = id;
    this->next = NULL;
}
