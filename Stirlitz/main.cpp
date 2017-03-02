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
    codeTable code;
    string str;
    code=analyze->codeOfText("D:/Projects/Work&Study/sem4ds/Stirlitz/2.txt");
    str=translate->ChangeCode("D:/Projects/Work&Study/sem4ds/Stirlitz/2", Translator::cp866_cp1251);
//    str=translate->ChangeCode()
    str=translate->ChangeCode(str, Translator::cp1251_cp866);
//    str=translate->ChangeCode(str, Translator::cp866_cp1251);
//    code=analyze->codeOfText(str+".txt");
//    analyze->isReadable();
//    str=translate->ChangeCode("D:/Projects/Work&Study/sem4ds/Stirlitz/1", (Translator::cp866_cp1251));
//    str=translate->ChangeCode(str, (Translator::cp1251_koi8r));
//    str=translate->ChangeCode(str, (Translator::koi8r_cp1251));
//    str=translate->ChangeCode(str, (Translator::cp1251_cp866));
//    str=translate->ChangeCode(str,Translator::cp866_cp1251);
//    str=translate->ChangeCode(str, (Translator::cp1251_koi8r));
//    str=translate->ChangeCode(str, (Translator::koi8r_cp1251));
//    str=translate->ChangeCode(str, (Translator::cp1251_cp866));
//    str=translate->ChangeCode(str, Translator::cp866_koi8r);
//    str=translate->ChangeCode(str,Translator::koi8r_cp866);
    code=analyze->codeOfText(str+".txt");
    analyze->isReadable();
    switch (code)
    {
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
