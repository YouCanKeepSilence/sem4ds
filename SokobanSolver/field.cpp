#include "field.h"
#include <iostream>
StaticField::StaticField(std::vector<bool> &walls , std::vector<bool> &places)
{
    this->walls=walls;
    this->places = places;
}

Field::Field()
{

}

void Field::readFieldFromFlie(std::istream &in)
{
    if(!in)
    {
        throw "Error with input stream!";
    }
    std::vector<bool> bufWalls;
    std::vector<bool> bufPlaces;
    int counter =0;
    int width = 0;
    bool flag = true;
    while(1)
    {
        unsigned char c = in.get();
        if(in.eof())
        {
            break;
        }
        switch(c)
        {
        case '#':
            bufWalls.push_back(true);
            bufPlaces.push_back(false);
            std::cout<<"#";
            break;
        case '$':
            bufPlaces.push_back(true);
            bufWalls.push_back(false);
            std::cout<<"$";
            break;
        case 'X':
            //Ящик на месте
            bufPlaces.push_back(true);
            bufWalls.push_back(false);
            //Добавляется ящик на основе bufWalls.size()
            std::cout<<"X";
            break;
        case 'P':
            //игрок
            bufPlaces.push_back(false);
            bufWalls.push_back(false);
            std::cout<<"P";
            break;
        case 'B':
            bufPlaces.push_back(false);
            bufWalls.push_back(false);
            //Ящик
            std::cout<<"B";
            //ящик
            break;
        case '\n':
            std::cout<<"\n";
            if(flag)
            {
                flag = false;
                width = counter;
            }
            counter--;
            break;
        case ' ':
            std::cout<<" ";
            bufPlaces.push_back(false);
            bufWalls.push_back(false);
            break;
        default:
            std::cout<<"default";
            break;
        }
        counter++;
    }
    std::cout<<std::endl<<counter<<std::endl<<width<<std::endl;
    for(long i = 0; i < bufWalls.size() ; i++)
    {
        if(bufWalls[i])
            std::cout<<1;
        else
            std::cout<<0;
        if((i+1) % width == 0 )
        {
            std::cout<<std::endl;
        }
    }

}
