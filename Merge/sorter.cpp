#include "sorter.h"
#include <fstream>
Sorter::Sorter(std::string startName, std::string resultName)
{
    this->startFile = startName;
    this->resultFile = resultName;
    this->currentCat = 0;
    this->currentInput = 0;
    this->currentOutput = 0;
    this->name1 = "~forMerge1.dat";
    this->name2 = "~forMerge2.dat";
    this->name3 = "~forMerge3.dat";
    this->name4 = "~forMerge4.dat";
}

void Sorter::sort()
{
    shrinkStartFile();

//    makeResult();
}

void Sorter::swapInputOutput()
{
    closeAll();

    std::string tempStr;
    tempStr = name1;
    name1 = name3;
    name3 = name1;

    tempStr = name2;
    name2 = name4;
    name4 = tempStr;

    try
    {
        openAll();
    }
    catch(const char * error)
    {
        throw error;
    }
}

void Sorter::openAll()
{
    inputs[0].open(name1, std::ios::binary);
    inputs[1].open(name2, std::ios::binary);
    outputs[0].open(name3, std::ios::binary);
    outputs[1].open(name4, std::ios::binary);
    if(!inputs[0].is_open() || !inputs[1].is_open() || !outputs[0].is_open() || !outputs[1].is_open())
    {
        throw "VSE PLOHO POTOKI YSHLI SPAT'!";
    }
}

void Sorter::closeAll()
{
    inputs[0].close();
    inputs[1].close();
    outputs[0].close();
    outputs[1].close();

}

void Sorter::shrinkStartFile()
{
    std::ifstream start;
    start.open(startFile, std::ios::binary);
    if(!start.is_open())
    {
        throw "Cannot open start file!";
    }
    outputs[0].open(name1, std::ios::binary);
    outputs[1].open(name2, std::ios::binary);
    if(!outputs[0].is_open() || !outputs[1].is_open())
    {
        throw "Cannot open buffer files!";
    }
    start.seekg(0, start.end);
    fileSizeInCats = start.tellg() / CLASS_SIZE;
    start.seekg(0, start.beg);
    Cat temp;
    for(unsigned int i = 0; i < fileSizeInCats / 2; ++i)
    {
        start >> temp;
        outputs[0] << temp;
    }
    for(unsigned int i = fileSizeInCats / 2; i < fileSizeInCats; ++i)
    {
        start >> temp;
        outputs[1] << temp;
    }
    start.close();
    outputs[0].close();
    outputs[1].close();

}

