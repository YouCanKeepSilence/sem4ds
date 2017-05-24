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

//void Sorter::Sort(std::string fileName)
//{
//    std::ifstream start;
//    start.open(fileName,std::ios::binary);
//    if(!start.is_open())
//    {
//        throw "Cannot open input file";
//    }
//    unsigned int bufferSize = 1;
//    start.seekg(0,start.end);
//    unsigned int fileSize = start.tellg() / CLASS_SIZE;
//    start.seekg(0,start.beg);
//    std::ofstream buf1;
//    std::ofstream buf2;
//    buf1.open("buf1.dat", std::ios::binary);
//    buf2.open("buf2.dat", std::ios::binary);
//    if(!buf1.is_open() || !buf2.is_open())
//    {
//        throw "Cannot open first two files";
//    }
//    for(unsigned int i = 0; i < (fileSize / 2); i++)
//    {
//        Cat temp;
//        start >> temp;
//        buf1 << temp;
//    }
//    for(unsigned int i = fileSize / 2; i< fileSize ; i++)
//    {
//        Cat temp;
//        start >> temp;
//        buf2<<temp;
//    }
//    buf1.close();
//    buf2.close();
//    while(1)
//    {
//        if(bufferSize >= fileSize /2)
//        {
//            break;
//        }
//        std::ifstream buf1;
//        std::ifstream buf2;
//        std::ofstream buf3;
//        std::ofstream buf4;
//        buf1.open("buf1.dat", std::ios::binary);
//        buf2.open("buf2.dat", std::ios::binary);
//        buf3.open("buf3.dat", std::ios::binary);
//        buf4.open("buf4.dat", std::ios::binary);
//        if(!buf1.is_open() || !buf2.is_open() || !buf3.is_open() || !buf4.is_open())
//        {
//            throw "Cannot open one of files in while loop";
//        }
//        Cat temp1;
//        Cat temp2;
//        unsigned int readedInFirst = 0;         //Кол-во прочитанных символов из первого файла (ограничено bufferSize)
//        unsigned int readedInSecond = 0;        //Кол-во прочитанных символов из второго файла (ограничено bufferSize)
//        bool InWhichFile = 0;                   //В какой файл пишем : 0 - первый файл , 1 - второй
//        bool FromWhichGet = 0;                  // Откуда берем 0 -первый файл 1 - второй
//        while(1)
//        {
//            if( buf1.eof() )
//            {
//                 //TODO flush
//                break;
//            }
//            else if ( buf2.eof())
//            {
//                //second flush
//                break;
//            }
//            std::ofstream * out;
//            InWhichFile == 0 ? (out = &buf3) : (out=&buf4);
//            buf1 >> temp1;
//            temp1.printCat();
//            buf2 >> temp2;
//            temp2.printCat();
//            while(1)
//            {
//                if(temp1.lessThenByName(temp2))
//                {
//                    FromWhichGet = 0;
//                }
//                else
//                {
//                    FromWhichGet = 1;
//                }
//                if(FromWhichGet == 0 && readedInFirst < bufferSize)
//                {
//                    *out << temp1;
//                    buf1 >> temp1;
//                    temp1.printCat();
//                    readedInFirst++;
//                }
//                else if(FromWhichGet == 1 && readedInSecond < bufferSize)
//                {
//                    *out << temp2;
//                    buf2 >> temp2;
//                    temp2.printCat();
//                    readedInSecond++;
//                }
//                else
//                {
//                    //FLUSH
//                    readedInFirst = 0;
//                    readedInSecond = 0;
//                    InWhichFile = !InWhichFile;
//                    break;
//                }
//            }

//        }
//        std::cout<<"---------------------------------"<<std::endl;
//        bufferSize *= 2;
//        buf1.close();
//        buf2.close();
//        buf3.close();
//        buf4.close();
//        if(std::remove("buf1.dat") || std::remove("buf2.dat"))
//        {
//            throw "Error with delete buf1 || buf2 ";
//        }
//        if(std::rename("buf3.dat","buf1.dat") || std::rename("buf4.dat","buf2.dat"))
//        {
//            throw "Error with rename buf3 || buf4";
//        }
//    }
//    Cat temp1 , temp2;
//    std::ifstream halfResult1;
//    std::ifstream halfResult2;
//    std::ofstream result;
//    halfResult1.open("buf1.dat", std::ios::binary);
//    halfResult2.open("buf2.dat", std::ios::binary);
//    result.open("result.dat" , std::ios::binary);
//    halfResult1 >> temp1;
//    halfResult2 >> temp2;
//    halfResult1.seekg(0,halfResult1.beg);
//    halfResult2.seekg(0,halfResult2.beg);
//    if(temp1.lessThenByName(temp2))
//    {
//        for(unsigned int i=0 ; i <fileSize /2 ; i++)
//        {
//            halfResult1 >> temp1;
//            result << temp1;
//        }
//        for(unsigned int i=fileSize /2 ; i <fileSize ; i++)
//        {
//            halfResult2 >> temp2;
//            result << temp2;
//        }
//    }
//    else
//    {
//        for(unsigned int i=fileSize /2 ; i <fileSize ; i++)
//        {
//            halfResult2 >> temp2;
//            result << temp2;
//        }
//        for(unsigned int i=0 ; i <fileSize /2 ; i++)
//        {
//            halfResult1 >> temp1;
//            result << temp1;
//        }


//    }
//    halfResult1.close();
//    halfResult2.close();
//    result.close();

//}
