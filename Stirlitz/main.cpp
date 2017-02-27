#include <iostream>
#include <fstream>
#include "translator.h"
#include "analyzer.h"
using namespace std;


int main(int argc, char *argv[])
{
    Analyzer *analyze;
    analyze=new Analyzer;
    codeTable code;
    code=analyze->codeOfText("D:/Projects/Work&Study/sem4ds/Stirlitz/1.txt");
    switch (code) {
    case koi8r:
        cout<<"it's koi8r";
        break;
    case cp1251:
        cout<<"it's cp1251";
        break;
    case cp866:
        cout<<"it's cp866";
        break;
    case NoOne:
        cout<<"undefined format";
        break;
    default:
        cout<<"somethig wrong";
        break;
    }

}
