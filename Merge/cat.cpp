#include "cat.h"

Cat::Cat(std::string name, std::string breed, int age, char gender):
    name(name),
    breed(breed),
    age(age),
    gender(gender)
{

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

void Cat::printCat()
{
    std::cout<<"Name "<<this->name<<std::endl;
    std::cout<<"Breed "<<this->breed<<std::endl;
    std::cout<<"Age "<<this->age<<std::endl;
    std::cout<<"Gender "<<this->gender<<std::endl;
}

bool Cat::lessThenByName(const Cat &cat)
{
    return (this->name < cat.name);
}

bool Cat::lessThenByBreed(const Cat &cat)
{
    return (this->breed < cat.breed);
}

bool Cat::lessThenByAge(const Cat &cat)
{
    return (this->age < cat.age);
}

bool Cat::lessThenByGender(const Cat &cat)
{
    return (this->gender < cat.gender);
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
