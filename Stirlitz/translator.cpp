#include "translator.h"
#include <fstream>
Translator::Translator()
{
    m_sourceFile=m_pathOfTransform="";


}

bool Translator::ChangeCode(string sourceFile,TypeOfChange type)
{
//    int realNum=0;
    char c;
//    codeTable now_code;
    m_sourceFile=sourceFile;
    ifstream fromFile;
    ofstream toFile;
    fromFile.open(m_sourceFile);
    switch (type) {
    case cp866_cp1251:
        while(!fromFile.eof())
        {
           c=fromFile.get();

        }
        break;
    default:
        break;
    }
}
