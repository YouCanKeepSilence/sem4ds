#include <iostream>
#include <fstream>
#include "cat.h"
#include "sorter.h"
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{


    system("clear");
    clock_t start = clock();
    Sorter sorter("dictionaryNechet.txt", "sortByAge.dat" , 0);
    sorter.sort();
//    ifstream in;
//    in.open("sortByName.dat",ios_base::binary);
//    if(!in.is_open())
//    {
//        cout<<"Нет такого";
//    }
//    Cat c;
//    string temp = "";
//    in >> c;
//    while(!in.eof())
//    {
//        if(temp > c.getName())
//        {
//            cout<<"Error"<<endl;
//        }
//        temp = c.getName();
////        c.printCat();
//        cout<<temp<<endl;
//        in >> c;
//    }
//    in.close();
    cout<<"Elapsed time "<<(clock() - start)/CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}
