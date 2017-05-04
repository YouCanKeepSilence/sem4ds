#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

class Element
{
public:

    Element(std::string data="",unsigned short id=0,Element * next=NULL);
    void setData(std::string &data);
    void setId(unsigned short &id);
    void setNext(Element* next);

    std::string getData();
    unsigned short getId();
    Element * getNext();
private:
    unsigned short id;
    std::string data;
    Element* next;
};

#endif // ELEMENT_H
