#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include "analyzer.h"
#include "codeTables.h"
#include <string>
using namespace std;
class Analyzer;
class Translator
{
public:
    Translator();
    enum TypeOfChange
    {
        cp866_cp1251,
        cp866_koi8r,
        cp1251_cp866,
        cp1251_koi8r,
        koi8r_cp866,
        koi8r_cp1251
    };


    bool ChangeCode(string sourceFile,TypeOfChange type);
private:
//    Analyzer m_analyzer;
    codeTable m_code;
    string m_sourceFile;
    Analyzer *m_analyzer;
    TypeOfChange m_type;
    string m_pathOfTransform;
};

#endif // TRANSLATOR_H
