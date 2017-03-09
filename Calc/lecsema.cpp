#include "lecsema.h"
Lecsema::Lecsema()
{

}

Lecsema::~Lecsema()
{

}

Number::Number(double num)
{
    m_num=num;
}

double Number::getNum()
{
    return m_num;
}

void Number::setNum(double num)
{
    m_num=num;
}

Operand::Operand(char sim)
{
    m_sim=sim;
}

char Operand::getSim()
{
    return m_sim;
}

void Operand::setSim(char sim)
{
    m_sim=sim;
}
