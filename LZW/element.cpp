#include "element.h"


Element::Element(std::string data, unsigned short id, Element *next):
id(id),
data(data),
next(next)
{

}

void Element::setData(std::string &data)
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

std::string Element::getData()
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
