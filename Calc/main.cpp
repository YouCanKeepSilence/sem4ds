#include <iostream>
#include "nqueue.h"
#include "lecsema.h"
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    system("clear");
    Lecsema * p;
    NQueue * queue;
    Number * n;
    Number * n1;
    n1=new Number;
    n1->setNum(3.32);
    n=new Number;
    n->setNum(2.28);
    p=dynamic_cast<Lecsema*>(n);
    if(p)
    {
        queue=new NQueue(p);
        cout<<"first add "<<n->getNum()<<endl;
    }
    p=dynamic_cast<Lecsema*>(n1);
    if(p)
    {
        queue->AddToQueue(p);
        cout<<"second add "<<n1->getNum()<<endl;
    }
    p=nullptr;
    n=nullptr;
    p=queue->GetFromQueue();
    n=dynamic_cast<Number*>(p);
    if(n)
        cout<<"first out "<<n->getNum()<<endl;
    p=nullptr;
    p=queue->GetFromQueue();
    n1=dynamic_cast<Number*>(p);
    if(n1!=nullptr)
    {
        cout<<"second out  "<<n1->getNum()<<endl;
    }
    p=queue->GetFromQueue();

    return 0;
}
