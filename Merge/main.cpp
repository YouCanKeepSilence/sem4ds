#include <iostream>
#include <fstream>
#include "cat.h"
#include "sorter.h"
#include "finder.h"
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{


    system("clear");
    clock_t start = clock();
    Finder path;
    path.setFileWithAges("sortByAge.dat");
    path.find(57);
//    Sorter sorter("dictionaryNechet.txt", "sortByAge.dat" , 0);
//    sorter.sort();
    ifstream in;
//    in.open("sortByAge.dat",ios_base::binary);
//    if(!in.is_open())
//    {
//        cout<<"Нет такого";
//    }
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
////        c.printCat();
////        cout<<temp<<endl;
//        if(temp == 57)
//        {
//            c.printCat();
//            break;
//        }
//        in >> c;
//    }
//    in.close();
    cout<<"Elapsed time "<<(clock() - start)/CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}
