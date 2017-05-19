#include <iostream>
#include <fstream>
#include "field.h"
#include <ctime>
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

    in.close();
    return 0;
}
