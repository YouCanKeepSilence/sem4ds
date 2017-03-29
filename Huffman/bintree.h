#ifndef BINTREE_H
#define BINTREE_H
#include <string>

class BinTree
{
public:
    BinTree(int weight=0,unsigned char * symbol=NULL,BinTree * parent=NULL);
    void addChild(int weight,unsigned  char * symbol,bool direction);// Надо ли?
    void addChild(BinTree * child,bool direction);
    void setWeight(int weight);
    int getWeight();
    unsigned char *getSymbol();
    static void countSymbols(int * symbols, std::string filename);
    BinTree * toChild(bool direction);//Вернет NULL если нет такого ребенка. 0 - левый , 1 - правый
    BinTree * toParent();// Вернет NULL если это самый корень дерева

private:
    BinTree * m_parent;
    BinTree * m_rightChild;
    BinTree * m_leftChild;
    int m_weight;
    unsigned char * m_symbol;

};

#endif // BINTREE_H
