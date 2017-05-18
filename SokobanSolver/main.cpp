#include <iostream>
#include <fstream>
#include "field.h"
using namespace std;

int main(int argc, char *argv[])
{
    Field fi;
    ifstream in;
    in.open(argv[1]);
    fi.readFieldFromFlie(in);
    return 0;
}
