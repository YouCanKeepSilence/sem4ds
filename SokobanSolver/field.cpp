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
    std::vector<unsigned char> buf;
    for(unsigned char i=0 ; i < places.size(); i++)
    {
        if(places.at(i)==1)
        {
            buf.push_back(i);
        }
    }
    unsigned char * indexes;
    indexes = new unsigned char [buf.size()];
    for(unsigned long i = 0; i<buf.size(); i++)
    {
        indexes[i] = buf[i];
    }
    buf.clear();
    return indexes;
}

bool StaticField::canMove(unsigned char position)
{
    return (!walls.at(position));
}

Field::Field() : playerPos(0),
    boxes(NULL)

{

}

//Field::~Field()
//{
//    delete [] boxes;
//}

Field::Field(Field &f)
{
    this->playerPos = f.playerPos;
    this->boxes = new unsigned char[f.sField->getBoxesCount()];
    memcpy(boxes,f.boxes,f.sField->getBoxesCount());
}

Field &Field::operator =(const Field &f)
{
    if(this == &f)
    {
        return *this;
    }
    else
    {
        this->playerPos = f.playerPos;
        this->boxes = new unsigned char[f.sField->getBoxesCount()];
        memcpy(boxes,f.boxes,f.sField->getBoxesCount());
        return *this;
    }

}



void Field::readFieldFromFlie(std::istream &in)
{
    if(!in)
    {
        throw "Error with input stream!";
    }
    std::vector<char> bufBoxes;
    unsigned char coordinate = 0;
    int currentWidth = 0;
    int width = 0;
    int height = 1;
//    bool newString = true;
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
            std::cout<<"#";
            break;
        case '$':
            //Место под ящик
            sField->addWallOrPlace(0,1);
            std::cout<<"$";
            break;
        case 'X':
            //Ящик на месте для ящика
            sField->addWallOrPlace(0,1);
            bufBoxes.push_back(coordinate);
            std::cout<<"X";
            break;
        case 'B':
            //Ящик
            sField->addWallOrPlace(0,0);
            bufBoxes.push_back(coordinate);
            std::cout<<"B";
            break;
        case ' ':
            std::cout<<" ";
            sField->addWallOrPlace(0,0);
            break;
        case '\n':
            std::cout<<"\n";
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
            std::cout<<"P";
            break;
        default:
            std::cout<<"default";
            break;
        }
        coordinate++;
        currentWidth++;

    }
    std::cout<<std::endl<<(int)coordinate<<std::endl<<(int)width<<std::endl;
    sField->setBoxesCount(bufBoxes.size());
    sField->setWidth(width);
    sField->setHeight(height);
    boxes = new unsigned char [sField->getBoxesCount()];
    for(int i = 0; i < sField->getBoxesCount(); i++)
    {
        boxes[i] = bufBoxes.at(i);
        std::cout<<"Box #"<<i<<" "<<(int)boxes[i]<<" ";
    }
    std::cout <<"Player position "<< (int)playerPos<<std::endl;
    bufBoxes.clear();
}

bool Field::move(Directions direction)
{
    unsigned char width = sField->getWidth();
    unsigned char height = sField->getHeight();
    switch(direction)
    {
    case Up:
        if((playerPos >= width) && (sField->canMove(playerPos - width)))
        {
            for(int i=0 ; i < sField->getBoxesCount() ; i++)
            {
                if(boxes[i] == playerPos - width)
                {
                    if((playerPos - width >= width) && sField->canMove(playerPos - 2*width))
                    {
                        playerPos = boxes[i];
                        boxes[i] -= width;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            playerPos -= width;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case Right:
        if(sField->canMove(playerPos + 1))
        {
            for(int i = 0; i < sField->getBoxesCount() ; i++)
            {
                if(boxes[i] == playerPos + 1)
                {
                    if(sField->canMove(playerPos + 2))
                    {
                        for(int j = i; j < sField->getBoxesCount() ; j++)
                        {
                            if(boxes[j] == playerPos + 2)
                            {
                                return false;
                            }
                        }
                        playerPos = boxes[i];
                        boxes[i]++;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            playerPos++;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case Down:
        break;
    case Left:

        break;
    default:
        std::cerr<<"Unknow direction"<<std::endl;
        break;
    }
    return false;

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

unsigned long Field::getMemory()
{
//    std::vector<char> degrees;
//    for(int i = sField->getBoxesCount() - 1; i  >= 0; i--)
//    {
//        degrees.push_back();
//    }
    unsigned long index = playerPos;
    unsigned char coordinate = sField->getHeight() * sField->getWidth();
    unsigned char count = sField->getBoxesCount();
    for(int i = 0; i < count; i++)
    {
        index += boxes[i] * pow(coordinate , i+1);
    }
    return index;
}

