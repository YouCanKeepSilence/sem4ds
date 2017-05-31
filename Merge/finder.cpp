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
    RightEdge = in.tellg(); // CLASS_SIZE;    // Конец потока ( в котах)
    in.seekg(0, in.beg);
    std::streampos currentOffset = (RightEdge - LeftEdge )/2;
    currentOffset = floor(currentOffset / CLASS_SIZE);
    std::cout<<currentOffset<<std::endl;
    int delta = 0;
    while(RightEdge - LeftEdge != 1)
    {

        in.seekg( currentOffset * CLASS_SIZE,in.beg);
        Cat c;
        in >> c;
        std::cout<<c.getAge()<<std::endl;
        std::cout<<" Offset : "<<currentOffset<<std::endl;
        if(c.getAge() < age)
        {

            //Вправо
            LeftEdge = currentOffset * CLASS_SIZE;
            delta = (RightEdge - LeftEdge) / 2;
        }
        else if(c.getAge() > age)
        {
            //Влево
            RightEdge = currentOffset * CLASS_SIZE;
            delta = -(RightEdge - LeftEdge) / 2;
        }
        else
        {
            std::cout<<"Нашел"<<std::endl;
            c.printCat();
            break;
        }
        currentOffset += delta / CLASS_SIZE;
//        currentOffset = floor(currentOffset / CLASS_SIZE);
//        break;

    }
    in.close();
}
