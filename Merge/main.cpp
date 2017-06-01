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
    path.findBreed("Мейн-кун");
//    int s = 7;
//    int e = 7;
//    string name = "А";
//    path.find(name);
//    Sorter sorter("dictionaryNechet.txt", "sortByBreed.dat" , 1);
//    sorter.sort();
//    ifstream in;
//    in.open("sortByName.dat",ios_base::binary);
//    if(!in.is_open())
//    {
//        cout<<"Нет такого";
//    }
//    Cat c;
//    int temp = 0;
//    in >> c;
//    int counter = 0;
//    while(!in.eof())
//    {
////        if(temp > c.getAge())
////        {
////            cout<<"Error"<<endl;
////        }
//        temp = c.getAge();
////        c.printCat();
////        cout<<temp<<endl;
////        if(temp >= s && temp <= e)
//        if(!strncmp(c.getName().c_str(),name.c_str(),name.length()))
//        {
//            counter++;
////            c.printCat();
////            break;
////            c.printCat();
//        }
//        in >> c;
//    }
//    in.close();
//    cout<<"in file: "<<counter<<endl;
    cout<<"Elapsed time "<<(clock() - start)/CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}
