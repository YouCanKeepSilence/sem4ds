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
    void resetCounters();
    codeTable  m_code;
    int m_counter[128];
};

#endif // ANALYZER_H
