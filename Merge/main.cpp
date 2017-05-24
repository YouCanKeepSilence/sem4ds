#include <iostream>
#include <fstream>
#include "cat.h"
using namespace std;

int main(int argc, char *argv[])
{

    ifstream in;
    system("clear");
    in.open("dictionary.txt",ios_base::binary);
    if(!in.is_open())
    {
        return 1;
    }
    in.seekg(0 , in.end);
    unsigned int point = in.tellg() / CLASS_SIZE;
    in.seekg(0,in.beg);
    in.close();
    while(1)
    {
        string name1 = "half1.txt";
        string name2 = "half2.txt";
        ofstream buf1;
        ofstream buf2;
        buf1.open(name1,ios::binary);
        buf2.open(name2,ios::binary);
        if(!buf1.is_open() || !buf2.is_open())
        {
            cerr<<"Bad files"<<endl;
            return 1;
        }
        for(unsigned int i = 0 ; i < point/2 ; i++)
        {
            Cat c;
            in >> c;
            buf1<<c;

        }
        for(unsigned int i = point/2 ; i < point ; i++)
        {
            Cat c;
            in >> c;
            buf2<<c;
        }
        buf1.close();
        buf2.close();

    }
    return 0;
}
