#include "node.h"

Node::Node() : field(),
    parent(NULL)
{

}

Node::Node(const Field &fi, Node *parent)
{
    this->field = fi;
    this->parent = parent;
}

Field Node::getField() const
{
    return this->field;
}

const Node *Node::getParent() const
{
    return this->parent;
}
