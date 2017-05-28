#include <iostream>
#include <fstream>
#include "cat.h"
#include "sorter.h"
using namespace std;

int main(int argc, char *argv[])
{


    system("clear");

    Sorter sorter("dictionary.txt");
    sorter.sort();
//    ifstream in;
//    in.open("~forMerge3.dat",ios_base::binary);
//    Cat c;
//    int temp = 0;
//    in >> c;
//    while(!in.eof())
//    {
//        if(temp > c.getAge())
//        {
//            cout<<"Error"<<endl;
//        }
//        temp = c.getAge();
//        c.printCat();
////        cout<<temp<<endl;
//        in >> c;
//    }
    return 0;
}
