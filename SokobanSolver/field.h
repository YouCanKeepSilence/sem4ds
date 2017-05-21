#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include <iostream>
#define MAX_BOXES 4

enum Directions                             // Направления движения
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
    void addWallOrPlace(bool wall, bool place); // Добавляем в вектор стенок и мест
    bool wallAt(unsigned char coordinate);      // Есть ли стена на координате
    bool placeAt(unsigned char coordinate);     // Есть ли место на координате
    void setWidth(unsigned char width);
    void setHeight(unsigned char height);
    void setBoxesCount(unsigned char boxesCount);
    void configureWinPlaces();                  //Собирает массив winPlaces
    unsigned char getWidth();
    unsigned char getHeight();
    unsigned char getBoxesCount();
    unsigned char * getPlacesIndexes();         // Выдает winPlaces проверка победы
    bool canMove(unsigned char position);       //Проверка можно ли сходить на координату
private:
    unsigned char boxesCount;                   //Кол-во коробок
    unsigned char width;
    unsigned char height;
    unsigned char winPlaces[MAX_BOXES];         // Необходим для проверки победы
    std::vector<bool> walls;                    //Стены
    std::vector<bool> places;                   //Места под коробоки
};

class Field
{
public:
    Field();
    void readFieldFromFlie(std::istream &in);   // Чтение из файла
    bool move(Directions direction);            // Двигает в направлении enum'a  возвращает true если удалось сходить
    bool checkForWin();                         // Проверяет победа ли
    void setStaticField(StaticField * sField);  //Устанавливает поле  содержащее стены и места под коробки
    unsigned char getWidth();
    unsigned char getHeight();
    unsigned char getBoxesCount();
    unsigned char getPlayerPos();
    unsigned char *getBoxes();
    unsigned long long getMemory();             // Возвращает индекс в массиве состояний
    void printField();                          // Выводит поле на экран

private:
    static StaticField * sField;                // Поле содерщаее стены и места под коробки
    void sortBoxes();                           // сортировка, нужна для проверки победы и вообще
    char checkBox(unsigned char position);      // -1 если нет коробки иначе индекс в boxes
    unsigned char playerPos;                    // Позиция игрока
    unsigned char boxes[MAX_BOXES];             // Массив коробок

};

#endif // FIELD_H
