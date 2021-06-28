#ifndef __ARCHIVO_HPP__
#define __ARCHIVO_HPP__

#define FILE_NAME "c:/Cuentas/Users.txt"
#define GEN_FOLDER_NAME "c:/Cuentas"

#define MSG_ERROR "\t\nERROR AL ABRIR EL ARCHIVO!!\n\n"
#define MSG_VALID "\n\t\t\tSE REGISTRO CORRECTAMENTE\n"

#define REPOSITORY "Repositorio_Local"
#define STATING_AREA "Area_de_preparacion"
#define WORKPLACE "Area_de_Trabajo"

#include <iostream> //
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "listaEnlazada.hpp"
#include "usuario.hpp"

template <class T>
class File
{
private:
    std::ofstream outFile;
    std::ifstream inFile;

public:
    File();
    ~File();
    void writeFile(std::string _nameUser, std::string _passwUser, std::string _emailUser);
    // cargar archivos de cada usuario
    void loadUserFiles(LinkedList<User*>* _list); // VERIFICAR PORQ NO DA CON TMPL
    
    void loadFile(LinkedList<T*>* _list);

    // crear archivo como almacen para cada carpeta de usuario
    void createGeneralFolder();
    // folder unico cuando se registra cada usuario
    void createUserFolder(std::string name);
    // carpetas cuando se inicializa el reporsitorio
    void createInitUserFolder(std::string name);
    // crear archivo X
    void createFileUser(T* _user, std::string _nameFile);
    // clonar carpeta de repositorio local a x ruta
    void cloneRepository(T* _user, std::string _destinationPath);
    // abrir archivo
    void openFile(T* _user, std::string _nameFile);
    // Listar archivos
    void listFiles(T* _user);
    // Agregar archivo area de preparación
    void addFile(T* _user, std::string _nameFile);
    
};

template <class T>
File<T>::File()
{
    // VERIFICAR POR QUE EL ERROR
    // std::ofstream outFile(FILE_NAME, std::ios::out | std::ios::app);
    // std::ofstream intFile(FILE_NAME, std::ios::in );
    createGeneralFolder(); // crea folder en C donde se almacenara todoas las carpetas de usuarios
}

template <class T>
void File<T>::writeFile(std::string _nameUser, std::string _passwUser, std::string _emailUser)
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

template <class T>
void File<T>::loadUserFiles(LinkedList<User*>* _list)
{
    for(LinkedList<User*>::Iterator it = _list->beginIt(); it != _list->endIt(); ++it)
    {
        std::string infoLine = "", infoPart = "", cheapName = "", cheapDate = "";
        User* currentData = *it;
        std::string pathFile = GEN_FOLDER_NAME "/" + currentData->getName() + "/FilesData.txt";
        std::ifstream inFile(pathFile, std::ios::in);
        if(inFile.fail()) std::cout << MSG_ERROR;
        else
        {
            while(std::getline(inFile, infoLine)) // Leemos lineas de archivo
            {
                std::stringstream data(infoLine);
                std::getline(data, infoPart, '-');
                cheapName = infoPart;
                std::getline(data, infoPart, '-');
                cheapDate = infoPart;

                UserFile* file = new UserFile(cheapName, cheapDate, currentData->getName()); // por otro lado se crea la fecha de creacion
                currentData->getStackFiles()->push(file);
            }
            inFile.close();
        }
    }
}

