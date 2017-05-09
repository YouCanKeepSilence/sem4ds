#include "myhash.h"
#include <iostream>
MyHash::MyHash(int size)
{
    table.resize(size);
    for(std::vector<Element*>::iterator it = table.begin() ; it < table.end(); it++)
    {
        *it=NULL;
    }
//    previousHash = 2139062143;

}

void MyHash::init()
{
    for(int i=0; i<256 ; i++)
    {
        char c = char(i);
        std::string str;
        str.push_back(c);
        this->add(str,i);
    }

}

unsigned int MyHash::getHash(std::string key)
{
    if(key.length()==1)
    {
        previousHash = 2139062143;
    }
//    previousHash = previousHash >> 1;
    previousHash *= 37 * key[key.length()-1];
    return previousHash % table.capacity();
}

void MyHash::add(std::string key, unsigned short id)
{
    unsigned int place = getHash(key);
    Element* elem = table.at(place);
    if(elem != NULL)
    {
        while(elem->getNext())
        {
            elem = elem->getNext();
        }
        elem->setNext(new Element(key, id));
    }
    else
    {
        table[place] = new Element(key,id);
    }
}

bool MyHash::ifContainsGetElseAdd(std::__1::string key,unsigned short &oldId, unsigned short &newId)
{
    unsigned int place = getHash(key);
    Element * elem = table.at(place);
    if(elem)
    {
        while(1)
        {
            if(elem->getData() == key)
            {
                oldId = elem->getId();
                return true;
            }
            else if(elem->getNext())
            {
                elem=elem->getNext();
                continue;
            }
            else
            {
                elem->setNext(new Element(key,newId));
                return false;
            }
        }

    }

    return false;
}

bool MyHash::contains(std::__1::string key)
{
    unsigned int place = getHash(key);
    Element * elem = table.at(place);
    if(elem)
    {
        if(elem->getData() == key)
        {
            return true;
        }
        else
        {
            while(elem->getNext())
            {
                elem=elem->getNext();
                if(elem->getData() == key)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

unsigned short MyHash::get(std::__1::string key)
{
    unsigned int place = getHash(key);
    Element * elem = table.at(place);
    if(elem)
    {
        if(elem->getData() == key)
        {
            return elem->getId();
        }
        else
        {
            while(elem->getNext())
            {
                elem=elem->getNext();
                if(elem->getData() == key)
                {
                    return elem->getId();
                }
            }
        }
    }
    std::cerr<<"Нет такого элемента вернется 0";
    return 0;
}
