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

void Finder::find(int from, int to)
{
    if(to == 0)     //Если задано только старт
    {
        to = from;
    }
    long long offset;
    try
    {
        offset = findOffset(from);
    }
    catch(const char * error)
    {
        std::cerr<<error<<std::endl;
        return;
    }
    std::ifstream in;
    in.open(sortByAge , std::ios::binary);
    if(!in.is_open())
    {
        throw "Error no file " + sortByAge + " or it can't be open";
    }
    if(offset == -1)
    {
        std::cout<<"We don't have cats with this options"<<std::endl;
        return;
    }
    in.seekg(offset, in.beg);
    Cat kitty;
    in >> kitty;
    while(kitty.getAge() <= to && !in.eof())
    {
        kitty.printCat();
        in>>kitty;
    }
    in.close();

}

void Finder::find(std::string word)
{

}

long long Finder::findOffset(int age)
{
    std::ifstream in;
    in.open(sortByAge , std::ios::binary);
    if(!in.is_open())
    {
        throw "Error no file " + sortByAge + " or it can't be open";
    }
    long long RightEdge;
    long long LeftEdge;
    LeftEdge = in.tellg();                                  //Начало потока
    in.seekg(0, in.end);
    RightEdge = in.tellg();                                 // Конец потока
    in.seekg(0, in.beg);
    unsigned int currentOffset = (RightEdge - LeftEdge )/2;
    currentOffset = floor(currentOffset / CLASS_SIZE);      // Получаем сдвиг относительно начала в котах, при сдвиге умножаем на размер кота.
    std::cout<<"Start offset "<<currentOffset<<std::endl;
    int delta = 0;                                          // тут изменение offset'a
    while(RightEdge - LeftEdge != 1)
    {
        std::cout<<"Offset "<<currentOffset<<std::endl;
        in.seekg( currentOffset * CLASS_SIZE,in.beg);
        Cat kitty;
        in >> kitty;
        if(kitty.getAge() < age)
        {
                //Вправо
            LeftEdge = currentOffset * CLASS_SIZE;
            delta = floor((RightEdge - LeftEdge) / (2*CLASS_SIZE));
        }
        else if(kitty.getAge() > age)
        {
                //Влево
            RightEdge = currentOffset * CLASS_SIZE;
            std::cout<<(LeftEdge - RightEdge ) / (2*CLASS_SIZE)<<std::endl;
            delta = floor((LeftEdge - RightEdge ) / (2*CLASS_SIZE));
        }
        else
        {
                //Надо двигаться влево пока не пропадет совпадения
            int countOfSteps = 0;
            std::cout<<"Нашел "<<std::endl;
            while(1)
            {

                countOfSteps--;
                in.seekg((currentOffset + countOfSteps) * CLASS_SIZE,in.beg);
                in >> kitty;
                if(kitty.getAge() != age)       // Как только вышли за пределы слева вернулись на шаг назад
                {
                    countOfSteps++;
                    std::cout<<"До "<<in.tellg();
                    in.seekg( (currentOffset + countOfSteps) * CLASS_SIZE,in.beg);
                    std::cout<<" После "<<in.tellg()<<std::endl;
                    in.close();
                    return (currentOffset + countOfSteps) * CLASS_SIZE;
                    break;
                }

            }

            break;
        }
        std::cout<<"Delta "<<floor(delta / CLASS_SIZE)<<std::endl;
        currentOffset += delta;
    }
    in.close();
    return -1;
}
