#include "node.h"

Node::Node() : field(),
    parent(NULL)
{

}

Node::Node(const Field &fi, const Node *parent)
{
    this->field = fi;
    this->parent = parent;
}

Field Node::getField()
{
    return this->field;
}
