#include <iostream>
#include <fstream>
#include "field.h"
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
    Field fi;
    ifstream in;
    in.open(argv[1]);

//    fi.readFieldFromFlie(in);
    in.close();
    return 0;
}
