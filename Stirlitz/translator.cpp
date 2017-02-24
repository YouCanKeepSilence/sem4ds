#include "translator.h"
#include <fstream>
Translator::Translator()
{
    m_sourceFile=m_pathOfTransform="";
    for(int i=0;i<=128;i++)
        m_counter[i]=0;

}

bool Translator::ChangeCode(string sourceFile,TypeOfChange type)
{
//    int realNum=0;
    char c;
    codeTable now_code;
    m_sourceFile=sourceFile;
    ifstream fromFile;
    ofstream toFile;
    fromFile.open(m_sourceFile);
    //Определить кодировку. Переписать в анализатор.
    while(!fromFile.oef())
    {
        c=fromFile.get();
        m_counter[c-128]++;
    }
    if()
    //как-то так
    fromFile.close();
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
