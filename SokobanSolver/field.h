#ifndef FIELD_H
#define FIELD_H
#include <vector>

class StaticField
{
public:
    StaticField(std::vector<bool> &walls , std::vector<bool> &places);
private:
    std::vector<bool> walls;
    std::vector<bool> places;
};

class Field
{
public:
    Field();
    void readFieldFromFlie(std::istream &in);
private:
    void setStaticField(StaticField * sField);
    static StaticField * sField;

};

#endif // FIELD_H
