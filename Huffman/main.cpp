#include <iostream>
#include "archiver.h"
using namespace std;
int main(int argc, char *argv[])
{
    system("clear");
    if(argc!=4)
    {
        cout<<"Not enough files or keys"<<endl;
        return 0;
    }
    string input;
    string out;
    string key;
    input=argv[1];
    key=argv[2];
    out=argv[3];
    if(key=="-a")
    {
        try
        {
            Archiver::archive(input,out);
        }
        catch(const char* ex)
        {
            cout<<ex<<endl;
        }
    }
    else if(key=="-u")
    {
        try
        {
            Archiver::unarchive(input,out);
        }
        catch(const char* ex)
        {
            cout<<ex<<endl;
        }

    }
    else
    {
        cout<<"Undefined key"<<endl;
    }
    cout<<"end"<<endl;
    return 1;
}
