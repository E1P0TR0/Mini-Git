#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <string>
#include <fstream>

#include "Pila.hpp"
#include "archivoUsuario.hpp"

class User
{
private:
    std::string name;
    std::string password;
    std::string email;

    //bool isInit;

    Stack<UserFile*>* files;

public:
    User(std::string _name = "", std::string _passw = "", std::string _email = "") : name(_name), password(_passw), email(_email) {  files = new Stack<UserFile*>(); };
    ~User();
    inline std::string getName() const { return this->name; }
    inline std::string getPassword() const { return this->password; }
    inline std::string getEmail() const { return this->email; }
    inline Stack<UserFile*>* getStackFiles() const { return this->files; }

    std::string addFile(std::string _nameFile);
    void printFiles();

    void writeFilesData(std::string _nameFile, std::string _cheapDate);
    // void loadFilesData(std::string _nameFile, std::string cheapDate);

    UserFile* getObjectByName(std::string _name) { return files->getByName(_name); }

    // void setIsInit(bool _init) { this->isInit = _init; }
    // bool getIsInit() const { return this->isInit; }
};

User::~User() {}

std::string User::addFile(std::string _nameFile)
{
    UserFile* file = new UserFile(_nameFile); // por otro lado se crea la fecha de creacion
    files->push(file);
    return file->getCreationDate();
}

void User::printFiles() 
{ 
    // Cargar datos y luego mostrar
    // ACCEDER A CADA ARCHIVO Y leer primera linea
    files->print();
}

void User::writeFilesData(std::string _nameFile, std::string _cheapDate)
{
    std::string pathFile = GEN_FOLDER_NAME "/" + this->name + "/FilesData.txt";
    std::ofstream outFile(pathFile, std::ios::out | std::ios::app);
    if(outFile.fail()) std::cout << "\tERROR AL CREAR ARCHIVO !\n";
    else
        outFile << _nameFile << "-" << _cheapDate;
    outFile.close();
}

#endif