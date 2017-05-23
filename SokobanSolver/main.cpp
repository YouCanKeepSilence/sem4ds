#include <iostream>
#include <fstream>
#include "field.h"
#include "node.h"
#include <ctime>
#include <cmath>
#include <list>
#include <unistd.h>
using namespace std;

void wayToWin(const Node* node)
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
        usleep(90000);
    }

}


int main(int argc, char *argv[])
{
    clock_t start = clock();
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
        cerr << error <<endl;
        exit(1);
    }
    std::vector<bool> memory;
    std::list<Node> states;
    bool win = false;
    unsigned char coordinates = fi.getHeight() * fi.getWidth();
    unsigned long long maxSize =  pow(coordinates , (fi.getBoxesCount()+1));
    system("clear");
    cout<<"Start field "<<endl;
    fi.printField();
    cout<<"Height "<<(int)fi.getHeight()<<endl;
    cout<<"Width "<<(int)fi.getWidth()<<endl;
    cout<<"Count of boxes "<<(int)fi.getBoxesCount()<<endl;
    memory.resize(maxSize);
    cout<<"Count of bool "<<maxSize <<" Size in memory "<<memory.size() / 8<<endl;
    cout<<"Size of Field "<<sizeof(Field)<<endl;
    cout<<"Size of Node "<<sizeof(Node)<<endl;
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
                if(memory.at(f.getMemory())==false)
                {
                    memory[f.getMemory()] = true;
                    states.push_back(Node(f,&(*currentNode)));
                    if(f.checkForWin())
                    {
                        win = true;
                        cout<<"Win found. Lets watch result..."<<endl;
                        sleep(2);
                        wayToWin(&states.back());
                        break;
                    }
                }
            }
        }
        currentNode++;
    }
    cout<<"Elapsed time : "<< (clock() - start)/CLOCKS_PER_SEC<<" seconds."<<endl;
    in.close();
    return 0;
}
