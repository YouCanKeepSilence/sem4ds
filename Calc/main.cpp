#include <iostream>
#include "nqueue.h"
#include "lecsema.h"
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    Lecsema * p;
    NQueue * queue;
    Number * n;
    Number * n1;
    n1=new Number;
    n1->setNum(3.32);
    n=new Number;
    n->setNum(2.28);
    p=dynamic_cast<Lecsema*>(n);
    queue=new NQueue(p);
    p=dynamic_cast<Lecsema*>(n1);
    queue->AddToQueue(p);
    p=nullptr;
    n=nullptr;
    p=queue->GetFromQueue();
    n=dynamic_cast<Number*>(p);
    cout<<"Hi"<<n->getNum()<<endl;
    p=queue->GetFromQueue();
    n=dynamic_cast<Number*>(p);
    cout<<n->getNum();
    return 0;
}
