#include <iostream>
#include <fstream>
#include "cat.h"
#include "sorter.h"
using namespace std;

int main(int argc, char *argv[])
{

    ifstream in;
    system("clear");
    in.open("dictionarySmall.txt",ios_base::binary);
//    Sorter sorter;
//    sorter.Sort("dictionarySmall.txt");
//    for(int i=0; i < 15 ; i++)
//    {
//        Cat c;
//        in >> c;
//        c.printCat();
//    }
    while(!in.eof())
    {
        Cat c;

        in>>c;
        if(in.eof())
        {
            c.printCat();
            break;
        }
        c.printCat();
    }
    return 0;
}
