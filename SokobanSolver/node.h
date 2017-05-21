#ifndef NODE_H
#define NODE_H
#include "field.h"

class Node
{
public:
    Node();
    Node(const Field &fi, Node *parent);
    Field getField() const;
    const Node *getParent() const;
private:
    Field field;
    Node * parent;
};

#endif // NODE_H
