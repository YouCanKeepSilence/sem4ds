#include <iostream>

#include "writer.h"
#include "reader.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include "mytable.h"
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
//    ofstream debug;
//    debug.open("debugWrite.txt");
    uint8_t maxSize = size;
    out.write("LZW5",4);
    out.put(maxSize);

    writer.attach(&out);
    writer.setState(Tools::zero);
    MyTable strings(pow(2,size));
    string currentString="";
    unsigned int flag = 256;
    unsigned int mark = 0;
    unsigned short id;
    cout<<strings.getSize();
    int parent = -1;
    while(1)
    {

        unsigned char c=in.get();

        if(in.eof())
        {
            if(!currentString.empty())
            {
                cout<<"Последняя строка "<<parent<<endl;
//                debug<<parent;
                writer.writeCode(parent);
            }
            writer.flush();
            break;
        }
        if(strings.contains(parent,c))
        {
            parent = strings.getCurrentParentIndex();
            currentString.push_back(c);
        }
        else
        {
            id = parent;
            currentString.push_back(c);
            strings.add(c,parent,currentString);
            parent = strings.getCurrentParentIndex();
//            cout<<"Добавлена строка "<<currentString<<" ее код "<<strings.getIndex(currentString)<<" выписан код "<<strings.getIndex(bufstr)<<endl;
            currentString = c;

//            debug<<id<<endl;
            writer.writeCode(id);
            if((strings.getSize()-1)%flag==0 && strings.getSize() < strings.getMaxSize()) // для холодного старта
            {
                mark++;
                cout<<"Текущий размер : "<<strings.getSize()<<" Состояние изменено с "<<(mark-1)<<" на "<<mark<<endl;
                writer.setState((Tools::States)mark);
//                debug<<"State"<<mark;
                flag *= 2;
            }
        }
        strings.resetOldHash();
    }
    cout<<"realSize "<<strings.getSize()<<endl;
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
//    ofstream debug;
//    debug.open("debugRead.txt");
    short size = in.get();
//    cout<<size;
    vector<string> strings;
    unsigned int lastIndex=0;
    for(int i=0; i< 256; i++)
    {
        string str;
        str.push_back((char)i);
        strings.push_back(str);
        lastIndex++;
    }

    unsigned int maxSize = pow(2,size);
    for(unsigned int i = 256 ; i < maxSize; i++)
    {
        strings.push_back("");
    }
//    strings.resize(pow(2,size));
    reader.attach(&in);
    reader.setState(Tools::zero);
    int flag = 256;
    int mark = 0;
    unsigned short old=0;
    unsigned short code=0;
    code = reader.readNextSymbol();
    cout<<strings.size()<<endl;
    out.write(strings[code].c_str(),strings[code].size() );
    while(1)
    {
        old = code;
//        debug<<old<<endl;
        if(lastIndex%flag==0 && (lastIndex < maxSize))
        {
            cout<<"размер "<< lastIndex<<" состояние изменено с "<<mark;
            mark++;
            reader.setState((Tools::States)mark);
            cout<<" на "<<mark<<endl;
//            debug<<"State"<<mark;
            flag *= 2;
        }
        code = reader.readNextSymbol();
        if(in.eof())
        {
            break;
        }

        if((!strings.at(code).empty() ))
        {
            string toWrite = strings[code];
            out.write(toWrite.c_str(),toWrite.size());
//            cout<<"Yes, string : "<<toWrite<<endl;
            if(lastIndex < maxSize)
            {
                strings[lastIndex]=(strings[old] + strings[code][0]);
                lastIndex++;
            }
        }
        else
        {
            string bufstr= strings[old];
            string toWrite = bufstr + bufstr[0];
            out.write(toWrite.c_str(),toWrite.size());
//            cout<<"No, string : "<<toWrite<<endl;
            if(lastIndex < maxSize)
            {
                strings[lastIndex]=(toWrite);
                lastIndex++;
            }
        }

    }

    in.close();
    out.close();
}

int main(int argc, char *argv[])
{
    system("clear");
    clock_t start = clock();
    if(argc==4)
    {
        //TODO упаковка
        packing(argv[1],argv[2],atoi(argv[3]));
        cout<<"Pack"<<endl;
    }
    else if(argc==3)
    {
        //TODO распаковка
        unpacking(argv[1],argv[2]);
        cout<<"Unpack"<<endl;
    }

    cout<<"goodbye "<<endl;
    cout<<"time : "<<(clock() - start) / CLOCKS_PER_SEC<<" s "<<endl;
}
