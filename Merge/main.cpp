#include <iostream>
#include <fstream>
#include "cat.h"
using namespace std;

int main(int argc, char *argv[])
{
    Cat cat("Vasya","Russia",66666,'m');
    ofstream out;
    system("clear");
    cout<<cat<<endl;
    cout<<cat.getAge()<<endl;
    out.open("vasya.txt",ios_base::binary);
    if(!out.is_open())
    {
        return 1;
    }
    out<<cat;
    out.close();
    ifstream in;
    in.open("vasya.txt",ios_base::binary);
    if(!in.is_open())
    {
        return 1;
    }
    Cat c;
    in>>c;
    cout<<"_________________"<<endl;
    cout<<c<<endl;
    cout<<c.getAge();

    return 0;
}
