#include "sorter.h"
#include <fstream>
Sorter::Sorter(std::string startName, std::string resultName, unsigned short state)
{
    this->startFile = startName;
    this->resultFile = resultName;
    this->currentCat = 0;
    this->currentInput = 0;
    this->currentOutput = 0;
    this->readFrom[0] = 0;
    this->readFrom[1] = 0;
    this->blockSize = 1;
    this->name1 = "~forMerge1.dat";
    this->name2 = "~forMerge2.dat";
    this->name3 = "~forMerge3.dat";
    this->name4 = "~forMerge4.dat";
    setTypeOfSort(state);
}

void Sorter::setTypeOfSort(unsigned short state)
{
    switch (state) {
    case 0:
        lessThan = &Cat::lessThanByAge;
        break;
    case 1:
        lessThan = &Cat::lessThanByBreed;
        break;
    case 2:
        lessThan = &Cat::lessThanByName;
        break;
    default:
        std::cerr << "Unknow state. Set zero";
        lessThan = &Cat::lessThanByAge;
        break;
    }
}

void Sorter::sort()
{
    try
    {
        shrinkStartFile();
        openAll();
    }
    catch ( const char * error)
    {
        std::cerr << error <<std::endl;
        return ;
    }

    while(blockSize <= fileSizeInCats )
    {
        currentOutput = 0;
        currentInput = 0;
        while(1)
        {
            readFrom[0] = 0;
            readFrom[1] = 0;
            bool fullBlock = false;
            cats[0] = readOneCat(0,fullBlock);
            if(fullBlock)
            {
                std::cout<<"End in main cycle"<<std::endl;
                break;
            }
            bool currentRead = 1;
            currentCat = currentRead;
            while(1)
            {
                cats[(int)currentCat] = readOneCat(currentRead , fullBlock);
                if(fullBlock)
                {
                    writeCat(!currentCat);
                    currentOutput = !currentOutput;
                    break;
                }
                if((cats[0].*lessThan)(cats[1]))
                {
                    writeCat(0);
                    currentRead = 0;
                    currentCat = 0;
                }
                else
                {
                    writeCat(1);
                    currentRead = 1;
                    currentCat = 1;
                }
            }
        }
        blockSize *= 2;
        std::cout<<blockSize <<std::endl;
        try
        {
            swapInputOutput();
        }
        catch(const char * error)
        {
            std::cerr << error <<std::endl;
            return ;
        }
    }
    try
    {
        makeResult();
    }
    catch(const char * error)
    {
        std::cerr << error<<std::endl;
    }
}

Cat Sorter::readOneCat(bool stream , bool &fullBlock)
{
    fullBlock = false;
    bool readed1 = false;
    bool readed2 = false;
    Cat kitty;
    if(readFrom[(int)stream] < blockSize)
    {
        inputs[(int)stream] >> kitty;
        if(!inputs[(int)stream].eof())
        {
            readFrom[(int)stream]++;
            readed1 = true;
            return kitty;
        }
    }
    if(readFrom[(int)!stream] < blockSize )
    {
        inputs[(int)!stream] >> kitty;

        if(!inputs[(int)!stream].eof())
        {
            readFrom[(int)!stream]++;
            readed2 = true;
            return kitty;
        }
    }
    if(!readed1 && !readed2)
    {
        fullBlock = true;
    }
    return kitty;

}

void Sorter::swapInputOutput()
{
    closeAll();

    std::string tempStr;
    tempStr = name1;
    name1 = name3;
    name3 = tempStr;

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

void Sorter::makeResult()
{
    if(std::rename(name1.c_str(),resultFile.c_str()))
    {
        throw "Error with rename result file. Real name is "+name1;
    }
    if(std::remove(name2.c_str()) || std::remove(name3.c_str()) || std::remove(name4.c_str()))
    {
        throw "Error with deleting buf files";
    }
}

void Sorter::writeCat(bool index)
{
    outputs[(int)currentOutput] << cats[(int)index];
}

