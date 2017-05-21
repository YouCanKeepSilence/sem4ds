#ifndef NODE_H
#define NODE_H
#include "field.h"

class Node
{
public:
    Node();
    Node(const Field &fi, const Node * parent);
    Field getField();
    const Node * getParent() const;
private:
    Field field;
    const Node * parent;
};

#endif // NODE_H
