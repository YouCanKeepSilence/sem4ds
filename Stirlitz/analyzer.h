#ifndef ANALYZER_H
#define ANALYZER_H
#include "translator.h"
#include "codeTables.h"
#include <string>

class Analyzer
{
public:
    Analyzer();
    codeTable codeOfText(std::string sourceFile);
    bool isReadable();
private:
    int m_topCp866[6]
    {
        133,165,//Е е
        142,174,//О о
        128,160//А а
    };
    int m_topCp1251[6]
    {
        192,224,//А а
        197,229,//Е е
        206,238//О о
    };
    int m_topKoi8r[6]
    {
        225,193,//А а
        229,197,//Е е
        239,207//О о

    };
    int m_currentTop[2];
    std::string m_source;
    void resetCounters();
    codeTable  m_code;
    int m_counter[128];
};

#endif // ANALYZER_H
