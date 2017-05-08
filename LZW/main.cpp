#include <iostream>
#include "table.h"
#include "writer.h"
#include "reader.h"
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

void packing(std::string inName,std::string outName,unsigned short size)
{
    ifstream in;
    ofstream out;
    in.open(inName,ios_base::binary);
    if(!in.is_open())
    {
        cerr<<"Ошибка при открытии входого файла. Завершение"<<endl;
        return;
    }
    out.open(outName,ios_base::binary);
    if(!out.is_open())
    {
        cerr<<"Ошибка при открытии выходного файла. Завершение"<<endl;
        in.close();
        return;
    }
    Writer writer;
    ofstream debug;
    debug.open("debugWrite.txt");
    uint8_t maxSize = size;
    out.write("LZW5",4);
    out.put(maxSize);

    writer.attach(&out);
    writer.setState(Tools::zero);
    Table strings(pow(2,size));
    string currentString="";
    unsigned int flag = 256;
    unsigned int mark = 0;
    cout<<strings.getRealSize();
//    bool first = true;
    while(1)
    {

        char c=in.get();

        if(in.eof())
        {
            if(!currentString.empty())
            {
                cout<<"Последняя строка "<<strings.getIndex(currentString)<<endl;
                debug<<strings.getIndex(currentString);
                writer.writeCode(strings.getIndex(currentString));
                writer.flush();
            }
            break;
        }
        if(strings.contains(currentString+c))
        {

            currentString.push_back(c);
//            cout<<"Есть строка "<<currentString<<" продолжаю "<<endl;
            continue;
        }
        else
        {
            string bufstr = currentString;
            currentString.push_back(c);
            strings.add(currentString);
//            cout<<"Добавлена строка "<<currentString<<" ее код "<<strings.getIndex(currentString)<<" выписан код "<<strings.getIndex(bufstr)<<endl;
            currentString = c;
            if((strings.getRealSize()-1)%flag==0 && strings.getRealSize() < strings.getMaxSize()) // для холодного старта
            {
//                if(first)
//                {
//                    first = false;
//                    writer.writeCode(strings.getIndex(bufstr));
//                    writer.setState(Tools::second);
//                    cout<<endl<<"Начальный пинок "<<strings.getRealSize();
//                    continue;
//                }
                mark++;
//                int state = mark +1;
                debug<<strings.getIndex(bufstr)<<endl;
                writer.writeCode(strings.getIndex(bufstr));
                cout<<"Текущий размер : "<<strings.getRealSize()<<" Состояние изменено с "<<(mark-1)<<" на "<<mark<<endl;
                writer.setState((Tools::States)mark);
                debug<<"State"<<mark;
                flag *= 2;
                continue;
            }
            else
            {
                debug<<strings.getIndex(bufstr)<<endl;
                writer.writeCode(strings.getIndex(bufstr));
                continue;
            }
        }
    }
//    writer.flush();
    cout<<"realSize "<<strings.getRealSize()<<endl;
    in.close();
    out.close();
    return;
}

void unpacking(std::string inName, std::string outName)
{
    ifstream in;
    ofstream out;
    in.open(inName,ios_base::binary);
    if(!in.is_open())
    {
        cerr<<"Ошибка при открытии входого файла. Завершение"<<endl;
        return;
    }
    out.open(outName);
    if(!out.is_open())
    {
        cerr<<"Ошибка при открытии выходного файла. Завершение"<<endl;
        in.close();
        return;
    }
    char str[4];
    in.read(str,4);
    if(!(strncmp(str,"LZW5",4)==0))
    {
        cerr<<"Не LZW5 файл. Выход."<<endl;
        return;
    }
    Reader reader;
    ofstream debug;
    debug.open("debugRead.txt");
    short size = in.get();
    cout<<size;
    Table strings(pow(2,size));
    reader.attach(&in);
    reader.setState(Tools::zero);
    int flag = 256;
    int mark = 0;
    unsigned short old=0;
    unsigned short code=0;
    code = reader.readNextSymbol();
    cout<<strings.getRealSize();
    out<<strings.getString(code);
    while(1)
    {
        old = code;
        debug<<old<<endl;
        if((strings.getRealSize())%flag==0 && (strings.getRealSize() < strings.getMaxSize()))
        {
            cout<<"размер "<< strings.getRealSize()<<" состояние изменено с "<<mark;
            mark++;
            reader.setState((Tools::States)mark);
            cout<<" на "<<mark<<endl;
            debug<<"State"<<mark;
            flag *= 2;
        }
        code = reader.readNextSymbol();
        if(in.eof())
        {
            break;
        }

        if(strings.contains(code))
        {
            out<<strings.getString(code);
            cout<<"Yes, string : "<<strings.getString(code)<<endl;
            strings.add(strings.getString(old) + strings.getString(code)[0]);
        }
        else
        {
            string bufstr= strings.getString(old);
            out<<(bufstr + bufstr[0]);
            cout<<"No, string : "<<(bufstr + bufstr[0])<<endl;
            strings.add(bufstr + bufstr[0]);
        }

    }

    in.close();
    out.close();
}

int main(int argc, char *argv[])
{
    system("clear");
    if(argc==4)
    {
        //TODO упаковка
//        stringstream str;
//        str<<argv[3];
//        unsigned short size;
//        str>>size;
        packing(argv[1],argv[2],atoi(argv[3]));
        unsigned short num = 46;
        unsigned short mask = 0b1000000000000000;
        for(int i = 0; i<16;i++)
        {
            if(num & (mask >> i))
            {
                cout<<1;
            }
            else
            {
                cout<<0;
            }
        }
        cout<<"Pack"<<endl;
    }
    else if(argc==3)
    {
        //TODO распаковка
        unpacking(argv[1],argv[2]);
        cout<<"Unpack"<<endl;
    }

    cout<<"hello"<<endl;
    cout<<"goodbye"<<endl;


}
