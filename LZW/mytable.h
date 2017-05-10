#ifndef MYTABLE_H
#define MYTABLE_H
#include <string>
#include <vector>

struct NElement;
class MyTable
{
public:
    MyTable(unsigned int maxSize = 256);
    bool contains(unsigned short id);
    bool contains(std::string key);
    void add(std::string data);
    unsigned int getSize();
    unsigned int getMaxSize();
    unsigned short get(std::string data);
    unsigned short getCurrentParentIndex();
private:
    unsigned int getHash(std::string key);
    void init();
    unsigned int indexOfLast;
    unsigned int maxSize;
    unsigned int parentIndex;
    std::vector<std::string> strings;
    std::vector<NElement*> hash;

};

struct NElement
{
    NElement(int parent, char symbol, unsigned int id);
    int parentId;
    char symbol;
    unsigned int id;
    NElement * next;
};

#endif // MYTABLE_H
