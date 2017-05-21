#include <iostream>
#include <fstream>
#include "field.h"
#include "node.h"
#include <ctime>
#include <cmath>
#include <list>
#include <unistd.h>
using namespace std;

void wayToWin(Node* node)
{
    list<Field> way;
    while(node->getParent()!=NULL)
    {
        way.push_front(node->getField());
        node = node->getParent();
    }
    for(list<Field>::iterator it = way.begin(); it != way.end(); it++)
    {
        system("clear");
        (*it).printField();
        sleep(1);
    }

}


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Unexpected number of arguments"<<endl;
        exit(1);
    }
    Field fi;
    ifstream in;

    in.open(argv[1]);
    try
    {
        fi.readFieldFromFlie(in);
    }
    catch(const char * error)
    {
        cerr << error<<endl;
        exit(1);
    }
    std::vector<bool> memory;
    std::list<Node> states;
    bool win = false;
    unsigned char coordinates = fi.getHeight() * fi.getWidth();
    unsigned long maxSize =  pow(coordinates , (fi.getBoxesCount()+1));

    memory.resize(maxSize);
    cout<<"Начальное поле"<<endl;
    fi.printField();
    cout<<"Высота "<<(int)fi.getHeight()<<endl;
    cout<<"Ширина "<<(int)fi.getWidth()<<endl;
    cout<<"Кол-во коробок "<<(int)fi.getBoxesCount()<<endl;
    cout<<"maxSize "<<maxSize<<" vec size "<<memory.size()<<endl;
    sleep(5);
    states.push_back(Node(fi,NULL));
    list<Node>::iterator currentNode = states.begin();
    while(!win)
    {
        if(states.size() >= maxSize)
        {
            cerr << "No win found"<<endl;
            break;
        }
        for(int DIR = Directions::_Start; DIR != Directions::_End; DIR++)
        {
            Field f;
            f = (*currentNode).getField();
            if(f.move((Directions)DIR))
            {
                cout<<"move "<<endl;
                cout<<"index "<<f.getMemory()<<endl;
                if(memory.at(f.getMemory())==false)
                {
                    cout<<"check"<<endl;
                    memory[f.getMemory()] = true;
                    states.push_back(Node(f,&(*currentNode)));
                    if(f.checkForWin())
                    {
                        win = true;
                        cout<<"ETO POBEDA!"<<endl;

                        wayToWin(&states.back());
                        break;
                    }
                }
            }
        }
        currentNode++;
    }
    in.close();
    return 0;
}
