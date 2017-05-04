#include <iostream>
#include "table.h"
#include "writer.h"
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

    uint8_t maxSize = size;
    out.write("LZW5",4);
    out.put(maxSize);

    writer.attach(&out);
    writer.setState(Tools::first);
    Table strings(pow(2,size));
    string currentString;
    unsigned int flag = 256;
    unsigned int mark = 0;
    bool first = true;
    while(1)
    {

        char c=in.get();

        if(in.eof())
        {
            if(!currentString.empty())
            {
                writer.writeCode(strings.getIndex(currentString));
            }
            break;
        }
        if(strings.contains(currentString+c))
        {
            currentString.push_back(c);
            continue;
        }
        else
        {
            currentString.push_back(c);
            strings.add(currentString);
            string bufstr = currentString;
            currentString = c;
            if((strings.getRealSize()-1)%flag==0 && strings.getRealSize()< strings.getMaxSize()) // для холодного старта
            {
                if(first)
                {
                    first = false;
                    writer.setState(Tools::second);
                    cout<<"Начальный пинок "<<strings.getRealSize();
                    writer.writeCode(strings.getIndex(bufstr));
                    continue;
                }
                mark++;
                int state = mark +1;
                cout<<"Текущий размер : "<<strings.getRealSize()<<" Состояние изменено с "<<mark<<" на "<<state<<endl;
                writer.setState((Tools::States)state);
                flag *= 2;
            }
            writer.writeCode(strings.getIndex(bufstr));
            continue;
        }
    }
    writer.flush();
    cout<<"realSize "<<strings.getRealSize()<<endl;
    in.close();
    out.close();
    return;
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
//        packing(argv[1],argv[2],atoi(argv[3]));
        unsigned short num = 65535;
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
//    else if(argc==3)
//    {
//        //TODO распаковка
//        cout<<"Unpack"<<endl;
//    }

    cout<<"hello"<<endl;
    cout<<"goodbye"<<endl;


}
