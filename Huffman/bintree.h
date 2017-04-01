#ifndef BINTREE_H
#define BINTREE_H
#include <string>
#include <list>

class BinTree
{
public:
    BinTree(uint32_t weight=0,unsigned char symbol=0,BinTree * parent=NULL);
    ~BinTree();

    void addChild(uint32_t weight,unsigned  char symbol,bool direction);// Надо ли?
    void addChild(BinTree * child,BinTree * parent,bool direction);

    void setWeight(uint32_t weight);
    void setParent(BinTree * parent);

    uint32_t getWeight();
    unsigned char getSymbol();
    void recalcWeight();

    BinTree * toChild(bool direction);//Вернет NULL если нет такого ребенка. 0 - левый , 1 - правый
    BinTree * toParent();// Вернет NULL если это самый корень дерева

    static void countSymbols(uint32_t *symbols, std::string filename);
    static BinTree* createHuffTree(uint32_t * symbols);
    static void createEncoding(std::string *symbolsEncoding, BinTree * root);
private:
    static std::list<BinTree*> createForest(uint32_t *symbols);
    BinTree * m_parent;
    BinTree * m_rightChild;
    BinTree * m_leftChild;
    uint32_t m_weight;
    unsigned char m_symbol;

};

#endif // BINTREE_H
