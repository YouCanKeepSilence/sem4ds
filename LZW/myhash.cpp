#include "myhash.h"
#include <iostream>
MyHash::MyHash(int size)
{
    table.resize(size);
    for(std::vector<Element*>::iterator it = table.begin() ; it < table.end(); it++)
    {
        *it=NULL;
    }


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
    unsigned int hash = 2139062143;
    for(unsigned int i=0; i<key.length() ; i++)
    {
        hash = 37*hash + key[i];
    }

    hash = hash % table.capacity();
//    std::cout<<hash<<std::endl;
    return hash;
}

void MyHash::add(std::string key, unsigned short id)
{
    int place = getHash(key);
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
