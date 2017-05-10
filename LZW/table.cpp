#include "table.h"
#include <iostream>
Table::Table(unsigned int maxSize):
    maxSize(maxSize),
    lastIndex(0),
    realSize(0),
    hashTable(maxSize*2),
    table(new std::string[maxSize])
{
    this->init();
}

void Table::init()
{
    for(int i=0; i < 256; i++)
    {
        char c(i);
        std::string str;
        str.push_back(c);
        table[lastIndex]=str;
        lastIndex++;
        realSize++;
    }
    hashTable.init();

}

void Table::add(std::string data)
{
    if(lastIndex +1 > maxSize)
    {
//        std::cerr<<"превышен размер таблицы."<<std::endl;
        return;
    }
    table[lastIndex] = data;
    hashTable.add(data , lastIndex);
    if(lastIndex < maxSize)
    {
        lastIndex ++ ;
        realSize++;
    }

}


bool Table::contains(std::string data)

{
    return hashTable.contains(data);
}

bool Table::ifContainsGetElseAdd(std::string key, unsigned short &oldId, unsigned short &newId)
{

}

bool Table::contains(unsigned short id)
{
    return lastIndex >= id;
}

unsigned short Table::getIndex(std::string key)
{
    return hashTable.get(key);
}

//bool Table::containsAndGetIndex(std::__1::string key, unsigned short &id)
//{
//    if(hashTable.containsAndGet(key,id))
//    {
//        return true;
//    }
//    else
//    {
////        std::cerr<<"Нет такого элемента вернется 0"<<std::endl;
//        return false;
//    }

//}

unsigned short Table::getLastIndex()
{
    return lastIndex;
}

unsigned int Table::getRealSize()
{
    return realSize;
}

unsigned int Table::getMaxSize()
{
    return maxSize;
}

std::string Table::getString(unsigned short id)
{
    if(id < lastIndex)
    {
        return table[id];
    }
    else
    {
//        std::cerr<<"нет такого id";
        return "";
    }

}
