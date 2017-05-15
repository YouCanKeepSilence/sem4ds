#ifndef MYTABLE_H
#define MYTABLE_H
#include <string>
#include <vector>

struct NElement;
class MyTable
{
public:
    MyTable(unsigned int maxSize = 256);
    ~MyTable();
    bool contains(unsigned short id);
    bool contains(int parent, unsigned char sym);
    void add(unsigned char lastSymbol, int parent, std::string data);
    unsigned int getSize();
    unsigned int getMaxSize();
    unsigned short getCurrentParentIndex();
    void resetOldHash();
private:
    unsigned int getHash(unsigned char symbol , int parent);
    void init();
    unsigned int indexOfLast;
    unsigned int maxSize;
    unsigned int parentIndex;
    long oldHash;
    std::vector<std::string> strings;
    std::vector<NElement*> hash;
//    NElement * forNew;

};

struct NElement
{
    NElement(int parent, unsigned char symbol, unsigned int id);
    int parentId;
    unsigned char symbol;
    unsigned int id;
    NElement * next;
};

#endif // MYTABLE_H
