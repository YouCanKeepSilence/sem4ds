#include <iostream>
#include "nqueue.h"
#include "lecsema.h"
#include "nstack.h"
#include <iomanip>
#include <string>
#ifdef __cplusplus
extern "C" {
#endif
double calc(const char * str, int * status);
#ifdef __cplusplus
}
#endif
using namespace std;
double сalc(char * str , int * status)
{
    string expression=str;

}

int main(int argc, char *argv[])
{
    system("clear");
    Lecsema * p;
    NStack * queue;
    Number * n;
    n=new Number;
    n->setNum(2.28);
    p=dynamic_cast<Lecsema*>(n);
    if(p)
    {
        queue=new NStack();
        queue->add(p);
        cout<<"first add "<<n->getNum()<<endl;
    }
    for(int i=0; i <=50000; i++)
    {
        n=new Number(i);
        p=dynamic_cast<Lecsema*>(n);
        if(p)
        {
            queue->add(p);
            cout<<i<<" add = "<<n->getNum()<<endl;
        }
    }
    for(int i=0; i<=50000 + 1 ; i++)
    {
        p=queue->get();
        if(p)
        {
            n=dynamic_cast<Number*>(p);
            if(n)
            {
                cout<<i<<" get = "<<n->getNum()<<endl;
            }

        }
    }


    for(int i=0; i <= 50000; i++)
    {
        n=new Number(i);
        p=dynamic_cast<Lecsema*>(n);
        if(p)
        {
            queue->add(p);
            cout<<i<<" add = "<<n->getNum()<<endl;
        }
    }
    for(int i=0; i<=50000 + 1 ; i++)
    {
        p=queue->get();
        if(p)
        {
            n=dynamic_cast<Number*>(p);
            if(n)
            {
                cout<<i<<" get = "<<n->getNum()<<endl;
            }

        }
    }
    return 0;
}
