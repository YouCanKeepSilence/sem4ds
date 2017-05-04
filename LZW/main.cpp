#include <iostream>
#include "myhash.h"
#include "writer.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    system("clear");
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

    MyHash hash(1024);
    hash.add("ABC",2);
    hash.add("ABCD",3);
    hash.add("A",4);
    hash.add("AB",5);
    hash.add("BC",6);
    try
    {
    cout<<hash.get("ABC")<<endl;
    cout<<hash.get("ABCD")<<endl;
    cout<<hash.get("A")<<endl;
    cout<<hash.get("Z")<<endl;


    }
    catch(std::runtime_error re)
    {
        cout<<re.what();
    }
    cout<<hash.get("AB")<<endl;
    cout<<hash.get("BC")<<endl;

}
