#include <iostream>
#include <fstream>
using namespace std;
void createKoi8r_Cp1251()
{
    ofstream toFile;
    toFile.open("koi8r-1251.txt");
    int counter=0;
    for(int c=128;c<=255;c++)
    {

        int b;

        counter++;
        if(c>=192 && c<=255)
        {
            cout<<(char)c<<" ";
            cin>>b;
            toFile<<b<<", ";
        }
        else
        {
            if((int)c==163)
            {
                cout<<(char)c<<" = ";
                c=184;
                cout<<(int)c<<endl;
                toFile<<(int)c<<", ";
                c=163;
            }
            else if((int)c==179)
            {
                cout<<(char)c<<" = ";
                c=168;
                cout<<(int)c<<endl;
                toFile<<(int)c<<", ";
                c=179;
            }

            else
            {
                cout<<(char)c<<" = "<<(int)c<<endl;
                toFile<<(int)c<<", ";
            }


        }
        if(counter%8==0)
            toFile<<"\n";
    }
    toFile.close();


}
void createKoi8r_Cp866()
{
    ofstream toFile;
    toFile.open("koi8r-cp866.txt");
    int counter=0;
    for(int c=128;c<=255;c++)
    {

        int b;

        counter++;
        if(c>=192 && c<=255)
        {
            cout<<(char)c<<" ";
            cin>>b;
            toFile<<b<<", ";
        }
        else
        {
            if((int)c==163)
            {
                cout<<(char)c<<" = ";
                c=241;
                cout<<(int)c<<endl;
                toFile<<(int)c<<", ";
                c=163;
            }
            else if((int)c==179)
            {
                cout<<(char)c<<" = ";
                c=240;
                cout<<(int)c<<endl;
                toFile<<(int)c<<", ";
                c=179;
            }

            else
            {
                cout<<(char)c<<" = "<<(int)c<<endl;
                toFile<<(int)c<<", ";
            }


        }
        if(counter%8==0)
            toFile<<"\n";
    }
    toFile.close();

}
void createCp866_koi8r()
{

}

void createCp1251_koi8r()
{

}
void createCp1251_Cp866()
{
    ofstream toFile;
    toFile.open("cp1251-cp866");


}
void createCp866_Cp1251()
{
    ofstream toFile;
    toFile.open("cp866-cp1251");
    for(int i=128;i<=255;i++)
    {
        char c;
        if(i>=128 && i<=175)
    }

}

int main(int argc,char** argv)
{
    system("clear");
//    createKoi8r_Cp1251();
//    createKoi8r_Cp866();

    return 0;
}

