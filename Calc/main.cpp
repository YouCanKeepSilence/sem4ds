#include <iostream>
#include "nqueue.h"
#include "lecsema.h"
#include "nstack.h"
#include <iomanip>
#include <sstream>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif
double calc(const char * str, int * status);
#ifdef __cplusplus
}
#endif

using namespace std;
bool baseCheck(string str)
{
    if(str.empty())
    {
        cout<<"Пустая строка."<<endl;
        return false;
    }
    for(int i=0; i <= str.length(); i++)
    {
        if(isalpha(str[i]))
        {
            cout<<"Есть буквы"<<endl;
            return false;
        }
    }

    return true;
}
/* Добавить проверки елси точка не разделяет два числа,
 * Проверку на предыдущий символ посредством черри пика с очереди
 * Добавить функцию для динамик каста
 *
 */
double calc(const char * str , int * status)
{
    string expression=str;
    stringstream bufstr;

    bool minus=false;
    bool space=false;
    bool wasDigit=false;
    bool point=false;
    int priority = -1;

    NQueue * queue= new NQueue(expression.length()-1);
    Number * num;
    Operand * oper;
    Lecsema * buf;

    if(!baseCheck(expression))
    {
        *status = -1;
        cout<<"Что-то не так с выражением"<<endl;
        return 0;
    }

    for(int i=0; i<=expression.length()-1; i++)
    {
        char c=str[i];//stream.peek если число то считать из потока число иначе символ кидать в элс. минус привязать к числу только в начале строки и после открывающей скобки.
        if(isdigit(c))
        {
            if(space && wasDigit)
            {
                *status = -1;
                cout<< "Ошибка, два числа разделены пробелом"<<endl;
                return 0;
            }
            if(minus)
            {
                bufstr<<c;


            }
            if(point)//12*(-1)
            {
                bufstr<<"."<<c;
            }
            wasDigit=true;
            cout<<c<<endl;
            bufstr<<c;
            continue;
        }
        else if(Operand::analyzeChar(c,minus,space,point, priority))
        {
            if(space && wasDigit)
            {
                continue;
            }

            if(!space && !minus && !point)
            {
                oper=new Operand(c);
                oper->setPriority(priority);
                buf=dynamic_cast<Lecsema*>(oper);
                if(buf)
                {
                    queue->add(buf);
                }
                else
                {
                    cout<<"Ошибка приведения типа"<<endl;
                    *status = -1;
                    return 0;
                }
            }
            cout<<"Распознан символ "<<c<<" приоритет "<<priority<<endl;
            wasDigit=false;

        }
        else
        {
            *status = -1;
            cout<<"Неопознанный символ"<<endl;
            break;
        }

    }
    cout<<"итог"<<bufstr.str()<<endl;
    return 0;
}

int main(int argc, char *argv[])
{
    system("clear");
    int *status = new int();
    string str="2 +        2 ^ 8 + 3 + 2 - 2";
    char* pstr = (char*)str.c_str();
//    cout<<pstr;
    calc(pstr,status);
//    cout<<calc( pstr, status);
}
