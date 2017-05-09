#ifndef TABLE_H
#define TABLE_H
#include "myhash.h"
#include <string>
class Table
{
public:
    Table(unsigned int maxSize=256);
    void init();
    void add(std::string data);
    bool containsAndGetIndex(std::__1::string key, unsigned short &id);
    bool contains(unsigned short id);
    bool contains(std::__1::string data);
    bool ifContainsGetElseAdd(std::string key, unsigned short &oldId, unsigned short &newId);
    unsigned short getIndex(std::string key);
    unsigned short getLastIndex();
    unsigned int getRealSize();
    unsigned int getMaxSize();
    std::string getString(unsigned short id);
private:
    unsigned int realSize;
    unsigned int maxSize;
    unsigned short lastIndex;
    std::string * table;
    MyHash hashTable;

};

#endif // TABLE_H
