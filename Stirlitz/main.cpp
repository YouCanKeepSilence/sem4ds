#include <iostream>
#include <fstream>
#include "translator.h"
#include "analyzer.h"
using namespace std;


int main(int argc, char *argv[])
{
    Analyzer *analyze;
    Translator *translate;
    translate=new Translator;
    analyze=new Analyzer;
    string source;
    string str;
    while(!analyze->isReadable())
    {
        for(int i=0;i<=5;i++)
        {
            str=translate->ChangeCode(source,(Translator::TypeOfChange)i);
            if(analyze->isReadable())
                vreak;
            for()
        }
    }
//    switch (code)
//    {
//    case koi8r:
//        cout<<"it's koi8r";
//        break;
//    case cp1251:
//        cout<<"it's cp1251";
//        break;
//    case cp866:
//        cout<<"it's cp866";
//        break;
//    case NoOne:
//        cout<<"undefined format";
//        break;
//    default:
//        cout<<"somethig wrong";
//        break;
//    }

}
