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

void Table::add(std::__1::string data)
{
    if(lastIndex > maxSize)
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

bool Table::contains(std::__1::string data)
{
    return hashTable.contains(data);
}

bool Table::contains(unsigned short id)
{
    return lastIndex >= id;
}

unsigned short Table::getIndex(std::__1::string key)
{
    if(hashTable.contains(key))
    {
        return hashTable.get(key);
    }
    else
    {
        std::cerr<<"Нет такого элемента вернется 0"<<std::endl;
        return 0;
    }

}

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

std::__1::string Table::getString(unsigned short id)
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
