#include "analyzer.h"
#include <fstream>
#include <iostream>
Analyzer::Analyzer()
{
    for(int i=0;i<=128;i++)
        m_counter[i]=0;

}

codeTable Analyzer::codeOfText(string sourceFile)
{
    ifstream fromFile;
    int count866,count1251,count_koi8r;
    count866=count1251=count_koi8r=0;
    fromFile.open(sourceFile);
    if(!fromFile.is_open())
    {
        std::cout<<"Не удалось открыть файл "<<sourceFile;for(int i=0;i<=128;i++)
            m_counter[i]=0;
        return NoOne;
    }

    while(!fromFile.eof())
    {
        unsigned char c;
        c=fromFile.get();
        cout<<(int)c<<" "<<c<<std::endl;
        m_counter[c-128]++;
    }
    for(int i=128;i<=175;i++)
        count866+=m_counter[i-128];
    for(int i=224;i<=241;i++)
        count866+=m_counter[i-128];
    for(int i=192;i<=255;i++)
        count_koi8r+=m_counter[i-128];
    count_koi8r+=m_counter[163-128];//Буквы ё
    count_koi8r+=m_counter[179-128];//и Ё

    if(count866-count_koi8r>0)
        return cp866;

    if(m_counter[163-128]+m_counter[179-128]>0)
        return koi8r;
    if(m_counter[168-128]+m_counter[184-128]>0)
        return cp1251;
    count_koi8r=count1251=0;
    for(int i=192;i<=223;i++)
        count_koi8r+=m_counter[i-128];
    for(int i=224;i<=255;i++)
        count1251+=m_counter[i-128];

    if(count_koi8r-count1251>0)
        return koi8r;
    else
        return cp1251;

}
