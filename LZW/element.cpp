#include "element.h"


Element::Element(std::__1::string data, unsigned short id, Element *next):
id(id),
data(data),
next(next)
{

}

void Element::setData(std::__1::string &data)
{
    this->data=data;
}

void Element::setId(unsigned short &id)
{
    this->id=id;
}

void Element::setNext(Element *next)
{
    this->next=next;
}

std::__1::string Element::getData()
{
    return data;
}

unsigned short Element::getId()
{
    return id;
}

Element *Element::getNext()
{
    return next;
}
