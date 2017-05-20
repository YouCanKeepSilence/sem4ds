#include "field.h"
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

bool StaticField::canMove(unsigned char position)
{

    return (!walls.at(position));
}

Field::Field()
{
    boxes = NULL;
}

Field::~Field()
{
    delete [] boxes;
}

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
    switch(direction)
    {
    case Up:
        if((playerPos >= sField->getWidth()) & (sField->canMove(playerPos - sField->getWidth())))
        {

        }
        break;
    case Right:
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

