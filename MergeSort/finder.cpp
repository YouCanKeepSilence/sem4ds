#include "finder.h"
#include <fstream>
#include <iostream>
#include <cmath>
Finder::Finder(std::string sortByName, std::string sortByAge, std::string sortByBreed):
    sortByName(sortByName),
    sortByAge(sortByAge),
    sortByBreed(sortByBreed)
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

void Finder::findAge(int from, int to)
{
    if(to == 0)     //Если задано только старт
    {
        to = from;
    }
    unsigned int countOfCats = 0;
    long long offset;
    setState(0);
    try
    {
        offset = findOffset(Cat(from));
        openCurrentFile();
    }
    catch(const char * error)
    {
        std::cerr<<error<<std::endl;
        return;
    }

    in.seekg(offset, in.beg);
    Cat kitty;
    in >> kitty;
    if(kitty.getAge() != from)                  // Жуткий костыль, как тебя убрать?
    {
        in>>kitty;
    }
    else
    {
        in.seekg(offset - CLASS_SIZE, in.beg);
        in >> kitty;
        if(kitty.getAge() != from)
        {
            in>>kitty;
        }
    }
    while((kitty.getAge() >= from) && (kitty.getAge() <= to) && !in.eof())
    {
        countOfCats++;
        kitty.printCat();
        in>>kitty;
    }
    if(countOfCats == 0)
    {
        std::cout<<"No cats found"<<std::endl;
    }
    else
    {
        std::cout<<"Number of found cats "<<countOfCats<<std::endl;
    }
    in.close();

}

void Finder::findName(std::string name)
{
    unsigned int countOfCats = 0;
    long long offset;
    setState(2);
    try
    {
        offset = findOffset(Cat(name));
        openCurrentFile();
    }
    catch(const char * error)
    {
        std::cerr<<error<<std::endl;
        return;
    }

    in.seekg(offset, in.beg);
    Cat kitty;
    in >> kitty;
    if(strncmp(kitty.getName().c_str(),name.c_str(),name.length()))                  // Жуткий костыль, как тебя убрать?
    {
        in>>kitty;
    }
    else
    {
        in.seekg(offset - CLASS_SIZE, in.beg);
        in >> kitty;
        if(strncmp(kitty.getName().c_str(),name.c_str(),name.length()))
        {
            in>>kitty;
        }
    }
    while(!strncmp(kitty.getName().c_str(),name.c_str(),name.length()) && !in.eof())
    {
        countOfCats++;
        kitty.printCat();
        in>>kitty;
    }
    if(countOfCats == 0)
    {
        std::cout<<"No cats found"<<std::endl;
    }
    else
    {
        std::cout<<"Number of found cats "<<countOfCats<<std::endl;
    }
    in.close();
}

void Finder::findBreed(std::string breed)
{
    unsigned int countOfCats = 0;
    long long offset;
    setState(1);
    try
    {
        offset = findOffset(Cat("",breed));
        openCurrentFile();
    }
    catch(const char * error)
    {
        std::cerr<<error<<std::endl;
        return;
    }

    in.seekg(offset, in.beg);
    Cat kitty;
    in >> kitty;
    if(kitty.getBreed() != breed)                  // Жуткий костыль, как тебя убрать?
    {
        in>>kitty;
    }
    else
    {
        in.seekg(offset - CLASS_SIZE, in.beg);
        in >> kitty;
        if(kitty.getBreed() != breed)
        {
            in>>kitty;
        }
    }
    while(kitty.getBreed() == breed && !in.eof())
    {
        countOfCats++;
        kitty.printCat();
        in>>kitty;
    }
    if(countOfCats == 0)
    {
        std::cout<<"No cats found"<<std::endl;
    }
    else
    {
        std::cout<<"Number of found cats "<<countOfCats<<std::endl;
    }
    in.close();
}

long long Finder::findOffset(Cat target)
{
//    std::ifstream in;
    in.open(currentFileName , std::ios::binary);
    if(!in.is_open())
    {
        throw "Error no file " + currentFileName + " or it can't be open";
    }
    long long RightEdge;
    long long LeftEdge;
    long long result = 0;
    LeftEdge = in.tellg();                                  //Начало потока
    in.seekg(0, in.end);
    RightEdge = in.tellg();                                 // Конец потока
    in.seekg(0, in.beg);
    unsigned int currentOffset = (RightEdge - LeftEdge )/2;
    currentOffset = floor(currentOffset / CLASS_SIZE);      // Получаем сдвиг относительно начала в котах, при сдвиге умножаем на размер кота.
    int delta = -1;                                          // тут изменение offset'a
    Cat kitty;

    while(RightEdge - LeftEdge != 1 && delta != 0)
    {
        std::cout<<"Offset "<<currentOffset<<std::endl;
        in.seekg( currentOffset * CLASS_SIZE,in.beg);
        result = in.tellg();
        in >> kitty;
        if((kitty.*lessThan)(target))
        {
                //Вправо
            LeftEdge = currentOffset * CLASS_SIZE;
            delta = floor((RightEdge - LeftEdge) / (2*CLASS_SIZE));
        }
        else
        {
                //Влево
            RightEdge = currentOffset * CLASS_SIZE;
            delta = floor((LeftEdge - RightEdge ) / (2*CLASS_SIZE));
        }

        std::cout<<"Delta "<<delta<<std::endl;
        currentOffset += delta;
    }
    kitty.printCat();
    in.close();
    return result;
}

void Finder::setState(int state)
{
    switch (state) {
    case 0:
        lessThan = &Cat::lessThanByAge;
        currentFileName = sortByAge;
        break;
    case 1:
        lessThan = &Cat::lessThanByBreed;
        currentFileName = sortByBreed;
        break;
    case 2:
        lessThan = &Cat::lessThanByName;
        currentFileName = sortByName;
        break;
    default:
        std::cerr << "Unknow state. Set zero";
        lessThan = &Cat::lessThanByAge;
        currentFileName = sortByAge;
        break;
    }
}

void Finder::openCurrentFile()
{
    in.open(currentFileName , std::ios::binary);
    if(!in.is_open())
    {
        throw "Error no file " + currentFileName + " or it can't be open";
    }
}
