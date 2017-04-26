#include <iostream>
#include "myhash.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
//    if(argc==4)
//    {
//        //TODO упаковка
//        cout<<"Pack"<<endl;
//    }
//    else if(argc==3)
//    {
//        //TODO распаковка
//        cout<<"Unpack"<<endl;
//    }
    ifstream ifs;
    ifs.open("31.txt");
    int array[137349];
    for(int i=0; i< 137349; i++)
    {
        array[i]=0;
    }
    int counter = 0;
    MyHash hash(137349);
    while(1)
    {
        string str;
        ifs>>str;
        if(ifs.eof())
            break;
        int h = hash.getHash(str);
        cout<<"Hash for "<<str<<" is "<<h<<endl;
        array[h]++;
        counter++;
    }
    for(int j=0; j<137349 ; j++)
    {
        if(array[j]>100)
            cout<<j<<" count "<<array[j]<<endl;
    }
    cout<<counter;
}
