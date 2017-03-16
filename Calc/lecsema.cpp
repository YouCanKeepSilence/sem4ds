#include "lecsema.h"
#include <iostream>
using namespace std;
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

void Operand::setPriority(int priority)
{
    if(priority<0 || priority >2)
    {
        cout<<"Ошибка приоритета"<<endl;
        return;
    }
    m_prioriry=priority;
}

bool Operand::analyzeChar(char c, bool &minus, bool &space,bool &point, int &priority)
{
    char definedChar=false;
//    cout<<(int)c<<endl;
    if((int)c==32)
    {
        definedChar=true;
        space=true;
        priority = -1;
    }
    else
    {
        switch (c)
        {
        case '.':
            definedChar=true;
            space=false;
            priority=-1;
            break;
        case '(':
            definedChar=true;
            space=false;
            priority = 0;
            break;
        case ')':
            definedChar=true;
            space=false;
            priority = 0;
            break;
        case '-':
            minus=true;
            definedChar=true;
            space=false;
            priority = 1;
            break;
        case '+':
            definedChar=true;
            space=false;
            priority = 1;
            break;
        case '/':
            definedChar=true;
            space=false;
            priority = 2;
            break;
        case '*':
            definedChar=true;
            space=false;
            priority = 2;
            break;
        case '^':
            definedChar=true;
            space=false;
            priority = 3;
            break;
        default:
            definedChar=false;
            cout<<"Неопределеный символ. Все очень плохо"<<endl;
            break;
        }
    }
    return definedChar;
}
