#ifndef __ARCHIVO_HPP__
#define __ARCHIVO_HPP__

#define FILE_NAME "Users.txt"
#define GEN_FOLDER_NAME "c:/Cuentas"

#define MSG_ERROR "\t\nERROR AL ABRIR EL ARCHIVO!!\n\n"
#define MSG_VALID "\n\t\t\tSE REGISTRO CORRECTAMENTE\n"

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

class File
{
private:
    std::ofstream outFile;
    std::ifstream inFile;

public:
    File();
    ~File();
    void writeFile(std::string _nameUser, std::string _passwUser, std::string _emailUser);
    bool loadFile(std::string _nameUser, std::string _passwUser);

    // crear archivo como almacen para cada carpeta de usuario
    void createGeneralFolder();

    void createUserFolder(std::string name);

};

File::File()
{
    // VERIFICAR POR QUE EL ERROR
    // std::ofstream outFile(FILE_NAME, std::ios::out | std::ios::app);
    // std::ofstream intFile(FILE_NAME, std::ios::in );

    createGeneralFolder();
}

void File::writeFile(std::string _nameUser, std::string _passwUser, std::string _emailUser)
{
    std::ofstream outFile(FILE_NAME, std::ios::out | std::ios::app);
    
    if(outFile.fail())
        std::cerr << MSG_ERROR;
    else
    {
        outFile << _nameUser << "-" << _passwUser << "-" << _emailUser << "\n";
        std::cout << MSG_VALID;
    }
    outFile.close();
}

// o mejor dicho para validar
bool File::loadFile(std::string _nameUser, std::string _passwUser)
{
    std::string cheapName = "", cheapPassw = "";
    std::string infoLine = "", infoPart = "";

    std::ifstream inFile(FILE_NAME, std::ios::in);

    bool valid = false; 

    if(inFile.fail())
        std::cerr << MSG_ERROR;
    else
    {
        while(std::getline(inFile, infoLine)) // Leemos lineas de archivo
        {
            std::stringstream data(infoLine);
            std::getline(data, infoPart, '-');
            cheapName = infoPart;
            std::getline(data, infoPart, '-');
            cheapPassw = infoPart;

            if(cheapName == _nameUser && cheapPassw == _passwUser)
                return true;
        }
    }
    return false;
}

void File::createGeneralFolder() { mkdir(GEN_FOLDER_NAME); }

void File::createUserFolder(std::string name) 
{ 
    std::string pathFolder = GEN_FOLDER_NAME "/" + name;
    mkdir(pathFolder.c_str());
    std::string pathRepository = pathFolder + "/" + "Repositorio Local";
    mkdir(pathRepository.c_str());
    std::string pathStatingArea = pathFolder + "/" + "Area de preparacion";
    mkdir(pathStatingArea.c_str());
    std::string pathWorkPlace = pathFolder + "/" + "Area de Trabajo";
    mkdir(pathWorkPlace.c_str());
}

#endif