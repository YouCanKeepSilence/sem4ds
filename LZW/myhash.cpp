#include "myhash.h"

MyHash::MyHash(int size)
{
    table.reserve(size);
    for(std::vector<int>::iterator it = table.begin() ; it!=table.end(); it++)
    {
        *it=-1;
    }

}

int MyHash::getHash(std::string str)
{
    int hash = 666;
//    hash = hash >> str.length();
//    hash *= str[0] * str[str.length()-1];
//    hash /= (str.length() +3) ;
    for(int i=0; i<str.length() ; i++)
    {
        hash = 13*hash + str[i];
    }

    hash = hash % table.capacity();

    return hash;
}

void MyHash::add(std::string key, uint16_t id)
{
    int place = getHash(key);
    std::vector<int>::iterator it;
    it = table.begin() + place;
    if(table.at(place) != -1)
    {
        while(*it!=-1 || it == table.end())
        {
            it++;
        }
        *it = id;
    }
}
