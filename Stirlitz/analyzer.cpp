#include "analyzer.h"
#include <fstream>
#include <iostream>
Analyzer::Analyzer()
{
    for(int i=0; i <= 128; i++)
        m_counter[i] = 0;
    m_code = NoOne;

}

codeTable Analyzer::codeOfText(string sourceFile)
{
    ifstream fromFile;
    int count866,count1251,count_koi8r;
    count866 = 0;
    count1251 = 0;
    count_koi8r = 0;
    fromFile.open(sourceFile);

    if(!fromFile.is_open())
    {
        std::cout<<"Не удалось открыть файл "<<sourceFile;
        for(int i = 0; i<= 128; i++)
            m_counter[i] = 0;
        m_code = NoOne;
        return NoOne;
    }

    while(!fromFile.eof())
    {
        unsigned char c;
        c=fromFile.get();
        m_counter[c-128]++;
    }

    int result = 0;

    for(int i = 0; i <= 128; i++)
        result += m_counter[i];

    for(int i = 0; i <= 128; i++)
    {
        char c;
        c=i+128;
        if(m_counter[i] != 0)
        {
            double proc=(double)m_counter[i]*100.00/(double)result;
            cout<<(int)proc<<" "<<c<<endl;
        }
    }
    for(int i = 128;i <= 175; i++)
        count866 += m_counter[i-128];

    for(int i = 224; i <= 241; i++)
        count866 += m_counter[i-128];

    for(int i = 192; i <= 255; i++)
        count_koi8r += m_counter[i-128];

    count_koi8r += m_counter[163-128];//Буквы ё
    count_koi8r += m_counter[179-128];//и Ё

    if(count866 - count_koi8r>0)
    {
        m_code = cp866;
        return cp866;
    }

    if(m_counter[163-128] + m_counter[179-128]>0)//Проверка на буквы Ёё в кои8р
    {
        m_code = koi8r;
        return koi8r;
    }

    if(m_counter[168-128] + m_counter[184-128]>0)//Проверка на буквы Ее в 1251
    {
        m_code = cp1251;
        return cp1251;
    }

    count_koi8r = 0;
    count1251 = 0;

    for(int i = 192; i <= 223; i++)
        count_koi8r += m_counter[i-128];
    for(int i = 224; i <= 255; i++)
        count1251 += m_counter[i-128];

    if(count_koi8r - count1251>0)
    {
        m_code=koi8r;
        return koi8r;
    }
    else
    {
        m_code = cp1251;
        return cp1251;
    }

}

bool Analyzer::isReadable()
{
    int toCompare = 0;
    unsigned char top1;
    unsigned char top2;
    unsigned char top3;
    for(int i = 0; i <= 128; i++)
    {
        if(m_counter[i] > toCompare)
        {
            toCompare = m_counter[i];
            top1 = i + 128;
        }
    }
    toCompare=0;
    for(int i = 0; i <= 128; i++)
    {
        if(m_counter[i] > toCompare && top1 != i+128)
        {
            toCompare = m_counter[i];
            top2 = i + 128;
        }
    }
    toCompare=0;
    for(int i = 0; i <= 128; i++)
    {
        if(m_counter[i] > toCompare && top1 != i+128 && top2 != i+128)
        {
            toCompare = m_counter[i];
            top3 = i + 128;
        }
    }
    cout<<"top1 = "<<top1<<endl<<"top2 = "<<top2<<endl<<"top3 = "<<top3<<endl;

    switch (m_code)
    {
    case NoOne:
        cout<<"Незивестная мне кодировка. Не могу распознать"<<endl;
        return false;
        break;
    case cp866:
//        if((top1 == m_expCp866[0] && top2 == m_expCp866[1])||(top2==)||())
        break;
    case cp1251:
        break;
    case koi8r:

        break;
    default:
        cout<<"Что-то не так."<<endl;
        return false;
        break;
    }
}
