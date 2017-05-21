#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include <iostream>
#define MAX_BOXES 5

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
    bool wallAt(unsigned char coordinate);
    bool placeAt(unsigned char coordinate);
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
    void printField();

private:
    static StaticField * sField;
    void sortBoxes();
    char checkBox(unsigned char position); // -1 если нет коробки иначе индекс в boxes
    unsigned char playerPos;
    unsigned char boxes[MAX_BOXES];

};

#endif // FIELD_H
