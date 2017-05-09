#ifndef MYHASH_H
#define MYHASH_H

#include <string>
#include "element.h"
#include <vector>
class MyHash
{
public:
    MyHash(int size=1024);
    void init();
    void add(std::string key,unsigned short id);
    bool ifContainsGetElseAdd(std::__1::string key, unsigned short &oldId, unsigned short &newId);
    bool contains(std::string key);
    unsigned short get(std::string key);
private:
    unsigned int getHash(std::string key);
    unsigned int previousHash;
    std::vector<Element*> table;
};

#endif // MYHASH_H
