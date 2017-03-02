#include "analyzer.h"
#include <fstream>
#include <iostream>
#include <cmath>
Analyzer::Analyzer()
{
    for(int i=0; i <= 128; i++)
        m_counter[i] = 0;
    m_code = NoOne;

}

void Analyzer::resetCounters()
{
    for(int i=0; i <= 128; i++)
        m_counter[i] = 0;
}

codeTable Analyzer::codeOfText(string sourceFile)
{
    ifstream fromFile;
    int count866,count1251,count_koi8r;
    resetCounters();
    count866 = 0;
    count1251 = 0;
    count_koi8r = 0;
    fromFile.open(sourceFile);

    if(!fromFile.is_open())
    {
        std::cout<<"Не удалось открыть файл "<<sourceFile;
        m_code = NoOne;
        return NoOne;
    }

    while(!fromFile.eof())
    {
        unsigned char c;
        c=fromFile.get();
        if(c>=128)
            m_counter[c-128]++;
    }

    int result = 0;

    for(int i = 0; i <= 128; i++)
        result += m_counter[i];

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
    int similarity = -1;//Если 1 то совпало 2 символа из 3 - текст внятен.
    unsigned char top1;
    unsigned char top2;
    unsigned char top3;
//    if(m_source.empty())
//    {
//        cout<<"!!!!!!!Ошибка. Не задано имя файла."<<endl;
//        return false;
//    }
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
//    cout<<"top1 = "<<top1<<endl<<"top2 = "<<top2<<endl<<"top3 = "<<top3<<endl;
    m_currentTop[0]=top1;
    m_currentTop[1]=top2;
    m_currentTop[2]=top3;
    cout<<"---------------"<<endl;
    for(int i=0;i<=2;i++)
    {

        cout<<m_currentTop[i]<<endl;
    }
    switch (m_code)
    {
    case NoOne:
        cout<<"Незивестная мне кодировка. Не могу распознать"<<endl;
        return false;
        break;
    case cp866:
        cout<<"866"<<endl;
        for(int j=0;j<=2;j++)
            for(int i=0;i<=5;i++)
                if(m_topCp866[i]==m_currentTop[j])
                    similarity++;

        break;
    case cp1251:
        cout<<"1251"<<endl;
        for(int j=0;j<=2;j++)
            for(int i=0;i<=5;i++)
                if(m_topCp1251[i]==m_currentTop[j])
                    similarity++;
        break;
    case koi8r:
        cout<<"koi8r"<<endl;
        for(int j=0;j<=2;j++)
            for(int i=0;i<=5;i++)
                if(m_topKoi8r[i]==m_currentTop[j])
                    similarity++;
        break;
    default:
        cout<<"Что-то не так."<<endl;
        return false;
        break;
    }
    if(similarity>=1)
        return true;
    else
        return false;
}
