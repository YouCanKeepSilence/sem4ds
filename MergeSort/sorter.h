#ifndef SORTER_H
#define SORTER_H
#include <string>
#include "cat.h"
class Sorter
{
public:
    Sorter(std::string startName , std::string resultName="result.dat", unsigned short state = 0);
    void setTypeOfSort(unsigned short state);   // Определяет тип сортировки : 0 - по возрасту, 1 - порода , 2 - имя
    void sort();
private:    
    bool (Cat::*lessThan)(const Cat & cat);

    std::string startFile;      //Имя начального файла
    std::string resultFile;     //Имя конечного файла
    std::string name1;          //Имена четырех потоков.
    std::string name2;
    std::string name3;
    std::string name4;

    unsigned int fileSizeInCats;    //Размер файла в котах)
    unsigned int blockSize;         // Размер упорядоченного блока
    unsigned int readFrom[2];       //Сколько прочитано за такт из первого потока и второго соответственно
    Cat cats[2];                    //Буферные коты

    bool currentCat;                // Текущий кот
    bool currentOutput;             //Текущий вывод
    bool currentInput;              //Текущий ввод

    std::ifstream inputs[2];        // Потоки ввода
    std::ofstream outputs[2];       // Потоки вывода

    Cat readOneCat(bool stream, bool &fullBlock);          // Читает одного кота из желаемого потока, если не выходит пробует из другого. Если ничего не прочитано возвращает true в fullBlock
    void swapInputOutput();                                 // Меняет местами ввод вывод
    void openAll();                                         //Открывает все потоки (полный вперед)
    void closeAll();                                        // Закрывает все потоки
    void shrinkStartFile();                                 //Разрезает стартовый файл на две части
    void makeResult();                                      // Собирает последние два куска в один
    void writeCat(bool index);                              //Пишет кота из массива в текущий вывод
};

#endif // SORTER_H