// validar información de archivo, leer info de usuario y archivos
template <class T>
void File<T>::loadFile(LinkedList<T*>* _list)
{
    std::string cheapName = "", cheapPassw = "", cheapEmail = "";
    std::string infoLine = "", infoPart = "";

    std::ifstream inFile(FILE_NAME, std::ios::in);

  
    auto loadData = [](LinkedList<T*>* _list, std::string _name, std::string _passw, std::string _email)
    {
        T* user = new T(_name, _passw, _email); // cargo los datos del archivo a la lista
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
    // CARGAR ARCHIVOS DE CADA USUARIO DE LA LSITA
    loadUserFiles(_list);
}

// quizas mejor en otra clase (USUARIO)
template <class T>
void File<T>::createGeneralFolder() { mkdir(GEN_FOLDER_NAME); }

template <class T>
void File<T>::createUserFolder(std::string name) 
{ 
    std::string pathFolder = GEN_FOLDER_NAME "/" + name;
    mkdir(pathFolder.c_str());
    std::string pathRepository = pathFolder + "/" + REPOSITORY;
    mkdir(pathRepository.c_str());
}

template <class T>
void File<T>::createInitUserFolder(std::string name)
{
    std::string pathFolder = GEN_FOLDER_NAME "/" + name;
    std::string pathStatingArea = pathFolder + "/" + STATING_AREA;
    mkdir(pathStatingArea.c_str());
    std::string pathWorkPlace = pathFolder + "/" + WORKPLACE;
    mkdir(pathWorkPlace.c_str());

    // pasar archivos a espacio de trabajo
    // si se crean nuevos archivos
    // la ruta cambia a la de area de trabajo
    std::string pathFile = "c:\\Cuentas\\" + name + "\\" + REPOSITORY + "\\*.txt";
    std::string newDestPath =  "c:\\Cuentas\\" + name + "\\" +  WORKPLACE;
    std::string command = "MOVE " + pathFile + " " + newDestPath;
    system(command.c_str());
}

template <class T>
void File<T>::createFileUser(T* _user, std::string _nameFile)
{
    std::string pathFile = GEN_FOLDER_NAME "/" + _user->getName() + "/" + REPOSITORY + "/" + _nameFile + ".txt";
    std::ofstream outFile(pathFile, std::ios::out | std::ios::app);

    if(outFile.fail())
        std::cerr << MSG_ERROR;
    else
    {
        std::cout << "\t\t\nArchivo creado correctamente !\n";
        std::string cheapDate = _user->addFile(_nameFile);
        outFile << _nameFile << " - " << cheapDate;
        _user->writeFilesData(_nameFile, cheapDate); // volvemos a crear la pila de archi.
    }
    outFile.close();
}

template <class T>
void File<T>::cloneRepository(T* _user, std::string _destPath)
{
    // XCOPY c:\Cuentas\rosa c:\Users\Amelia\Desktop /E
    std::string pathFile = "c:\\Cuentas\\" + _user->getName() + "\\" + REPOSITORY;
    std::string newDestPath =  _destPath + "\\" + REPOSITORY + "-" + _user->getName();
    mkdir(newDestPath.c_str());
    std::string command = "XCOPY " + pathFile + " " + newDestPath + " " + "/E" + "/-Y";
    std::cout << "\n";
    system(command.c_str());
    std::cout << "\n\t\tClonacion terminada !\n";
}

template <class T>
void File<T>::openFile(T* _user, std::string _nameFile)
{
    // Manera 1:
    // std::string pathFile = "c:\\Cuentas\\" + _user->getName() + "\\" + REPOSITORY;
    // std::string command = pathFile + "\\" + _nameFile + ".txt";
    // system(command.c_str());

    // PROBLEMA AL ABRIR, SE HACE UNA COPIA DEL ARCHIVO
    std::string pathFileOther = GEN_FOLDER_NAME "/" + _user->getName() + "/" + REPOSITORY + "/" + _nameFile + ".txt";
    // Manera 2:
    std::string _cheapContent = "";
    std::ofstream outFile(pathFileOther, std::ios::out | std::ios::app);
    if(outFile.fail()) std::cout << MSG_ERROR;
    else
    {
        std::cout << "\nIngrese contenido para el archivo : \n\n\t";
        getline(std::cin, _cheapContent);
        outFile << _cheapContent << "\n";

        std::cout << "\n\nIngreso existoso!!!";
    }
    outFile.close();

    // Abrir archivo para extraer contenido
    std::string currentContent = "";
    std::string line = "";

    std::ifstream inFile(pathFileOther, std::ios::in | std::ios::out);
    if(inFile.fail()) std::cout << MSG_ERROR;
    else
        while(getline(inFile, line))
            currentContent += line;
    inFile.close();

    // Comparación
    if((_user->getObjectByName(_nameFile)->getCurrentContent()).compare(currentContent) != 0)
    {
        std::string _newName = _nameFile + " - Modificado";
        _user->getObjectByName(_nameFile)->setName(_newName);
        _user->getObjectByName(_newName)->setCurrentContent(currentContent);        
    }
}

template <class T>
void File<T>::addFile(T* _user, std::string _nameFile)
{
    std::string pathFile = "c:\\Cuentas\\" + _user->getName() + "\\" + WORKPLACE + "\\" + _nameFile + ".txt";
    std::string newDestPath =  "c:\\Cuentas\\" + _user->getName() + "\\" +  STATING_AREA;
    std::string command = "MOVE " + pathFile + " " + newDestPath;
    system(command.c_str());
}

#endif