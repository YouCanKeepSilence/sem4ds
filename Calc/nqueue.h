#ifndef NQUEUE_H
#define NQUEUE_H
#include "lecsema.h"


class NQueue
{
public:
    NQueue(Lecsema *data=nullptr);
    void AddToQueue(Lecsema *data);
    Lecsema * GetFromQueue(bool &isOver);
private:
    NQueue * p_current;
    NQueue * p_next;
    NQueue * p_first;
    Lecsema *m_data;
};

#endif // NQUEUE_H
