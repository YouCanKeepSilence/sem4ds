#ifndef CAT_H
#define CAT_H
#include <string>
#include <fstream>
#include <iostream>
#define MAX_SIZE_OF_NAME 11
#define MAX_SIZE_OF_BREED 30
#define CLASS_SIZE 46
class Cat
{
public:
    Cat(std::string name="",std::string breed="",int age=0,char gender='m');
    friend std::ostream& operator<<(std::ostream& stream, Cat &cat);
    friend std::istream& operator>>(std::istream& stream,Cat &cat);
    int getAge();
    std::string getName();
    std::string getBreed();
    char getGender();
    void printCat();
    bool lessThenByName( const Cat & cat);
    bool lessThenByBreed(const Cat & cat);
    bool lessThenByAge(const Cat & cat);
    bool lessThenByGender(const Cat & cat);
private:
    std::string name;
    std::string breed;
    int age;
    char gender;

};

#endif // CAT_H
