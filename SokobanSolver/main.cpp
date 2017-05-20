#include <iostream>
#include <fstream>
#include "field.h"
#include <ctime>
#include <cmath>
using namespace std;



int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Unexpected number of arguments"<<endl;
        exit(1);
    }
    Field fi;
    ifstream in;

    in.open(argv[1]);
    try
    {
        fi.readFieldFromFlie(in);
    }
    catch(const char * error)
    {
        cerr << error<<endl;
        exit(1);
    }
    std::vector<bool> memory;
    memory.resize(pow((int)fi.getHeight() * (int)fi.getWidth() , (int)fi.getBoxesCount()));
    memory.resize(pow(100 , 5 ));
    cout<<(int)fi.getHeight()<<endl;
    cout<<(int)fi.getWidth()<<endl;
    cout<<(int)fi.getBoxesCount()<<endl;
    cout<<memory.size();
    int a;
    cin>>a;
    in.close();
    return 0;
}
