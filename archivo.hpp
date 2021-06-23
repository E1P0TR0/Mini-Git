#ifndef __ARCHIVO_HPP__
#define __ARCHIVO_HPP__

#define FILE_NAME "c:/Cuentas/Users.txt"
#define GEN_FOLDER_NAME "c:/Cuentas"

#define MSG_ERROR "\t\nERROR AL ABRIR EL ARCHIVO!!\n\n"
#define MSG_VALID "\n\t\t\tSE REGISTRO CORRECTAMENTE\n"

#include <iostream> //
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "listaEnlazada.hpp"
#include "usuario.hpp"

class File
{
private:
    std::ofstream outFile;
    std::ifstream inFile;

public:
    File();
    ~File();
    void writeFile(std::string _nameUser, std::string _passwUser, std::string _emailUser);
    void loadFile(LinkedList<User*>* _list);

    // crear archivo como almacen para cada carpeta de usuario
    void createGeneralFolder();
    // folder unico cuando se registra cada usuario
    void createUserFolder(std::string name);
    // carpetas cuando se inicializa el reporsitorio
    void createInitUserFolder(std::string name);

};

File::File()
{
    // VERIFICAR POR QUE EL ERROR
    // std::ofstream outFile(FILE_NAME, std::ios::out | std::ios::app);
    // std::ofstream intFile(FILE_NAME, std::ios::in );

    createGeneralFolder(); // crea folder en C donde se almacenara todoas las carpetas de usuarios
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

// validar información de archivo
void File::loadFile(LinkedList<User*>* _list)
{
    std::string cheapName = "", cheapPassw = "", cheapEmail = "";
    std::string infoLine = "", infoPart = "";

    std::ifstream inFile(FILE_NAME, std::ios::in);

  
    auto loadData = [](LinkedList<User*>* _list, std::string _name, std::string _passw, std::string _email)
    {
        User* user = new User(_name, _passw, _email); // cargo los datos del archivo a la lista
        _list->addFinal(user); 
    };

    if(!inFile.is_open()) return;
    
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
            std::getline(data, infoPart, '-');
            cheapEmail = infoPart;

            loadData(_list, cheapName, cheapPassw, cheapEmail);

        }
        inFile.close();
    }
}

// quizas mejor en otra clase (USUARIO)
void File::createGeneralFolder() { mkdir(GEN_FOLDER_NAME); }

void File::createUserFolder(std::string name) 
{ 
    std::string pathFolder = GEN_FOLDER_NAME "/" + name;
    mkdir(pathFolder.c_str());
    std::string pathRepository = pathFolder + "/" + "Repositorio Local";
    mkdir(pathRepository.c_str());
}

void File::createInitUserFolder(std::string name)
{
    std::string pathFolder = GEN_FOLDER_NAME "/" + name;
    std::string pathStatingArea = pathFolder + "/" + "Area de preparacion";
    mkdir(pathStatingArea.c_str());
    std::string pathWorkPlace = pathFolder + "/" + "Area de Trabajo";
    mkdir(pathWorkPlace.c_str());
}

#endif