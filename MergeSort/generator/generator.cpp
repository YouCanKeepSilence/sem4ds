#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#define DICTIONARY_SIZE 10000

int main()
{
    std::ifstream in1;
    std::ifstream in2;
    std::ifstream in3;
    in1.open("heCat.txt", std::ios_base::binary);
    in2.open("sheCat.txt", std::ios_base::binary);
    in3.open("breeds.txt", std::ios_base::binary);
    if (!in1.is_open() || !in2.is_open() || !in3.is_open())
    {
        std::cerr<<"One of in files isn't open"<<std::endl;
        return 1;
    }
    
    std::vector<std::string> males;
    std::vector<std::string> females;
    std::vector<std::string> breeds;
    
    std::string tempStr;
    int maxNameLen=0;
    int maxBreedLen=0;
    
    while (!in1.eof())
    {
        getline(in1,tempStr);
        //std::cerr<<tempStr.size()<<std::endl;
        males.push_back(tempStr);
        
        if (tempStr.size()>maxNameLen)
        {
            maxNameLen=tempStr.size();
        }
    }
    
    while (!in2.eof())
    {
        getline(in2,tempStr);
        //std::cerr<<tempStr.size()<<std::endl;
        females.push_back(tempStr);
        
        if (tempStr.size()>maxNameLen)
        {
            maxNameLen=tempStr.size();
        }
    }
    
    while (!in3.eof())
    {
        getline(in3,tempStr);
        //std::cerr<<tempStr.size()<<std::endl;
        breeds.push_back(tempStr);
        
        if (tempStr.size()>maxBreedLen)
        {
            maxBreedLen=tempStr.size();
        }
    }
    std::cout<<"Максимальная длина имени: "<<maxNameLen<<std::endl;
    std::cout<<"Максимальная длина породы: "<<maxBreedLen<<std::endl;
    /*for (int i=0; i<males.size(); ++i)
    {
        while (males.at(i).size()<maxNameLen)
        {
            males[i]+=' ';
        }
    }
    
    for (int i=0; i<females.size(); ++i)
    {
        while (females.at(i).size()<maxNameLen)
        {
            females[i]+=' ';
        }
    }
    
    for (int i=0; i<breeds.size(); ++i)
    {
        while (breeds.at(i).size()<maxBreedLen)
        {
            breeds[i]+=' ';
        }
    }*/
    
    in1.close();
    in2.close();
    in3.close();
    
    std::ofstream out;
    out.open("dictionary.txt");
    if (!out.is_open())
    {
        std::cerr<<"Out file isn't open"<<std::endl;
        return 1;
    }
    
    srand(time(0));
    for (unsigned int i=0; i<DICTIONARY_SIZE; ++i)
    {
        int seed=rand();
        
        bool gender=seed%2;
        
        std::string name;
        if (gender)
        {
            name=males.at(seed%males.size());
        }
        else
        {
            name=females.at(seed%females.size());
        }
        std::string breed=breeds.at(seed%breeds.size());
        
        int age=(seed%100)+1;
        
        out.write(name.c_str(),maxNameLen);
        out.write(breed.c_str(),maxBreedLen);
        out.write((char*)&age,4);
        if (gender)
        {
            out.put('m');
        }
        else
        {
            out.put('f');
        }
    }
    
    out.close();
    return 0;
}
