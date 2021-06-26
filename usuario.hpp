#ifndef __USUARIO_HPP__
#define __USUARIO_HPP__

#include <string>

#include "Pila.hpp"
#include "archivoUsuario.hpp"

class User
{
private:
    std::string name;
    std::string password;
    std::string email;

    Stack<UserFile*>* files;

public:
    User(std::string _name = "", std::string _passw = "", std::string _email = "") : name(_name), password(_passw), email(_email) {  files = new Stack<UserFile*>(); };
    ~User();
    inline std::string getName() const { return this->name; }
    inline std::string getPassword() const { return this->password; }
    inline std::string getEmail() const { return this->email; }
  

    void addFile(std::string _nameFile, std::string _creationDate);
    void printFiles();
};

User::~User() {}

void User::addFile(std::string _nameFile, std::string _creationDate)
{
    UserFile* file = new UserFile(_nameFile, _creationDate);
    files->push(file); // ERRORRRRRR
}

void User::printFiles()
{
    files->print();
}

#endif