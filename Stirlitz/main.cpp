#include <iostream>
#include <fstream>
#include "translator.h"
#include "analyzer.h"
#include <vector>
using namespace std;


int main(int argc, char *argv[])
{
    Analyzer *analyze;
    Translator *translate;
    translate=new Translator;
    analyze=new Analyzer;
    string source="D:/Projects/Work&Study/sem4ds/Stirlitz/3";
//    string source="/Users/silence/Workbench/Bondin/sem4ds/build-stirlitz-Desktop_Qt_5_7_0_clang_64bit-Debug/31";
    string str,str1,str2;
    vector<string> vec;
//    str=translate->ChangeCode(source,Translator::koi8r_cp1251);
//    str=translate->ChangeCode(str,Translator::koi8r_cp866);
//    str=translate->ChangeCode(str,(Translator::cp1251_cp866));

   for(int n=0;n<=3;n++)
    {
        for(int i=0;i<=5;i++)
        {
            str=translate->ChangeCode(source,(Translator::TypeOfChange)i);
            analyze->codeOfText(str+".txt");
            if(analyze->isReadable())
            {
                cout<<str<<endl;
                rename((str+".txt").c_str(),"result.txt");
                return 0;
                break;
            }
            vec.push_back(str+".txt");
            for(int j=0;j<=5;j++)
            {
                str1=translate->ChangeCode(str,(Translator::TypeOfChange)j);
                analyze->codeOfText(str1+".txt");
                if(analyze->isReadable())
                {
                    cout<<str1<<endl;
                    rename((str1+".txt").c_str(),"result.txt");
                    return 0;
                    break;
                }
                vec.push_back(str1+".txt");
                for(int k=0;k<=5;k++)
                {
                    str2=translate->ChangeCode(str1,(Translator::TypeOfChange)k);
                    analyze->codeOfText(str2+".txt");
                    if(analyze->isReadable())
                    {
                        cout<<str2<<endl;
                        rename((str2+".txt").c_str(),"/Users/silence/Workbench/Bondin/sem4ds/build-stirlitz-Desktop_Qt_5_7_0_clang_64bit-Debug/result.txt");
                        for(int c=0;c<=vec.size();c++)
                        {
                            remove(vec[c].c_str());
                        }
                        return 0;
                        break;
                    }
                    vec.push_back(str2+".txt");
                }


            }
        }
    }
    for(int c=0;c<=vec.size();c++)
    {
        remove(vec[c].c_str());
    }
    cout<<"Все плохо. Текст не внятен или глубина больше 3"<<endl;

}
