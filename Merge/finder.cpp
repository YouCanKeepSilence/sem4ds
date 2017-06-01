#include "finder.h"
#include "cat.h"
#include <fstream>
#include <iostream>
#include <cmath>
Finder::Finder(std::string sortByName, std::string sortByAge):
    sortByName(sortByName),
    sortByAge(sortByAge)
{

}

void Finder::setFileWithNames(std::string sortByName)
{
    this->sortByName = sortByName;
}

void Finder::setFileWithAges(std::string sortByAge)
{
    this->sortByAge = sortByAge;
}

std::string Finder::getFileWithNames()
{
    return this->sortByName;
}

std::string Finder::getFileWithAges()
{
    return this->sortByAge;
}

void Finder::find(int age)
{
    std::ifstream in;
    in.open(sortByAge , std::ios::binary);
    if(!in.is_open())
    {
        throw "Error no file " + sortByAge + " or it can't be open";
    }
    std::streampos RightEdge;
    std::streampos LeftEdge;
    LeftEdge = in.tellg(); // CLASS_SIZE;     //Начало потока ( в котах)
    in.seekg(0, in.end);
    std::cout<<"Line "<<in.tellg()<<std::endl;
    unsigned int zzz= in.tellg();
    std::cout<<zzz<<std::endl;
    RightEdge = in.tellg(); // CLASS_SIZE;    // Конец потока ( в котах)
    in.seekg(0, in.beg);
    std::streampos currentOffset = (RightEdge - LeftEdge )/2;
    currentOffset = floor(currentOffset / CLASS_SIZE);
    std::cout<<currentOffset<<std::endl;
    int delta = 0;
    while(RightEdge - LeftEdge != 1)
    {

        in.seekg( currentOffset * CLASS_SIZE,in.beg);
        Cat kitty;
        in >> kitty;
        if(kitty.getAge() < age)
        {
            //Вправо
            LeftEdge = currentOffset * CLASS_SIZE;
            delta = (RightEdge - LeftEdge) / 2;
        }
        else if(kitty.getAge() > age)
        {
            //Влево
            RightEdge = currentOffset * CLASS_SIZE;
            delta = -(RightEdge - LeftEdge) / 2;
        }
        else
        {
            //Надо двигаться влево пока не пропадет совпадения затем до упора вправо
            std::cout<<"Нашел"<<std::endl;
            std::cout<<"offset "<<currentOffset<<std::endl;
            int countOfSteps = 0;
            while(1)
            {
                countOfSteps--;
                in.seekg( ((int)currentOffset + countOfSteps) * CLASS_SIZE,in.beg);
                in >> kitty;
                if(kitty.getAge() != age)
                {
                    countOfSteps++;
                    in.seekg( ((int)currentOffset + countOfSteps) * CLASS_SIZE,in.beg);
                    break;
                }

            }
            while(1)
            {
//                std::cout<<c.getAge()<<std::endl;
                in >> kitty;
//                std::cout<<"Выписал бы "<<c.getAge()<<std::endl;
                if(kitty.getAge() != age)
                {
                    break;
                }
//                c.printCat();
            }
//            c.printCat();
            break;
        }
        currentOffset += floor(delta / CLASS_SIZE);
    }
    in.close();
}
