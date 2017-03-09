#include <iostream>
#include "nqueue.h"
#include "lecsema.h"
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    Lecsema * p;
    Number * n;
    n=new Number;
    n->setNum(2.28);
    p=dynamic_cast<Lecsema*>(n);
    //Суй в очередь
    n=dynamic_cast<Number*>(p);

    cout<<"Hi"<<n->getNum();
    return 0;
}
