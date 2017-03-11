#include "nqueue.h"

using namespace std;

NQueue::NQueue(Lecsema * data)
{
    static bool state=false;
    if(!state)
    {
        p_first=this;
        state=true;
    }
    p_next=nullptr;
    m_data=data;
    p_current=p_first;
}

void NQueue::AddToQueue(Lecsema *data)
{
    if(m_data==nullptr)
    {
        m_data=data;
        p_next=nullptr;
    }
    else
    {
        while(p_current->p_next!=nullptr)
        {
            p_current=p_next;
        }
        p_current->p_next=new NQueue(data);

    }
}

Lecsema * NQueue::GetFromQueue(bool &isOver)
{
    p_current=p_first;
    NQueue * p_buf;
    Lecsema * bufdata;
    if(p_current->p_next==nullptr)
    {
        bufdata = p_current->m_data;
        delete p_current;
        isOver=true;
        return bufdata;
    }
    while(p_current->p_next!=nullptr)
    {
        p_buf=p_current;
        p_current=p_next;
    }
    p_buf->p_next=nullptr;
    bufdata=p_current->m_data;
    delete p_current;
    isOver=false;
    return bufdata;


}
