#include "translator.h"
#include <fstream>
#include <iostream>
Translator::Translator()
{
    m_sourceFile=m_pathOfTransform="";
}

string Translator::ChangeCode(string sourceFile,TypeOfChange type)
{
    unsigned char c;
    m_sourceFile=sourceFile+".txt";
    ifstream fromFile;
    ofstream toFile;
    fromFile.open(m_sourceFile);
    static string saveName;
    switch (type)
    {
    case cp866_cp1251:
        saveName+="cp866_cp1251_";
        toFile.open(saveName+".txt");
        while(!fromFile.eof())
        {
           c=fromFile.get();
           if(c >= 128)
                c=Cp866ToCp1251[(int)c-128];
           if(fromFile.eof())
               break;
           toFile.put(c);
        }
        break;

    case cp1251_cp866:
        saveName+="cp1251_cp866_";
        toFile.open(saveName+".txt");
        while(!fromFile.eof())
        {
           c=fromFile.get();
           if(c >= 128)
                c=Cp1251ToCp866[(int)c-128];
           if(fromFile.eof())
           {
               break;
               std::cout<<"it's EOF"<<(int)c<<endl;
           }
           toFile.put(c);
        }
        break;

    case cp866_koi8r:
        saveName+="cp866_koi8r_";
        toFile.open(saveName+".txt");
        while(!fromFile.eof())
        {
           c=fromFile.get();
           if(c >= 128)
                c=Cp866ToKoi8R[(int)c-128];
           if(fromFile.eof())
               break;
           toFile.put(c);

        }
        break;

    case koi8r_cp866:
        saveName+="koi8r_cp866_";
        toFile.open(saveName+".txt");
        while(!fromFile.eof())
        {
           c=fromFile.get();
           if(c >= 128)
                c=Koi8RToCp866[(int)c-128];
           if(fromFile.eof())
               break;
           toFile.put(c);

        }
        break;

    case cp1251_koi8r:
        saveName+="cp1251_koi8r_";
        toFile.open(saveName+".txt");
        while(!fromFile.eof())
        {
           c=fromFile.get();
           if(c >= 128)
                c=Cp1251ToKoi8R[(int)c-128];
           if(fromFile.eof())
               break;
           toFile.put(c);
        }
        break;

    case koi8r_cp1251:
        saveName+="koi8r_cp1251_";
        toFile.open(saveName+".txt");
        while(!fromFile.eof())
        {
           c=fromFile.get();
           if(c >= 128)
                c=Koi8RToCp1251[(int)c-128];
           if(fromFile.eof())
               break;
           toFile.put(c);
        }
        break;

    default:
        break;
    }
    fromFile.close();
    toFile.close();
    return saveName;
}
