#include "field.h"
#include <cmath>
StaticField::StaticField():
    width(0),
    height(0)
{

}

StaticField::~StaticField()
{
    places.clear();
    walls.clear();
}



StaticField * Field::sField = new StaticField();

void StaticField::addWallOrPlace(bool wall, bool place)
{
    walls.push_back(wall);
    places.push_back(place);
}

bool StaticField::wallAt(unsigned char coordinate)
{
    return walls.at((int)coordinate);
}

bool StaticField::placeAt(unsigned char coordinate)
{
    return places.at((int)coordinate);
}

void StaticField::setWidth(unsigned char width)
{
    this->width = width;
}

void StaticField::setHeight(unsigned char height)
{
    this->height = height;
}

void StaticField::setBoxesCount(unsigned char boxesCount)
{
    this->boxesCount = boxesCount;
}

void StaticField::configureWinPlaces()
{
    unsigned char boxNum = 0;
    for(unsigned char i=0 ; i < places.size(); i++)
    {
        if(places.at(i)==1)
        {
            winPlaces[boxNum] = i;
            boxNum++;
        }
    }
}

unsigned char StaticField::getWidth()
{
    return width;
}

unsigned char StaticField::getHeight()
{
    return height;
}

unsigned char StaticField::getBoxesCount()
{
    return boxesCount;
}

unsigned char *StaticField::getPlacesIndexes()
{
    return winPlaces;
}

bool StaticField::canMove(unsigned char position)
{
    return (!walls.at(position));
}

Field::Field() : playerPos(0)
{

}

void Field::readFieldFromFlie(std::istream &in)
{
    if(!in)
    {
        throw "Error with input stream!";
    }
    unsigned char coordinate = 0;
    int currentWidth = 0;
    int width = 0;
    int height = 1;
    int boxIndex = 0;
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
            //Стена
            sField->addWallOrPlace(1,0);            
            break;
        case '$':
            //Место под ящик
            sField->addWallOrPlace(0,1);            
            break;
        case 'X':
            //Ящик на месте для ящика
            sField->addWallOrPlace(0,1);
            boxes[boxIndex] = coordinate;
            boxIndex++;
            break;
        case 'B':
            //Ящик
            sField->addWallOrPlace(0,0);
            boxes[boxIndex] = coordinate;
            boxIndex++;
            break;
        case ' ':
            sField->addWallOrPlace(0,0);
            break;
        case '\n':
            if(currentWidth > width)
            {
                width = currentWidth;
            }
            height++;
            currentWidth = -1;
            coordinate--;
            break;
        case 'P':
            //игрок
            sField->addWallOrPlace(0,0);
            playerPos = coordinate;         
            break;
        default:
            break;
        }
        coordinate++;
        currentWidth++;
        if(boxIndex > MAX_BOXES)
        {
            throw "Error with count of boxes. Check MAX_BOXES";
        }
    }
    sField->setBoxesCount(boxIndex);
    sField->setWidth(width);
    sField->setHeight(height);
    sField->configureWinPlaces();
}

bool Field::move(Directions direction)
{
    unsigned char width = sField->getWidth();
    unsigned char newPosition = 0;
    switch(direction)
    {
    case Up:
        newPosition = playerPos - width;
        if(sField->canMove(newPosition))
        {
            char index = checkBox(newPosition);
            if(index != -1)
            {
                if(sField->canMove(newPosition - width))
                {
                    if(checkBox(newPosition - width)!= -1)
                    {
//                        std::cout<<"no"<<std::endl;
                        return false;
                    }
                    else
                    {
                        boxes[(int)index] -= width;
                        this->sortBoxes();
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        break;
    case Right:
        newPosition = playerPos + 1;
        if(sField->canMove(newPosition))
        {
            char index = checkBox(newPosition);
            if(index != -1)
            {
                if(sField->canMove(newPosition + 1))
                {
                    if(checkBox(newPosition + 1)!=-1)
                    {
//                        std::cout<<"no"<<std::endl;
                        return false;
                    }
                    else
                    {
                        boxes[(int)index]++;
                        this->sortBoxes();
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        break;
    case Down:
        newPosition = playerPos + width;
        if(sField->canMove(newPosition))
        {
            char index = checkBox(newPosition);
            if(index != -1)
            {
                if(sField->canMove(newPosition + width))
                {
                    if(checkBox(newPosition + width)!=-1)
                    {
//                        std::cout<<"no"<<std::endl;
                        return false;
                    }
                    else
                    {
                        boxes[(int)index] += width;
                        this->sortBoxes();
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        break;
    case Left:
        newPosition = playerPos -1;
        if(sField->canMove(newPosition))
        {
            char index = checkBox(newPosition);
            if(index != -1)
            {
                if(sField->canMove(newPosition - 1))
                {
                    if(checkBox(newPosition - 1)!=-1)
                    {
//                        std::cout<<"no"<<std::endl;
                        return false;
                    }
                    else
                    {
                        boxes[(int)index]--;
                        this->sortBoxes();
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        break;
    default:
        std::cerr<<"ERROR!! Unknow direction"<<std::endl;
        return false;
        break;
    }
    playerPos = newPosition;
    return true;

}

bool Field::checkForWin()
{
    unsigned char * win;
    win = sField->getPlacesIndexes();
    if(memcmp(win , boxes, sField->getBoxesCount())==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned char Field::getWidth()
{
    return sField->getWidth();
}

unsigned char Field::getHeight()
{
    return sField->getHeight();
}

unsigned char Field::getBoxesCount()
{
    return sField->getBoxesCount();
}

unsigned char Field::getPlayerPos()
{
    return playerPos;
}

unsigned char *Field::getBoxes()
{
    return boxes;
}

unsigned long long Field::getMemory()
{
    unsigned long long index = playerPos;
    unsigned char coordinate = sField->getHeight() * sField->getWidth();
    unsigned char count = sField->getBoxesCount();
    for(int i = 0; i < count; i++)
    {
        index += boxes[i] * pow(coordinate , i+1);
    }
    return index;
}

void Field::printField()
{
    unsigned char maxCoordinate = sField->getHeight() * sField->getWidth();
    for(unsigned char i = 0 ; i < maxCoordinate ; i++)
    {

        if(sField->wallAt(i))
        {
            std::cout<<"#";
        }
        else if(sField->placeAt(i))
        {
            if(checkBox(i)!=-1)
            {
                std::cout<<"X";
            }
            else
            {
                std::cout<<"$";
            }
        }
        else if(checkBox(i)!=-1)
        {
            std::cout<<"B";
        }
        else if(playerPos == i)
        {
            std::cout<<"P";
        }
        else
        {
            std::cout<<" ";
        }
        if( ((i+1) % sField->getWidth())==0)
        {
            std::cout<<std::endl;
        }

    }
}

void Field::sortBoxes()
{
    unsigned char buf;
    for(int i = 1 ; i < sField->getBoxesCount() ; i++)
    {
        for(int j = i; j > 0 && boxes[j-1] > boxes[j]; j--)
        {
            buf = boxes[j-1];
            boxes[j - 1] = boxes[j];
            boxes[j] = buf;
        }
    }
}

char Field::checkBox(unsigned char position)
{
    for(char i = 0 ; i<sField->getBoxesCount(); i++)
    {
        if(boxes[(int)i] == position)
        {
            return i;
        }
    }
    return -1;
}

