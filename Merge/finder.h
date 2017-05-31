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
    void find(int age);
    void find(int from, int to);
    void find(std::string word);
private:
    std::string sortByName;
    std::string sortByAge;
};

#endif // FINDER_H
