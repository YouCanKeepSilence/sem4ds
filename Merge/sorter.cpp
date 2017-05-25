#include "sorter.h"
#include <fstream>
Sorter::Sorter(std::string startName, std::string resultName)
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
}

void Sorter::sort()
{
    int debugCounter=0;
    shrinkStartFile();
    try
    {
        openAll();
    }
    catch ( const char * error)
    {
        std::cerr << error <<std::endl;
        return ;
    }

    while(blockSize <= fileSizeInCats )
    {
//        char state;

        currentOutput = 0;
        currentInput = 0;
        while(1)
        {
            readFrom[0] = 0;
            readFrom[1] = 0;
            bool fullBlock = false;
            bool allEnds = false;
            char eofStream = -1;
            cats[0] = readOneCat(0,fullBlock,eofStream , allEnds);
            if(allEnds)
            {
                std::cout<<"End in main cycle"<<std::endl;
                break;
            }
            bool currentRead = 1;
            currentCat = currentRead;
            if(eofStream != -1)
            {
                currentCat = 0;
            }
            while(1)
            {
                if(eofStream != -1)         //Если в каком-то потоке конец, то шарашим из другого потока
                {
                    std::cout<<std::endl<<"!!!! eof in "<<(int)eofStream<<" !!!!!!!!"<<std::endl;
                    std::cout<<"Read form "<<(int)!eofStream<<" now "<<std::endl<<std::endl;
                    currentRead = !eofStream;
                }
                cats[(int)currentCat] = readOneCat(currentRead , fullBlock , eofStream , allEnds);
                if(allEnds)
                {
                    std::cout<<"End in sequence loop both eof"<<std::endl;
                    writeCat(!currentCat);
                    debugCounter++;
                    break;
                }
//                std::cout<<"Read new cat from "<<(int)currentRead <<std::endl;
//                cats[(int)currentCat].printCat();
//                std::cout<<"-------------------------";
//                std::cout<<std::endl;
                if(fullBlock)
                {

                    std::cout<<std::endl<<"Full block";
                    writeCat(!currentCat);
                    std::cout<<" output changed from "<<currentOutput << " to ";
                    currentOutput = !currentOutput;
                    std::cout<<currentOutput<<std::endl<<std::endl;
                    break;
                }
                if(cats[0].lessThenByAge(cats[1]))
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
//        if(blockSize == 4)
//            break;
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
    std::cout<< "Counts of non eaual files "<<debugCounter<<std::endl;
//    makeResult();
}

Cat Sorter::readOneCat(bool stream , bool &fullBlock, char &whereEnd, bool &bothEnd)
{
    fullBlock = false;
    bool readed1 = false;
    bool readed2 = false;
    bool eof1 = false;
    bool eof2 = false;
//    bool fileEnd = false;
    Cat kitty;
    if(readFrom[(int)stream] < blockSize)
    {
        inputs[(int)stream] >> kitty;

        if(inputs[(int)stream].eof())
        {
            whereEnd = 0;
            eof1 = true;
        }
        else
        {
            readFrom[(int)stream]++;
            readed1 = true;
        }
    }
    if(readFrom[(int)!stream] < blockSize && (!readed1 || eof1))
    {
        inputs[(int)!stream] >> kitty;

        if(inputs[(int)!stream].eof())
        {
            eof2 = true;
            whereEnd = 1;
        }
        else
        {
            readFrom[(int)!stream]++;
            readed2 = true;
        }
    }
    if(!readed1 && !readed2)
    {
        fullBlock = true;
    }
    if(eof1 && eof2)
    {
        bothEnd = true;
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

void Sorter::writeCat(bool index)
{
    outputs[(int)currentOutput] << cats[(int)index];
//    std::cout<<"write cat"<<std::endl;
//    cats[(int)index].printCat();
//    std::cout<<"------------------------"<<std::endl;

}

