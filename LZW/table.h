#ifndef TABLE_H
#define TABLE_H
#include "myhash.h"
#include <string>
class Table
{
public:
    Table(unsigned short maxSize=256);
    void init();
    void add(std::string data);
    bool contains(std::string data);
    unsigned short getIndex(std::string key);
private:
    unsigned short maxSize;
    unsigned short lastIndex;
    std::string * table;
    MyHash hashTable;

};

#endif // TABLE_H
