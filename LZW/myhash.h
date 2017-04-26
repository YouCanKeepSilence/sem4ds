#ifndef MYHASH_H
#define MYHASH_H

#include <string>
#include <vector>
class MyHash
{
public:
    MyHash(int size=1024);
    int getHash(std::string str);
    void add(std::string key,uint16_t id);
private:
    std::vector<int> table; // TODO Element but not int
};

#endif // MYHASH_H
