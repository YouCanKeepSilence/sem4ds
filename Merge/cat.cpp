#include "cat.h"

Cat::Cat(std::string name, std::string breed, int age, char gender)
{
    this->name=name;
    this->breed=breed;
    this->age=age;
    this->gender=gender;
}

int Cat::getAge()
{
    return this->age;
}

std::string Cat::getName()
{
    return this->name;
}

std::string Cat::getBreed()
{
    return this->breed;
}

char Cat::getGender()
{
    return this->gender;
}

std::istream& operator>>(std::istream &stream,Cat &cat)
{
    char name[MAX_SIZE_OF_NAME];
    stream.read(name,MAX_SIZE_OF_NAME);
    cat.name = name;
    char breed[MAX_SIZE_OF_BREED];
    stream.read(breed,MAX_SIZE_OF_BREED);
    cat.breed = breed;
    stream.read((char*)&cat.age,sizeof(int));
    cat.gender = stream.get();
    return stream;
}

std::ostream& operator<<(std::ostream &stream,Cat &cat)
{
    stream.write(cat.name.c_str(),MAX_SIZE_OF_NAME);
    stream.write(cat.breed.c_str(),MAX_SIZE_OF_BREED);
    stream.write((char*)&cat.age,sizeof(int));
    stream.put(cat.gender);
    return stream;
}
