#ifndef __ARCHIVO_HPP__
#define __ARCHIVO_HPP__

#define FILE_NAME "Users.txt"

#include <iostream>
#include <fstream>

class File
{
private:
    std::ofstream outFile;
    std::ifstream inFile;

public:
    File();
    ~File();
    void writeFile(std::string _nameUser, std::string _passwUser);
    void readFile();
};

File::File()
{
    // VERIFICAR POR QUE EL ERROR
    // std::ofstream outFile(FILE_NAME, std::ios::out | std::ios::app);
    // std::ofstream intFile(FILE_NAME, std::ios::in );
}

void File::writeFile(std::string _nameUser, std::string _passwUser)
{
    std::ofstream outFile(FILE_NAME, std::ios::out | std::ios::app);
    
    if(outFile.fail())
        std::cerr << "\t\nERROR AL ABRIR EL ARCHIVO!!\n\n";
    else
    {
        outFile << _nameUser << "-" << _passwUser << "\n";
        std::cout << "\n\t\t\tSE REGISTRO CORRECTAMENTE\n";
    }
    outFile.close();
}

void File::readFile()
{

}

#endif