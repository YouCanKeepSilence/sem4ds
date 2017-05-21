#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include <iostream>

enum Directions
{
    _Start = 0,
    Up = 0,
    Right,
    Down,
    Left,
    _End
};

class StaticField
{
public:
    StaticField();
    ~StaticField();
    void addWallOrPlace(bool wall, bool place);
    void setWidth(unsigned char width);
    void setHeight(unsigned char height);
    void setBoxesCount(unsigned char boxesCount);
    unsigned char getWidth();
    unsigned char getHeight();
    unsigned char getBoxesCount();
    unsigned char * getPlacesIndexes();
    bool canMove(unsigned char position);
private:
    unsigned char boxesCount;
    unsigned char width;
    unsigned char height;
    std::vector<bool> walls;
    std::vector<bool> places;
};

class Field
{
public:
    Field();
//    ~Field();
    Field(Field &f);
    Field& operator= (const Field &f);
    void readFieldFromFlie(std::istream &in);
    bool move(Directions direction);
    bool checkForWin();
    void setStaticField(StaticField * sField);
    unsigned char getWidth();
    unsigned char getHeight();
    unsigned char getBoxesCount();
    unsigned char getPlayerPos();
    unsigned char *getBoxes();
    unsigned long getMemory();
private:
    static StaticField * sField;
    unsigned char playerPos;
    unsigned char * boxes;

};

#endif // FIELD_H
