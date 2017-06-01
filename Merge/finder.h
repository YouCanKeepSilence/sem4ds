#ifndef FINDER_H
#define FINDER_H
#include <string>

class Finder
{
public:
    Finder(std::string sortByName="sortByName.dat" , std::string sortByAge="sortByAge.dat");
    void setFileWithNames(std::string sortByName);
    void setFileWithAges(std::string sortByAge);
    std::string getFileWithNames();
    std::string getFileWithAges();

    void find(int from, int to = 0);
    void find(std::string word);
private:
    long long findOffset(int age);            //Вернет необходимый сдвиг для установки в начало искомых котов, -1 если нет такого.
    std::string sortByName;
    std::string sortByAge;
};

#endif // FINDER_H
