#include "table.h"

Table::Table(unsigned short maxSize):
    maxSize(maxSize),
    lastIndex(0),
    hashTable(maxSize*2),
    table(new std::string[maxSize])
{

}
