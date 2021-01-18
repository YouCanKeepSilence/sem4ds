#ifndef FINDER_H
#define FINDER_H
#include <string>
#include "cat.h"
class Finder
{
public:
    Finder(std::string sortByName="sortByName.dat" , std::string sortByAge="sortByAge.dat",
           std::string sortByBreed="sortByBreed.dat");
    void setFileWithNames(std::string sortByName);
    void setFileWithAges(std::string sortByAge);
    std::string getFileWithNames();
    std::string getFileWithAges();

    void findAge(int from, int to = 0);
    void findName(std::string name);
    void findBreed(std::string breed);
private:

    long long findOffset(Cat target);            //Вернет необходимый сдвиг для установки в начало искомых котов, -1 если нет такого.
    void setState(int state);
    bool (Cat::*lessThan)(const Cat & cat);
    void openCurrentFile();
    std::ifstream in;
    std::string currentFileName;
    std::string sortByName;
    std::string sortByAge;
    std::string sortByBreed;
};

#endif // FINDER_H
