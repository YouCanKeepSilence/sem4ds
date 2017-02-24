#include <iostream>
#include <fstream>
#include "translator.h"
using namespace std;


int main(int argc, char *argv[])
{
    fstream fromFile,toFile;
    fromFile.open("2.txt",ios_base::out);
    toFile.open("1.txt",ios_base::out);
    unsigned char c;
    string str;
    getline(cin,str);
    fromFile<<str;
    fromFile.close();
    fromFile.open("2.txt",ios_base::in);
    while(!fromFile.eof())
    {
        c=fromFile.get();
        cout<<(int)c<<" "<<c<<endl;

        if((c>=128)&&((c<=256)))
        {
        c=Cp866ToCp1251[c-128];

        }
        toFile.put(c);
    }

}
