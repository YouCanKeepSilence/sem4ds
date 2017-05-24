#ifndef SORTER_H
#define SORTER_H
#include <string>
#include "cat.h"
class Sorter
{
public:
    Sorter(std::string startName , std::string resultName="result.dat");
    void sort();
private:
    std::string startFile;      //Имя начального файла
    std::string resultFile;     //Имя конечного файла
    std::string name1;          //Имена четырех потоков.
    std::string name2;
    std::string name3;
    std::string name4;

    Cat cats[2];                //Буферные коты
    bool currentCat;            // Текущий кот
    bool currentOutput;         //Текущий вывод
    bool currentInput;          //Текущий ввод
    std::ifstream inputs[2];    // Потоки ввода
    std::ofstream outputs[2];   // Потоки вывода

    void swapInputOutput();     // Меняет местами ввод вывод
    void openAll();             //Открывает все потоки (полный вперед)
    void closeAll();            // Закрывает все потоки
    void shrinkStartFile();     //Разрезает стартовый файл на две части
    void makeResult();          // Собирает последние два куска в один
};

#endif // SORTER_H
