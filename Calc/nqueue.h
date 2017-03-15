#ifndef NQUEUE_H
#define NQUEUE_H
#include "lecsema.h"


class NQueue
{
public:
    NQueue(Lecsema *data=nullptr, int size=1024);
    void add(Lecsema *data);
    Lecsema * get();

private:
    Lecsema **replace();
    int m_indexOfFirst;
    int m_indexOfLast;
    int m_realsize;
    int m_size;
    Lecsema ** m_data;

};

#endif // NQUEUE_H
