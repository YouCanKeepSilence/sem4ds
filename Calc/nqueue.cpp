#include "nqueue.h"
#include <iostream>
using namespace std;

NQueue::NQueue(Lecsema *data, int size)
{
    m_size=size;
    Lecsema *mass[size];
    m_realsize=0;
    for(int i=0;i<size;i++)
    {
        mass[i]=nullptr;
    }
    if(data)
    {
        m_indexOfFirst=0;
        m_indexOfLast=0;
        mass[0]=data;
        m_realsize++;
    }
    m_data=mass;
}

void NQueue::AddToQueue(Lecsema *data)
{
    if(m_indexOfLast+1<=m_size)
    {
        m_indexOfLast++;
        m_data[m_indexOfLast]=data;
        m_realsize++;
    }
    else
    {
        cout<<"Превышен размер массива"<<endl;
        return;
    }
}

Lecsema * NQueue::GetFromQueue()
{
    Lecsema * forData;
    if(m_realsize<=0)
    {
        cout<<"Массив пуст"<<endl;
        return nullptr;
    }
    forData=m_data[m_indexOfFirst];
    m_indexOfFirst++;
    m_realsize--;
    return forData;
}
