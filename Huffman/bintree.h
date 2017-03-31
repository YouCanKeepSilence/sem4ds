#ifndef BINTREE_H
#define BINTREE_H
#include <string>

class BinTree
{
public:
    BinTree(int weight=0,unsigned char symbol=0,BinTree * parent=NULL);
    ~BinTree();

    void addChild(int weight,unsigned  char symbol,bool direction);// Надо ли?
    void addChild(BinTree * child,BinTree * parent,bool direction);

    void setWeight(int weight);
    void setParent(BinTree * parent);

    int getWeight();
    unsigned char getSymbol();
    void recalcWeight();

    BinTree * toChild(bool direction);//Вернет NULL если нет такого ребенка. 0 - левый , 1 - правый
    BinTree * toParent();// Вернет NULL если это самый корень дерева

    static void countSymbols(int * symbols, std::string filename);
private:
    BinTree * m_parent;
    BinTree * m_rightChild;
    BinTree * m_leftChild;
    int m_weight;
    unsigned char m_symbol;

};

#endif // BINTREE_H
